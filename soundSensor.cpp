#include "soundSensor.hpp"
#include "header.hpp"
#include <random>

// Constructeur par défaut
soundSensor::soundSensor() : Sensor(), soundLevel(0.0f) {}

// Constructeur avec paramètres
soundSensor::soundSensor(int id, string type, float soundLevel, class server *serverPtr)
    : Sensor(id, type, 0.0, serverPtr), soundLevel(soundLevel) {}

// Constructeur de copie
soundSensor::soundSensor(const soundSensor &s)
    : Sensor(s), soundLevel(s.soundLevel) {}

// Opérateur d'affectation
soundSensor &soundSensor::operator=(const soundSensor &s) {
    if (this != &s) {
        Sensor::operator=(s);
        soundLevel = s.soundLevel;
    }
    return *this;
}

// Destructeur
soundSensor::~soundSensor() {}

Sensor* soundSensor::clone() const {
    return new soundSensor(*this);
}

// Génère une mesure spécifique au capteur de température
string soundSensor::generateMeasurement() {
    // Génération d'une mesure de température aléatoire pour la simulation
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(0.0, 150.0); // Plage de température simulée entre 0 et 150 décibels
    soundLevel = dis(gen);

    ostringstream measurement;
    measurement << fixed << setprecision(2) << soundLevel;
    return measurement.str();
}