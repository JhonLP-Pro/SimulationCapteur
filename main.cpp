#include "header.hpp"
#include "temperatureSensor.hpp"
#include "humiditySensor.hpp"
#include "lightSensor.hpp"
#include "soundSensor.hpp"
#include "scheduler.hpp"
#include "server.hpp"
#include <csignal>

volatile sig_atomic_t stopRequested = 0;

void handleInterrupt(int) {
    stopRequested = 1;
}

int main() {
    // Instanciation du serveur
    server myServer;

    // Instanciation des capteurs
    Sensor* sensor1 = new temperatureSensor(1, "Temperature", 25.0f, &myServer);
    Sensor* sensor2 = new humiditySensor(2, "Humidite", 60.0f, &myServer);
    Sensor* sensor3 = new lightSensor(3, "Etat lumière", true, &myServer);
    Sensor* sensor4 = new soundSensor(4, "Son", 50.0f, &myServer);
    
    // Instanciation de l'ordonnanceur et ajout des capteurs
    scheduler myScheduler;
    myScheduler.addSensor(sensor1);
    myScheduler.addSensor(sensor2);
    myScheduler.addSensor(sensor3);
    myScheduler.addSensor(sensor4);

    signal(SIGINT, handleInterrupt);
    cout << "Simulation en cours. Appuyez sur Ctrl+C pour arrêter." << endl;

    int tick = 0;
    while (!stopRequested && tick < 20) { // Limite à 20 ticks pour éviter une boucle infinie
        myScheduler.simulate(tick++);
        this_thread::sleep_for(chrono::seconds(1));
    }

    if (stopRequested) {
        cout << "\nArrêt demandé par l'utilisateur." << endl;
    } else {
        cout << "Nombre maximal de tours atteint." << endl;
    }

    myServer.writeSummaryToFiles();
    cout << "Simulation arrêtée proprement. Les mesures sont enregistrées dans le dossier build/." << endl;

    return 0;
}
