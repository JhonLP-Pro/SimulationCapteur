#include "server.hpp"

//constructeur par defaut
server::server() : consoleEnabled(true) {
    const string logFiles[] = {
        "log_Temperature.txt",
        "log_Humidite.txt",
        "log_Etat lumière.txt",
        "log_Son.txt"
    };

    for (const string &filename : logFiles) {
        ofstream logFile(filename, ios::out | ios::trunc);
        if (!logFile.is_open()) {
            cerr << "Erreur lors de la reinitialisation du fichier "
                 << filename << "." << endl;
        }
    }
}

// Destructeur
server::~server() {}

// Constructeur de copie
server::server(const server &s) : consoleEnabled(s.consoleEnabled) {}

// Affichage dans la console
void server::consoleWrite(string data) {
    if (consoleEnabled) {
        cout << "[" << currentDateTime() << "] " << data << endl;
    }
}

// Ajoute la mesure au fichier correspondant au type pour la session en cours
void server::fileWrite(string type, string measurement) {
    const string filename = "log_" + type + ".txt";
    ofstream logFile(filename, ios::out | ios::app);
    if (logFile.is_open()) {
        logFile << "[" << currentDateTime() << "] " << measurement << endl;
    } else {
        cerr << "Erreur lors de l'ouverture du fichier " << filename
             << " pour l'ecriture." << endl;
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