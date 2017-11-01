#include <string>

#ifndef EMAIL_H
#define EMAIL_H

using namespace std;

/**
 * Clase con los datos del mail
 */
class email {
public:
    unsigned long id;
    string from;
    string to;
    string date;
    string subject;
    string content;

    bool operator==(const email&);
};


#endif // EMAIL_H
