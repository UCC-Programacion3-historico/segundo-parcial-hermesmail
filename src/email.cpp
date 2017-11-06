#include "email.h"

//string email::fechear(string d) {
//    string R;
//}

void email::imprimir() {
    cout << endl<<id<<endl << from << endl << to << endl << date << endl << subject << endl << content << endl;
}

bool email::operator==(const email &E) {
    return (this->id == E.id);
}

bool email::operator!=(const email &E) {
    return (this->id != E.id);
}


