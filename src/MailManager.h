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
    //metodo que calcula el bobfara a 9 de un numero

    string corrige(string);
    //metodo que filtra los caracteres que no son letras ni numeros

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