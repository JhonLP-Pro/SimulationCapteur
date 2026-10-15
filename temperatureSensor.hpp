#ifndef TEMPERATURE_SENSOR_H
#define TEMPERATURE_SENSOR_H
#include "header.hpp"
#include "sensor.hpp"

using namespace std;

class temperatureSensor : public Sensor {
    private:
    float temperature;
    public:
    //forme canononique coplien
    temperatureSensor();
    temperatureSensor(int id, string type, float temperature, class server *serverPtr);
    temperatureSensor(const temperatureSensor &s);
    temperatureSensor &operator=(const temperatureSensor &s);
    ~temperatureSensor();

    //methodes
    string generateMeasurement() override;
    Sensor* clone() const override;
};
#endif