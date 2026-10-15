#ifndef SOUND_SENSOR_H
#define SOUND_SENSOR_H
#include "header.hpp"
#include "sensor.hpp"

using namespace std;

class soundSensor : public Sensor {
    private:
    float soundLevel;
    public:
    //forme canononique coplien
    soundSensor();
    soundSensor(int id, string type, float soundLevel, class server *serverPtr);
    soundSensor(const soundSensor &s);
    soundSensor &operator=(const soundSensor &s);
    ~soundSensor();

    //methodes
    string generateMeasurement() override;
    Sensor* clone() const override;
};
#endif