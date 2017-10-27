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
    Nodo<email> *tmpInicio = lista_Emails.getInicio();      //para evitar llamadas a metodos
    arbol_Remitentes.put(m.from, tmpInicio);
    arbol_Fecha.put(m.date, tmpInicio);

    string tmp = m.subject + ' ' + m.content;
    for (int i = 0; i < tmp[i] != nullptr; ++i) {
        string palabra = nullptr;
        while (tmp[i] != ' ') {
            //may min puntos etc.
            palabra += tmp[i];
            i++;
        }
        arbol_Diccionario.put(palabra, tmpInicio);
    }
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
    Cola<email> tmp;
    arbol_Fecha.inorder(tmp);
    while (!tmp.esVacia())
        ret.push_back(tmp.desencolar());
    //ret.insert()
    return ret;
    ///REVISAR
}


/**
 * Devuelve una lista de mails oredenados por fecha que estan en el rango
 * desde - hasta
 * @param desde Fecha desde donde buscar
 * @param hasta Fecha hasta donde buscar
 * @return lista de mails ordenados
 */
vector<email> MailManager::getSortedByDate(string desde, string hasta) {

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
    Nodo<email> *R = arbol_Remitentes.getLista(from).getInicio();           //que devuelva solo el puntero a nodo
    while (R != nullptr) {
        ret.push_back(R->getDato());
        R = R->getNext();
    }
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