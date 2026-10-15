#ifndef LIGHT_SENSOR_H
#define LIGHT_SENSOR_H
#include "header.hpp"
#include "sensor.hpp"

using namespace std;

class lightSensor : public Sensor {
    private:
    bool lightstatus;
    public:
    //forme canononique coplien
    lightSensor();
    lightSensor(int id, string type, bool lightstatus, class server *serverPtr);
    lightSensor(const lightSensor &s);
    lightSensor &operator=(const lightSensor &s);
    ~lightSensor();

    //methodes
    string generateMeasurement() override;
    Sensor* clone() const override;
};
#endif