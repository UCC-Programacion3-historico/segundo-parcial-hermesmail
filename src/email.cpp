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

//string email::gringa(string O) {
//    string R = "";
//    R += O[6] + O[7] + '/' + O[4] + O[5] + '/' + O[0] + O[1] + O[2] + O[3] + ' ' + O[8] + O[9] + ':' + O[10] + O[11] +
//         ':' + O[12] + O[13];
//    return  R;
//}