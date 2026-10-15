#include "humiditySensor.hpp"
#include "header.hpp"
#include <random>

// Constructeur par défaut
humiditySensor::humiditySensor() : Sensor(), humidity(0.0f) {}

// Constructeur avec paramètres
humiditySensor::humiditySensor(int id, string type, float humidity, class server *serverPtr)
    : Sensor(id, type, 0.0, serverPtr), humidity(humidity) {}

// Constructeur de copie
humiditySensor::humiditySensor(const humiditySensor &s)
    : Sensor(s), humidity(s.humidity) {}

// Opérateur d'affectation
humiditySensor &humiditySensor::operator=(const humiditySensor &s) {
    if (this != &s) {
        Sensor::operator=(s);
        humidity = s.humidity;
    }
    return *this;
}

// Destructeur
humiditySensor::~humiditySensor() {}

Sensor* humiditySensor::clone() const {
    return new humiditySensor(*this);
}

// Génère une mesure spécifique au capteur de température
string humiditySensor::generateMeasurement() {
    // Génération d'une mesure de température aléatoire pour la simulation
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(0.0, 100.0); // Plage de température simulée entre 0 et 100 pourcentage
    humidity = dis(gen);

    // Retourne la mesure de température sous forme de chaîne de caractères
    
    ostringstream measurement;
    measurement << fixed << setprecision(2) << humidity;
    return measurement.str();
}