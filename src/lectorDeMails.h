//
// Created by nelon on 10/11/2017.
//

#ifndef MAILMANAGER_LECTORDEMAILS_H
#define MAILMANAGER_LECTORDEMAILS_H

#include <iostream>
#include <fstream>
#include <vector>
#include "email.h"

using namespace std;

vector<string> split(const string &s, char delim) {
    vector<std::string> elems;
    unsigned long pos = s.find(delim);
    if (pos == string::npos)
        elems.push_back(s);
    else {
        elems.push_back(s.substr(0, pos));
        elems.push_back(s.substr(pos + 1, string::npos));
    }
    return elems;
}

string trim(string &str) {
    size_t first = str.find_first_not_of(' ');
    if (first == string::npos)
        return "";
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

vector<email> load_mm(string archivo) {
    string line;
    vector<email> mails;
    ifstream miArchivo(archivo);
    unsigned long indice = 0;
    vector<string> campos;
    email *mail = NULL;

    if (miArchivo.is_open()) {
        try {
            unsigned long c = 1;
            while (getline(miArchivo, line)) {
                campos = split(line, ':');
                if (campos.size() > 0) { // Es un dato completo
                    if (campos[0] == "-.-.-") {
                        if (mail != NULL)
                            mails.push_back(*mail);
                        mail = new email();
                        mail->content = "";
                    } else if (campos[0] == "date") {
                        mail->id = c;
                        c++;
                        mail->date = trim(campos[1]);
                    } else if (campos[0] == "from") {
                        mail->from = trim(campos[1]);
                    } else if (campos[0] == "to") {
                        mail->to = trim(campos[1]);
                    } else if (campos[0] == "subject") {
                        mail->subject = trim(campos[1]);
                    } else {
                        mail->content += line + "\n";
                    }
                }
            }
        } catch (int e) {
            cout << "error cargando mail\n";
        }
    } else
        cout << "No se pudo leer el archivo.";
    return mails;
}


#endif //MAILMANAGER_LECTORDEMAILS_H
