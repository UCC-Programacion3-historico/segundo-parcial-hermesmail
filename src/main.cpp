#include <iostream>
#include <fstream>
#include "MailManager.h"

//Funcion que devuelve un objeto de tipo Email a partir del archivo txt donde se almacena
email LeeEmail(string nombre_txt) {
    nombre_txt = "../Emails/" + nombre_txt + ".txt";
    ifstream txt(nombre_txt, ifstream::in);

    if (!txt.is_open())
        throw -1;

    email R;
    string tmp[6];
    int i = 0;
    while (!txt.eof()) {
        getline(txt, tmp[i]);
        i++;
    }   // obligatoriamente cada campo tiene que estar en una unica linea
//    for (int j = 1; j < 5; ++j) {
//        tmp[j][tmp[j].length()-1]='\0';
//    }
    R.id = atoi(tmp[0].c_str());
    R.from = tmp[1];
    R.to = tmp[2];
    R.date = tmp[3];
    R.subject = tmp[4];
    R.content = tmp[5];

    txt.close();
    return R;
}

int main() {
    std::cout << "Super gestor de mails" << std::endl;
    MailManager MM;

    email prueba = LeeEmail("email000");

    MM.addMail(prueba);
    vector<email> v = MM.getSortedByDate();
    cout << v[0].date << endl;
    vector<email> v2 = MM.getSortedByFrom();
    cout << v2[0].from << endl;
    v2 = MM.getByFrom("Zeus\r");
    cout << v2[0].from << endl;
    vector<email> v3 = MM.getByQuery("necesita");
    cout << v3[0].content << endl;
    vector<email> v4 = MM.getSortedByDate("20171015", "20171102");
    cout << v4[0].subject << endl;
    v4 = MM.getSortedByDate("20180101", "20190101");
    cout << v4.empty() << endl;
    v4 = MM.getSortedByDate();
    cout << v4[0].subject << endl;
    MM.deleteMail(000);
    cout << "hola";
    return 0;
}