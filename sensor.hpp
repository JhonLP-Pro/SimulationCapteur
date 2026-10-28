/*Pour repr´esenter les donn´ees sp´ecifiques `a chaque capteur, la classe Sensor devra inclure, en tant qu’attributs, un identifiant unique du capteur, un type par d´efaut (via
une ”string”), une donn´ee pour la valeur du capteur, ainsi qu’un pointeur vers le Server
d´edi´e*/
#include "header.hpp"
#ifndef SENSOR_H
#define SENSOR_H
#include "server.hpp"


class Sensor{
    private:
    int id;
    string type;
    server *serverPtr;
    int currentTime;
    public:
    // Forme canonique coplienne
    Sensor();
    Sensor(int id, string type, double value, class server *serverPtr);
    Sensor(const Sensor &s);
    Sensor &operator=(const Sensor &s);
    virtual ~Sensor();

    // Méthodes
    void update(int time);
    virtual void execute();
    virtual string generateMeasurement() = 0; // Méthode virtuelle pure pour générer une mesure spécifique au capteur
    virtual Sensor* clone() const = 0; 
};

#endif // SENSOR_H