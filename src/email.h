#include <string>
#include <iostream>

#ifndef EMAIL_H
#define EMAIL_H

using namespace std;

/**
 * Clase con los datos del mail
 */
class email {
private:
//    string fechear(string);

public:
    unsigned long id;
    string from;
    string to;
    string date;
    string subject;
    string content;

    void imprimir();

    bool operator==(const email &);

    bool operator!=(const email &);
};


#endif // EMAIL_H
