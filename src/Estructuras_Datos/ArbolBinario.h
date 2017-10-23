//
// Created by nelon on 23/10/2017.
//

#ifndef MAILMANAGER_ARBOLBINARIO_H
#define MAILMANAGER_ARBOLBINARIO_H

#include "Cola.h"

template<class T>
class NodoArbol {
private:
    NodoArbol<T> *izq, *der;
    T dato;
public:
    NodoArbol(T);

    T getDato();

    void put(T);

    NodoArbol<T> *remover(T d);

    void inorder(); //ver tipo de retorno

    void encola_preorden(Cola<T> &);
};

template<class T>
NodoArbol<T>::NodoArbol(T dato) {
    this->dato = dato;
    izq = nullptr;
    der = nullptr;
}

template<class T>
T NodoArbol<T>::getDato() {
    return dato;
}

template<class T>
void NodoArbol<T>::put(T d) {
    if (d == dato)throw 1;
    if (d < dato) {
        if (izq == nullptr) {
            izq = new NodoArbol<T>(d);
        } else {
            izq->put(d);
        }
    } else {
        if (der == nullptr) {
            der = new NodoArbol<T>(d);
        } else {
            der->put(d);
        }
    }
}

template<class T>
void NodoArbol<T>::put(NodoArbol<T> *nodo) {
    if (nodo->getDato() == dato)throw 1;
    if (nodo->getDato() < dato) {
        if (izq == nullptr) {
            izq = new NodoArbol<T>(nodo->getDato());
        } else {
            izq->put(nodo);
        }
    } else {
        if (der == nullptr) {
            der = new NodoArbol<T>(nodo->getDato());
        } else {
            der->put(nodo);
        }
    }
}

template<class T>
NodoArbol<T> *NodoArbol<T>::remover(T d) {
    NodoArbol<T> *aux;
    if (d == dato) {
        if (der != nullptr) {
            der->put(izq);
            return der;
        }
        return izq;
    }
    if (d < dato) {
        if (izq == nullptr)throw 1;
        aux = izq;
        izq = izq->remover(d);
        if (izq != aux)delete aux;
    } else {
        if (der == nullptr)throw 1;
        aux = der;
        der = der->remover(d);
        if (der != aux)delete aux;
    }
    return this;
}

template<class T>
void NodoArbol<T>::inorder() {
    if (izq != nullptr)izq->inorder();
    //cout << dato << ", ";
    if (der != nullptr)der->inorder();
}

template<class T>
void NodoArbol<T>::encola_preorden(Cola<T> &R) {
    R.encolar(this->dato);
    if (izq != nullptr) izq->encola_preorden(R);
    if (der != nullptr) der->encola_preorden(R);
}

template<class T>
class ArbolBinario {
private:
    NodoArbol<T> *raiz;
public:
    ArbolBinario();

    ~ArbolBinario();

    void put(T dato);

    void remove(T dato);

    void inorder();

    bool esVacio();

    void encola_preorden(Cola<T> &);
};

template<class T>
ArbolBinario<T>::ArbolBinario() {
    raiz = nullptr;
}

template<class T>
ArbolBinario<T>::~ArbolBinario() {

}

template<class T>
void ArbolBinario<T>::put(T dato) {
    if (raiz == nullptr)
        raiz = new NodoArbol<T>(dato);
    else
        raiz->put(dato);
}

template<class T>
void ArbolBinario<T>::remove(T dato) {
    NodoArbol<T> *aux;
    if (raiz == nullptr)
        throw 6;
    aux = raiz;
    raiz = raiz->remover(dato);
    if (raiz != aux)        //si se quiere eliminar la raiz no hay padre para borrar el aux
        delete aux;
}

template<class T>
void ArbolBinario<T>::inorder() {
    if (raiz != nullptr)
        raiz->inorder();
}

template<class T>
bool ArbolBinario<T>::esVacio() {
    return raiz == nullptr;
}

template<class T>
void ArbolBinario<T>::encola_preorden(Cola<T> &R) {
    if (raiz != nullptr)
        raiz->encola_preorden(R);
}

#endif //MAILMANAGER_ARBOLBINARIO_H
