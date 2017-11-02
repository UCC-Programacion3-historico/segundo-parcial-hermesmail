#include "MailManager.h"

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
    arbol_ID.put(m.id, tmpInicio);
    arbol_Remitentes.put(m.from, tmpInicio);
    arbol_Fecha.put(bobfara(m.date), tmpInicio);

    string tmp = m.subject + ' ' + m.content;
    for (int i = 0; tmp[i] != '\0'; ++i) {
        string palabra = nullptr;
        while (tmp[i] != ' ' || tmp[i] != '\0') {
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
    Nodo<email> *aEliminar = arbol_ID.getLista(id).getInicio()->getDato();    //apunta al eliminar de la lista principal
    string tmpFecha = bobfara(aEliminar->getDato().date);
    string tmpRemitente = aEliminar->getDato().from;
    string tmpTexto = aEliminar->getDato().subject + ' ' + aEliminar->getDato().content;

    arbol_Fecha.remove(tmpFecha, aEliminar);
    arbol_Remitentes.remove(tmpRemitente, aEliminar);


    for (int i = 0; tmpTexto[i] != '\0'; ++i) {
        string palabra = nullptr;
        while (tmpTexto[i] != ' ' || tmpTexto[i] != '\0') {
            //may min puntos etc.
            palabra += tmpTexto[i];
            i++;
        }
        arbol_Diccionario.remove(palabra, aEliminar);
    }
    arbol_ID.remove(id, aEliminar);
    lista_Emails.remover(aEliminar->getDato());
}


/**
 * Devuelve una lista de mails ordenados por fecha
 * @return lista de mails ordenados
 */
vector<email> MailManager::getSortedByDate() {
    vector<email> ret;
    arbol_Fecha.inorder(ret);
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
    vector<email> ret;
    arbol_Fecha.inorderRango(ret, bobfara(desde), bobfara(hasta));
    return ret;
}


/**
 * Devuelve una lista de mails ordenados por Remitente
 * @return lista de mails ordenados
 */
vector<email> MailManager::getSortedByFrom() {
    vector<email> ret;
    arbol_Remitentes.inorder(ret);
    return ret;
}


/**
 * Devuelve una lista de mails de un determinado remitente
 * @param from String con direccion del remitente
 * @return lista de mails del remitente
 */
vector<email> MailManager::getByFrom(string from) {
    vector<email> ret;
    Nodo<email> *R = arbol_Remitentes.getLista(from).getInicio()->getDato();      //que devuelva solo el puntero a nodo
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
    Nodo<email> *R = arbol_Diccionario.getLista(query).getInicio()->getDato();
    while (R != nullptr) {
        ret.push_back(R->getDato());
        R = R->getNext();
    }
    return ret;
}


string MailManager::bobfara(string c) {
    char num[] = {'9', '8', '7', '6', '5', '4', '3', '2', '1', '0'};
    for (int i = 0; i < 8; ++i)
        c[i] = num[int(c[(i)])];
    c[9] = '\0';
    return c;
}
