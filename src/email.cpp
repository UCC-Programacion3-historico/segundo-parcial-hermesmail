#include "email.h"

void email::imprimir(bool mostID, bool mostContenido) {
    if (mostID)cout << endl << id;
    cout << endl << from << endl << to << endl << date << endl << subject << endl;
    if (mostContenido)cout << content << endl;
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
