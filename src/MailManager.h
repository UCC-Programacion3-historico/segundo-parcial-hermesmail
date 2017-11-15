#include <string>
#include <vector>
#include "email.h"
#include "Estructuras_Datos/Lista.h"
#include "Estructuras_Datos/ArbolConLista.h"

#ifndef MAILMANAGER_H
#define MAILMANAGER_H

using namespace std;

class MailManager {
private:
    ArbolBinarioConLista<unsigned long, email *> arbol_ID;
    ArbolBinarioConLista<string, email *> arbol_Remitentes;
    ArbolBinarioConLista<string, email *> arbol_Diccionario;
    ArbolBinarioConLista<string, email *> arbol_Fecha;

    string bobfara(string);
    //metodo que corta strings

    bool fechaValida(string);
    //metodo que que valida fechas ingresadas


public:
    MailManager();

    void addMail(email m);

    void deleteMail(unsigned long id);

    vector<email> getSortedByDate();

    vector<email> getSortedByDate(string desde, string hasta);

    vector<email> getSortedByFrom();

    vector<email> getByFrom(string from);

    vector<email> getByQuery(string query);

    void printArbolIDs() {
        this->arbol_ID.print();
    }

    void printArbolFechas() {
        this->arbol_Fecha.print();
    }

    void printArbolRemitentes() {
        this->arbol_Remitentes.print();
    }

    void printArbolPalabras() {
        this->arbol_Diccionario.print();
    }
};

#endif // MAILMANAGER_H