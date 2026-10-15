#include "temperatureSensor.hpp"
#include "header.hpp"
#include <random>

// Constructeur par défaut
temperatureSensor::temperatureSensor() : Sensor(), temperature(0.0f) {}

// Constructeur avec paramètres
temperatureSensor::temperatureSensor(int id, string type, float temperature, class server *serverPtr)
    : Sensor(id, type, 0.0, serverPtr), temperature(temperature) {}

// Constructeur de copie
temperatureSensor::temperatureSensor(const temperatureSensor &s)
    : Sensor(s), temperature(s.temperature) {}

// Opérateur d'affectation
temperatureSensor &temperatureSensor::operator=(const temperatureSensor &s) {
    if (this != &s) {
        Sensor::operator=(s);
        temperature = s.temperature;
    }
    return *this;
}

// Destructeur
temperatureSensor::~temperatureSensor() {}

Sensor* temperatureSensor::clone() const {
    return new temperatureSensor(*this);
}

// Génère une mesure spécifique au capteur de température
string temperatureSensor::generateMeasurement() {
    // Génération d'une mesure de température aléatoire pour la simulation
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(-10.0, 40.0); // Plage de température simulée entre -10 et 40 degrés Celsius
    temperature = dis(gen);

    // Retourne la mesure de température avec deux décimales
    ostringstream measurement;
    measurement << fixed << setprecision(2) << temperature;
    return measurement.str();
}