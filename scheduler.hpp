/*L’ordonnanceur, implemente dans la classe Scheduler, gere l’animation des processus, leur
donne une activation suivant une base de temps pr´ed´efinie. Dans cette classe, vous allez
d´efinir une fonction simulation qui organise le s´equencement de l’execution des processus
(capteurs) via leur methode update. Seuls les capteurs sont des processus, neanmoins
on peut se poser la question pour le serveur selon les choix de realisation. La fonction
simulation doit permettre aux capteurs de recuperer les informations de mesure et de les
retourner au serveur dedie.*/

#include "header.hpp"
#ifndef scheduler_H
#define scheduler_H
#include "sensor.hpp"
#include <vector>
using namespace std;

class scheduler{
    private:
    std::vector<Sensor*> sensors;
    public:
    //forme canonique coplien
    scheduler();
    scheduler(const scheduler &s);
    scheduler &operator=(const scheduler &s);
    ~scheduler();
    
    //methodes
    void addSensor(Sensor* sensor);
    void simulate(int tick);

};
#endif // scheduler_H