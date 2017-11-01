#include "email.h"

#include <iostream>
#include <fstream>
#include "email.h"

bool email::operator==(const email &E) {
    return (this->id == E.id);
}

bool email::operator!=(const email &E) {
    return (this->id != E.id);
}

//Funcion que devuelve un objeto de tipo Email a partir del archivo txt donde se almacena
email LeeEmail(string nombre_txt) {
    nombre_txt = "../Emails/" + nombre_txt + ".txt";
    ifstream txt(nombre_txt, ifstream::in);

    if (!txt.is_open())
        throw -1;

    email R;
    string tmp[5];
    int i = 0;
    while (!txt.eof()) {
        getline(txt, tmp[i]);
        i++;
    }   // obligatoriamente cada campo tiene que estar en una unica linea

    R.id = atoi(tmp[0].c_str());
    R.from = tmp[1];
    R.to = tmp[2];
    R.date = tmp[3];
    R.content = tmp[4];

    txt.close();
    return R;
}


