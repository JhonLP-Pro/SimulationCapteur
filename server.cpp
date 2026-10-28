#include "server.hpp"

#ifndef LOG_DIRECTORY
#define LOG_DIRECTORY "build"
#endif

//constructeur par defaut
server::server() : consoleEnabled(true) {
    const string logFiles[] = {
        "log_Temperature.txt",
        "log_Humidite.txt",
        "log_Etat lumière.txt",
        "log_Son.txt"
    };

    for (const string &filename : logFiles) {
        ofstream logFile(string(LOG_DIRECTORY) + "/" + filename,
                         ios::out | ios::trunc);
        if (!logFile.is_open()) {
            cerr << "Erreur lors de la reinitialisation du fichier "
                 << string(LOG_DIRECTORY) + "/" + filename << "." << endl;
        }
    }
}

// Destructeur
server::~server() {}

// Constructeur de copie
server::server(const server &s)
    : consoleEnabled(s.consoleEnabled), statistics(s.statistics) {}

server &server::operator=(const server &s) {
    if (this != &s) {
        consoleEnabled = s.consoleEnabled;
        statistics = s.statistics;
    }
    return *this;
}

// Affichage dans la console
void server::consoleWrite(string data) {
    if (consoleEnabled) {
        cout << "[" << currentDateTime() << "] " << data << endl;
    }
}

// Ajoute la mesure au fichier correspondant au type pour la session en cours
void server::fileWrite(string type, string measurement) {
    updateStatistics(type, measurement);

    const string filename = string(LOG_DIRECTORY) + "/log_" + type + ".txt";
    ofstream logFile(filename, ios::out | ios::app);
    if (logFile.is_open()) {
        logFile << "[" << currentDateTime() << "] " << measurement << endl;
    } else {
        cerr << "Erreur lors de l'ouverture du fichier " << filename
             << " pour l'ecriture." << endl;
    }
}

void server::updateStatistics(const string &type, const string &measurement) {
    MeasurementStats &stats = statistics[type];
    ++stats.count;

    const size_t valuePosition = measurement.find("Valeur: ");
    if (valuePosition == string::npos) {
        return;
    }

    string value = measurement.substr(valuePosition + 8);
    const size_t separatorPosition = value.find(',');
    if (separatorPosition != string::npos) {
        value = value.substr(0, separatorPosition);
    }
    if (value == "true") {
        ++stats.trueCount;
        return;
    }
    if (value == "false") {
        ++stats.falseCount;
        return;
    }

    try {
        const double numericValue = stod(value);
        if (stats.numericCount == 0) {
            stats.minimum = numericValue;
            stats.maximum = numericValue;
        } else {
            stats.minimum = min(stats.minimum, numericValue);
            stats.maximum = max(stats.maximum, numericValue);
        }
        stats.sum += numericValue;
        ++stats.numericCount;
    } catch (const invalid_argument &) {
        cerr << "Erreur : valeur de mesure invalide pour " << type << "." << endl;
    } catch (const out_of_range &) {
        cerr << "Erreur : valeur de mesure hors limites pour " << type << "." << endl;
    }
}

void server::writeSummaryToFiles() const {
    for (const auto &entry : statistics) {
        const string &type = entry.first;
        const MeasurementStats &stats = entry.second;
        const string filename = string(LOG_DIRECTORY) + "/log_" + type + ".txt";
        ofstream logFile(filename, ios::out | ios::app);

        if (!logFile.is_open()) {
            cerr << "Erreur lors de l'ouverture du fichier " << filename
                 << " pour l'ecriture du recapitulatif." << endl;
            continue;
        }

        logFile << "\n===== Récapitulatif des mesures =====" << endl;
        logFile << "Nombre de mesures : " << stats.count << endl;
        if (stats.numericCount > 0) {
            logFile << fixed << setprecision(2)
                    << "Moyenne : " << stats.sum / stats.numericCount << endl
                    << "Minimum : " << stats.minimum << endl
                    << "Maximum : " << stats.maximum << endl;
        } else {
            logFile << "Etat true : " << stats.trueCount << endl
                    << "Etat false : " << stats.falseCount << endl;
        }
        logFile << "=====================================" << endl;
    }
}

string server::currentDateTime() const {
    const time_t now = time(nullptr);
    tm localTime{};
#ifdef _WIN32
    localtime_s(&localTime, &now);
#else
    localtime_r(&now, &localTime);
#endif

    ostringstream timestamp;
    timestamp << put_time(&localTime, "%Y-%m-%d %H:%M:%S");
    return timestamp.str();
}

// Surcharge de l'opérateur <<
ostream &operator<<(ostream &os, const server &s) {
    os << "Serveur [consoleActive=" << s.consoleEnabled << "]";
    return os;
}