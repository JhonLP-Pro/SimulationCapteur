#include "sensor.hpp"
#include <random>

// Constructeur par défaut
Sensor::Sensor() : id(0), type("inconnu"), serverPtr(nullptr), currentTime(0) {}

// Destructeur
Sensor::~Sensor() {}

// Constructeur avec paramètres
Sensor::Sensor(int id, string type, double value, class server *serverPtr)
    : id(id), type(type), serverPtr(serverPtr), currentTime(0) {}

// Constructeur de copie
Sensor::Sensor(const Sensor &s)
    : id(s.id), type(s.type), serverPtr(s.serverPtr), currentTime(s.currentTime) {}

// Opérateur d'affectation
Sensor &Sensor::operator=(const Sensor &s) {
    if (this != &s) {
        id = s.id;
        type = s.type;
        serverPtr = s.serverPtr;
        currentTime = s.currentTime;
    }
    return *this;
}

// Met à jour la valeur du capteur
void Sensor::update(int time) {
    currentTime = time;
    execute();
}

void Sensor::execute() {
    string mesure = generateMeasurement();

    ostringstream measurement;
    measurement << "Capteur ID: " << id
                << ", Type: " << type
                << ", Valeur: " << mesure
                << ", seconde: " << currentTime;

    if (serverPtr) {
        serverPtr->consoleWrite(measurement.str());
        serverPtr->fileWrite(type, measurement.str());
    }
}
