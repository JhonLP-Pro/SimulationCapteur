#ifndef HUMIDITY_SENSOR_H
#define HUMIDITY_SENSOR_H
#include "header.hpp"
#include "sensor.hpp"

using namespace std;

class humiditySensor : public Sensor {
    private:
    float humidity;
    public:
    //forme canononique coplien
    humiditySensor();
    humiditySensor(int id, string type, float humidity, class server *serverPtr);
    humiditySensor(const humiditySensor &s);
    humiditySensor &operator=(const humiditySensor &s);
    ~humiditySensor();

    //methodes
    string generateMeasurement() override;
    Sensor* clone() const override;
};
#endif