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
     email* tmpInicio=new email;
     *tmpInicio=m;

    arbol_ID.put(m.id, tmpInicio);
    arbol_Remitentes.put(m.from, tmpInicio);
    arbol_Fecha.put(bobfara(m.date), tmpInicio);

    string tmpTexto = m.subject + ' ' + m.content + ' ' + '\0';
    int i = 0;
    while (tmpTexto[i] != '\0') {
        string palabra = "";
        while ((tmpTexto[i] >= '0' && tmpTexto[i] <= '9') || (tmpTexto[i] >= 'A' && tmpTexto[i] <= 'Z') ||
               (tmpTexto[i] >= 'a' && tmpTexto[i] <= 'z')) {
            palabra += tolower(tmpTexto[i]);
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
    email *aEliminar = arbol_ID.getLista(id).getInicio()->getDato();
    //apunta al que queremos eliminar de la lista principal
    string tmpFecha = bobfara(aEliminar->date);
    string tmpRemitente = aEliminar->from;
    arbol_Fecha.remove(tmpFecha, aEliminar);
    arbol_Remitentes.remove(tmpRemitente, aEliminar);

    string tmpTexto = aEliminar->subject + ' ' + aEliminar->content + ' ' + '\0';
    int i = 0;
    while (tmpTexto[i] != '\0') {
        string palabra = "";
        while ((tmpTexto[i] >= '0' && tmpTexto[i] <= '9') || (tmpTexto[i] >= 'A' && tmpTexto[i] <= 'Z') ||
               (tmpTexto[i] >= 'a' && tmpTexto[i] <= 'z')) {
            palabra += tolower(tmpTexto[i]);
            i++;
        }
        if (palabra != "")
            try {
                arbol_Diccionario.remove(palabra, aEliminar);
            } catch (int e) {}
        i++;
    }

    arbol_ID.remove(id, aEliminar);
    delete aEliminar;
}


/**
 * Devuelve una lista de mails ordenados por fecha
 * @return lista de mails ordenados
 */
vector<email> MailManager::getSortedByDate() {
    vector<email *> tmp;
    vector<email> ret;
    arbol_Fecha.inorder(tmp);
    unsigned long size = tmp.size();
    for (int i = 0; i < size; ++i) {
        ret.push_back(*tmp[size - 1 - i]);
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
    if (!fechaValida(desde) && !fechaValida(hasta))
        throw -50;
    if (!fechaValida(desde))
        throw -10;
    if (!fechaValida(hasta))
        throw -20;
    if (atoi(hasta.c_str()) < atoi(desde.c_str()))          //hasta es menor a desde
        throw -8;
    vector<email *> tmp;
    vector<email> ret;
    arbol_Fecha.inorderRango(tmp, bobfara(desde), bobfara(hasta));
    unsigned long size = tmp.size();
    for (int i = 0; i < size; ++i)
        ret.push_back(*tmp[size - 1 - i]);
    return ret;
}


/**
 * Devuelve una lista de mails ordenados por Remitente
 * @return lista de mails ordenados
 */
vector<email> MailManager::getSortedByFrom() {
    vector<email> ret;
    vector<email *> tmp;
    arbol_Remitentes.inorder(tmp);
    for (int i = 0; i < tmp.size(); ++i)
        ret.push_back(*tmp[i]);
    return ret;
}


/**
 * Devuelve una lista de mails de un determinado remitente
 * @param from String con direccion del remitente
 * @return lista de mails del remitente
 */
vector<email> MailManager::getByFrom(string from) {
    vector<email> ret;
    Nodo<email *> *R = arbol_Remitentes.getLista(from).getInicio();
    while (R != nullptr) {
        ret.push_back(*R->getDato());
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
    int i = 0;
    string palabra = "";

    while ((query[i] >= '0' && query[i] <= '9') || (query[i] >= 'A' && query[i] <= 'Z') ||
           (query[i] >= 'a' && query[i] <= 'z')) {
        palabra += tolower(query[i]);
        i++;
    }

    if (palabra != "") {
        Nodo<email *> *R = arbol_Diccionario.getLista(palabra).getInicio();
        while (R != nullptr) {
            ret.push_back(*R->getDato());
            R = R->getNext();
        }
    }
    return ret;
}


string MailManager::bobfara(string c) {
    string R = "";
    for (int i = 0; i < 10; ++i)
        R += c[i];
    return R;
}

bool MailManager::fechaValida(string fecha) {
    string d = "", m = "", a = "";
    d += fecha[6];
    d += fecha[7];
    m += fecha[4];
    m += fecha[5];
    a += fecha[0];
    a += fecha[1];
    a += fecha[2];
    a += fecha[3];
    if (d >= "01" && d <= "31" && m >= "01" && m <= "12") {
        if ((d < "29") || (m == "01") || (m == "03") || (m == "05") || (m == "07") || (m == "08") || (m == "10") ||
            (m == "12"))
            return true;
        else {
            if (d < "31" && m != "02")
                return true;
            else {
                if (atoi(a.c_str()) % 4 == 0 && d == "29")
                    return true;
                else
                    return false;
            }
        }
    } else
        return false;
}