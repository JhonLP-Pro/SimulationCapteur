/*Votre premi`ere tˆache consistera `a cr´eer un squellette succinct de programme avec ces
diff´erentes classes, un main. On commencera par d´etailler la classe ”Server”. Cette classe
doit nous permettre de recevoir des donn´ees envoy´ees par l’ensemble des capteurs, de les
analyser, de les formater, puis de stocker les informations utiles dans des fichiers de logs
ou encore de les visualiser dans la console.*/
#ifndef SERVER_H
#define SERVER_H
#include "header.hpp"
#include <algorithm>
#include <stdexcept>

using namespace std;

class server{
    private:
    struct MeasurementStats {
        int count = 0;
        int numericCount = 0;
        double sum = 0.0;
        double minimum = 0.0;
        double maximum = 0.0;
        int trueCount = 0;
        int falseCount = 0;
    };

    bool consoleEnabled;
    map<string, MeasurementStats> statistics;
    string currentDateTime() const;
    void updateStatistics(const string &type, const string &measurement);

    public:
    //forme canononique coplien
    server();
    server(const server &s);
    server &operator=(const server &s);
    ~server();

    //methodes
    void consoleWrite(string data);
    void fileWrite(string type, string data);
    void writeSummaryToFiles() const;

    friend ostream &operator<<(ostream &os, const server &s);
};
#endif // SERVER_H
