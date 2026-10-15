#include "scheduler.hpp"

// Constructeur par défaut
scheduler::scheduler() {}

// Destructeur
scheduler::~scheduler() {
    for (Sensor* sensor : sensors) {
        delete sensor;
    }
}

// Constructeur de copie
scheduler::scheduler(const scheduler &s) {
    for (Sensor* sensor : s.sensors) {
        sensors.push_back(sensor->clone());
    }
}

// Opérateur d'affectation
scheduler &scheduler::operator=(const scheduler &s) {
    if (this != &s) {
        // Supprime les capteurs existants
        for (Sensor* sensor : sensors) {
            delete sensor;
        }
        sensors.clear();

        // Copie les capteurs de l'ordonnanceur source
        for (Sensor* sensor : s.sensors) {
            sensors.push_back(sensor->clone());
        }
    }
    return *this;
}

// Ajoute un capteur
void scheduler::addSensor(Sensor* sensor) {
    sensors.push_back(sensor);
}

// Simule l'exécution des processus pendant un tour
void scheduler::simulate(int tick) {
    for (Sensor* sensor : sensors) {
        sensor->update(tick);
    }
}