#include "email.h"

void email::imprimir() {
    cout << endl << id << endl << from << endl << to << endl << gringa(date) << endl << subject << endl << content
         << endl;
}

bool email::operator==(const email &E) {
    return (this->id == E.id);
}

bool email::operator!=(const email &E) {
    return (this->id != E.id);
}

void email::operator=(const email &E) {
    id = E.id;
    from = E.from;
    to = E.to;
    date = E.date;
    subject = E.subject;
    content = E.content;
}

string email::gringa(string O) {
    string R = "";
    R += O[6];
    R += O[7];
    R += "/";
    R += O[4];
    R += O[5];
    R += "/";
    R += O[0];
    R += O[1];
    R += O[2];
    R += O[3];
    R += " ";
    R += O[8];
    R += O[9];
    R += ':';
    R += O[10];
    R += O[11];
    R += ':';
    R += O[12];
    R += O[13];
    return R;
}