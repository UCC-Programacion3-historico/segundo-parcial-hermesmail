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
    Lista<email> lista_Emails;
    //Lista enlazada que almacena un listado de los mails agregados
    ArbolBinarioConLista<unsigned long, email> arbol_ID;
    //Arbol binario que almacena los IDs de los emails ordenandos de menor a mayor
    ArbolBinarioConLista<string, email> arbol_Remitentes;
    //Arbol binario que almacena los remitentes de los emails ordenandos alfabeticamente
    ArbolBinarioConLista<string, email> arbol_Diccionario;
    //Arbol binario que almacena las palabras de los emails ordenandos alfabeticamente
    ArbolBinarioConLista<string, email> arbol_Fecha;
    //Arbol binario que almacena las fechas de los emails ordenandos cronologicamente

    string bobfara(string);
    //funcion que calcula el bobfara a 9 de un numero

public:
    MailManager();

    // Métodos de uso
    void addMail(email m);

    void deleteMail(unsigned long id);

    vector<email> getSortedByDate();

    vector<email> getSortedByDate(string desde, string hasta);

    vector<email> getSortedByFrom();

    vector<email> getByFrom(string from);

    vector<email> getByQuery(string query);
};

#endif // MAILMANAGER_H