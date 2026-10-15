#include "lightSensor.hpp"
#include "header.hpp"
#include <random>

// Constructeur par défaut
lightSensor::lightSensor() : Sensor(), lightstatus(false) {}

// Constructeur avec paramètres
lightSensor::lightSensor(int id, string type, bool lightstatus, class server *serverPtr)
    : Sensor(id, type, 0.0, serverPtr), lightstatus(lightstatus) {} 

// Constructeur de copie
lightSensor::lightSensor(const lightSensor& s)
    : Sensor(s), lightstatus(s.lightstatus) {}

// Opérateur d'affectation
lightSensor &lightSensor::operator=(const lightSensor &s) {
    if (this != &s) {
        Sensor::operator=(s);
        lightstatus = s.lightstatus;
    }
    return *this;
};

// Destructeur
lightSensor::~lightSensor() {}

Sensor* lightSensor::clone() const {
    return new lightSensor(*this);
}

// Génère une mesure spécifique au capteur de luminosité
string lightSensor::generateMeasurement() {
    // Génération d'une mesure de luminosité aléatoire pour la simulation
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, 1); // Plage de luminosité simulée entre 0 (éteint) et 1 (allumé)
    if (dis(gen) == 0) {
        lightstatus = false;
    } else {
        lightstatus = true;
    }
    return lightstatus ? "true" : "false";
}
