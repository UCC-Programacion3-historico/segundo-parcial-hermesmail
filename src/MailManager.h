#include <string>
#include <vector>
#include "email.h"
#include "Estructuras_Datos/Lista.h"
#include "Estructuras_Datos/ArbolConLista.h"

#ifndef MAILMANAGER_H
#define MAILMANAGER_H

using namespace std;

//typedef struct {
//    string remitente;
//    Lista<email *> listaEmails;
//} DatoRemitente;
//// dato del nodo del arbol para que guarde el remitente y una lista que tenga los punteros a los emails de dicho remitente
//
//typedef struct {
//    string palabra;
//    Lista<email *> listaEmails;
//} DatoPalabra;
//// dato del nodo del arbol para que guarde las palabras y una lista de los emails que contienen dicha palabra
//
//typedef struct {
//    string fecha;
//    Lista<email *> listaEmails;
//} DatoFecha;
//// dato del nodo del arbol/hash que guarda las fechas y una lista de los emails que contienen dicha fecha

class MailManager {
private:
    Lista<email> lista_Emails;
    //Lista enlazada que almacena un listado de los mails agregados
    ArbolBinarioConLista<string, email> arbol_Remitentes;
    //Arbol binario que almacena ordenando los remitentes alfabeticamente
    ArbolBinarioConLista<string, email> arbol_Diccionario;
    //Arbol binario que almacena las palabras de los emails alfabeticamente

    /*Aca iria el hash/arbol de fechas*/

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