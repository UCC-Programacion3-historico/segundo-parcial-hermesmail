//
// Created by nelon on 23/10/2017.
//

#ifndef MAILMANAGER_LISTA_H
#define MAILMANAGER_LISTA_H

#include "Nodo.h"

template<class T>
class Lista {
private:
    Nodo<T> *inicio;
public:
    Lista();

    ~Lista();

    bool esVacia();

    Nodo<T> *getInicio() const;

    void insertarPrimero(T);

    void remover(T);

    void vaciar();
};


template<class T>
Lista<T>::Lista() {
    inicio = nullptr;
}

template<class T>
Lista<T>::~Lista() {
    vaciar();

}

template<class T>
void Lista<T>::vaciar() {
    Nodo<T> *borr;
    Nodo<T> *aux = inicio;

    while (aux != nullptr) {
        borr = aux;
        aux = aux->getNext();
        delete borr;
    }
    inicio = nullptr;
}

template<class T>
bool Lista<T>::esVacia() {
    return inicio == nullptr;
}

template<class T>
Nodo<T> *Lista<T>::getInicio() const {
    return inicio;
}

template<class T>
void Lista<T>::insertarPrimero(T dato) {
    Nodo<T> *nn = new Nodo<T>(dato, inicio);
    inicio = nn;
}

template<class T>
void Lista<T>::remover(T dato) {
    Nodo<T> *aux = inicio;
    if (aux == nullptr)
        throw -1;
    if (dato == inicio->getDato()) {
        inicio = inicio->getNext();
        delete aux;
        return;
    }

    while (aux->getNext() != nullptr && aux->getNext()->getDato() != dato) {
        aux = aux->getNext();
    }

    Nodo<T> *tmp = aux->getNext();

    if (tmp == nullptr) {
        throw -1;
    }

    aux->setNext(tmp->getNext());
    delete tmp;
}


#endif //MAILMANAGER_LISTA_H