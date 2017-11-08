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
    Nodo<email> *tmpInicio = lista_Emails.getInicio();
    arbol_ID.put(m.id, tmpInicio);
    arbol_Remitentes.put(corrige(m.from), tmpInicio);
    arbol_Fecha.put(bobfara(m.date), tmpInicio);

    string tmpTexto = m.subject + ' ' + m.content + ' ' + '\0';
    tmpTexto=corrige(tmpTexto);
    int i = 0;
    while (tmpTexto[i] != '\0') {
        string palabra = "";
        while ((tmpTexto[i] >= '0' && tmpTexto[i] <= '9') || (tmpTexto[i] >= 'A' && tmpTexto[i] <= 'Z') ||
               (tmpTexto[i] >= 'a' && tmpTexto[i] <= 'z')) {
            palabra += tmpTexto[i];
            i++;
        }
        if (palabra != "")
            arbol_Diccionario.put(palabra, tmpInicio);
        i++;
    }
}


/**
 * Elimina un mail del gestor
 * @param id identificador del mail a borrar
 */
void MailManager::deleteMail(unsigned long id) {
    Nodo<email> *aEliminar = arbol_ID.getLista(id).getInicio()->getDato();
    //apunta al que queremos eliminar de la lista principal
    string tmpFecha = bobfara(aEliminar->getDato().date);
    string tmpRemitente = corrige(aEliminar->getDato().from);

    arbol_Fecha.remove(tmpFecha, aEliminar);
    arbol_Remitentes.remove(tmpRemitente, aEliminar);

    string tmpTexto = aEliminar->getDato().subject + ' ' + aEliminar->getDato().content + ' ' + '\0';
    int i = 0;
    tmpTexto=corrige(tmpTexto);
    while (tmpTexto[i] != '\0') {
        string palabra = "";
        while ((tmpTexto[i] >= '0' && tmpTexto[i] <= '9') || (tmpTexto[i] >= 'A' && tmpTexto[i] <= 'Z') ||
               (tmpTexto[i] >= 'a' && tmpTexto[i] <= 'z')) {
            palabra += tmpTexto[i];
            i++;
        }
        if (palabra != "")
            try {
                arbol_Diccionario.remove(palabra, aEliminar);
            } catch (int e) {}
        i++;
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
    vector<Nodo<email> *> tmp;
    arbol_Fecha.inorder(tmp);
    unsigned long size = tmp.size();
    for (int i = 0; i < size; ++i) {
        ret.push_back(tmp[size - 1 - i]->getDato());
    }
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
    if (atoi(hasta.c_str()) < atoi(desde.c_str()))          //hasta es menor a desde
        throw -8;
    vector<Nodo<email> *> tmp;
    vector<email> ret;
    arbol_Fecha.inorderRango(tmp, bobfara(desde), bobfara(hasta));
    unsigned long size = tmp.size();
    for (int i = 0; i < size; ++i)
        ret.push_back(tmp[size - 1 - i]->getDato());
    return ret;
}


/**
 * Devuelve una lista de mails ordenados por Remitente
 * @return lista de mails ordenados
 */
vector<email> MailManager::getSortedByFrom() {
    vector<email> ret;
    vector<Nodo<email> *> tmp;
    arbol_Remitentes.inorder(tmp);
    for (int i = 0; i < tmp.size(); ++i)
        ret.push_back(tmp[i]->getDato());
    return ret;
}


/**
 * Devuelve una lista de mails de un determinado remitente
 * @param from String con direccion del remitente
 * @return lista de mails del remitente
 */
vector<email> MailManager::getByFrom(string from) {
    vector<email> ret;
    from = corrige(from);
    Nodo<Nodo<email> *> *R = arbol_Remitentes.getLista(from).getInicio();
    while (R != nullptr) {
        ret.push_back(R->getDato()->getDato());
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
    query = corrige(query);
    Nodo<Nodo<email> *> *R = arbol_Diccionario.getLista(query).getInicio();
    while (R != nullptr) {
        ret.push_back(R->getDato()->getDato());
        R = R->getNext();
    }
    return ret;
}


string MailManager::bobfara(string c) {
    string R = "";
    for (int i = 0; i < 8; ++i)
        R += c[i];
    return R;
}

string MailManager::corrige(string tmpTexto) {
    string R = "";
    //int cantC = 7;
    int cantC = 6;
    char espaniol[cantC] = {'\160', '\130', '\161', '\162', '\163', /*'\129',*/ '\164'};
    char noespaniol[cantC] = {'a', 'e', 'i', 'o', 'u', /*'u',*/ 'n'};
    for (int i = 0; i < tmpTexto.length(); ++i) {
        for (int j = 0; j < cantC; ++j) {
            if (R[i] == espaniol[j])
                R[i] = noespaniol[j];
        }
        R += tolower(tmpTexto[i]);
    }

    return R;
}
