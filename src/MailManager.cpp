#include "MailManager.h"
#include "Estructuras_Datos/ArbolBinario.h"

/**
 * Constructor
 */
MailManager::MailManager() {

}


/**
 * Agrega un mail al gestor
 * @param m mail a agregar
 */
void MailManager::addMail(email m) {
    lista_Emails.insertarPrimero(m);
    arbol_Remitentes.put(m.from, lista_Emails.getInicio());

    string tmp = m.subject + ' ' + m.content;
    ArbolBinario<string> lasPalabras;
    for (int i = 0; tmp[i] != nullptr; ++i) {
        string palabra = nullptr;
        while (tmp[i] != ' ') {
            //may min puntos etc.
            palabra += tmp[i];
            i++;
        }
        if (palabra != nullptr)
            lasPalabras.put(palabra);
    }
    Cola<string> colaPalabras;
    lasPalabras.encola_preorden(colaPalabras);
    while (!colaPalabras.esVacia())
        arbol_Diccionario.put(colaPalabras.desencolar(), lista_Emails.getInicio());

    //FALTA VER SI HASH O ARBOL PARA LAS FECHAS
}


/**
 * Elimina un mail del gestor
 * @param id identificador del mail a borrar
 */
void MailManager::deleteMail(unsigned long id) {

}


/**
 * Devuelve una lista de mails ordenados por fecha
 * @return lista de mails ordenados
 */
vector<email> MailManager::getSortedByDate() {
    vector<email> ret;
    return ret;
}


/**
 * Devuelve una lista de mails oredenados por fecha que estan en el rango
 * desde - hasta
 * @param desde Fecha desde donde buscar
 * @param hasta Fecha hasta donde buscar
 * @return lista de mails ordenados
 */
vector<email> MailManager::getSortedByDate(string desde, string hasta) {
    vector<email> ret;
    return ret;
}


/**
 * Devuelve una lista de mails ordenados por Remitente
 * @return lista de mails ordenados
 */
vector<email> MailManager::getSortedByFrom() {
    vector<email> ret;
    Cola<email> tmp;
    arbol_Remitentes.inorder(tmp);
    while (!tmp.esVacia())
        ret.push_back(tmp.desencolar());
    return ret;
    ///REVISAR
}


/**
 * Devuelve una lista de mails de un determinado remitente
 * @param from String con direccion del remitente
 * @return lista de mails del remitente
 */
vector<email> MailManager::getByFrom(string from) {
    vector<email> ret;
    return ret;
}


/**
 * Devuelve una lista de mails que contengan las palabras de 'query'
 * en su asunto o en su contenido
 * @param query String con palabra/s a buscar
 * @return lista de mails que contienen dicha/s palabra/s
 */
vector<email> MailManager::getByQuery(string query) {
    vector<email> ret;
    return ret;
}