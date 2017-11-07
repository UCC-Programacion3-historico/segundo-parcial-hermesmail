#include "email.h"

void email::imprimir() {
    cout << endl << id << endl << from << endl << to << endl << date << endl << subject << endl << content << endl;
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