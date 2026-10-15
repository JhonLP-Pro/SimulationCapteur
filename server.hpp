/*Votre premi`ere tˆache consistera `a cr´eer un squellette succinct de programme avec ces
diff´erentes classes, un main. On commencera par d´etailler la classe ”Server”. Cette classe
doit nous permettre de recevoir des donn´ees envoy´ees par l’ensemble des capteurs, de les
analyser, de les formater, puis de stocker les informations utiles dans des fichiers de logs
ou encore de les visualiser dans la console.*/
#ifndef SERVER_H
#define SERVER_H
#include "header.hpp"

using namespace std;

class server{
    private:
    ofstream data;
    bool consoleEnabled;
    map<string, string> latestMeasurements;
    string currentDateTime() const;
    public:
    //forme canononique coplien
    server();
    server(const server &s);
    server &operator=(const server &s);
    ~server();

    //methodes
    void consoleWrite(string data);
    void fileWrite(string type, string data);

    friend ostream &operator<<(ostream &os, const server &s);
};
#endif // SERVER_H
