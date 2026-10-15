#include "server.hpp"

//constructeur par defaut
server::server() : consoleEnabled(true) {
    // Initialisation du flux de sortie vers le fichier de journalisation
    data.open("log.txt", ios::out | ios::trunc);
    if (!data.is_open()) {
        cerr << "Erreur lors de l'ouverture du fichier log.txt" << endl;
    }
}

// Destructeur
server::~server() {
    if (data.is_open()) {
        data.close();
    }
}

// Constructeur de copie
server::server(const server &s) : consoleEnabled(s.consoleEnabled) {
    // Ouverture d'un nouveau fichier de journalisation
    data.open("log.txt", ios::out | ios::trunc);
    if (!data.is_open()) {
        cerr << "Erreur lors de l'ouverture du fichier log.txt" << endl;
    }
}

// Affichage dans la console
void server::consoleWrite(string data) {
    if (consoleEnabled) {
        cout << "[" << currentDateTime() << "] " << data << endl;
    }
}

// Écriture de la dernière mesure de chaque type dans le fichier
void server::fileWrite(string type, string measurement) {
    latestMeasurements[type] = "[" + currentDateTime() + "] " + measurement;

    if (this->data.is_open()) {
        this->data.close();
    }

    this->data.open("log.txt", ios::out | ios::trunc);
    if (this->data.is_open()) {
        for (const auto &entry : latestMeasurements) {
            this->data << entry.second << endl;
        }
        this->data.flush();
    } else {
        cerr << "Erreur: le fichier n'est pas ouvert pour l'écriture." << endl;
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