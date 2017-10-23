//
// Created by nelon on 23/10/2017.
//

#ifndef MAILMANAGER_ARBOL_H
#define MAILMANAGER_ARBOL_H

#include "Cola.h"

template<class T, class K>
class NodoArbolConLista {
private:
    NodoArbolConLista<T, K> *izq, *der;
    T dato;
    Lista<K *> listaPtr;
public:
    NodoArbolConLista(T, Nodo<K> *);

    T getDato();

    void put(T, Nodo<K> *);

    NodoArbolConLista<T, K> *remover(T d);

    void inorder(Cola<T> &); //ver tipo de retorno
};

template<class T, class K>
NodoArbolConLista<T, K>::NodoArbolConLista(T dato, Nodo<K> *ptr) {
    this->dato = dato;
    this->listaPtr.insertarPrimero(ptr);
    izq = nullptr;
    der = nullptr;
}

template<class T, class K>
T NodoArbolConLista<T, K>::getDato() {
    return dato;
}

template<class T, class K, class K>
void NodoArbolConLista<T, K>::put(T d, Nodo<K> *ptr) {
    if (d == dato) {
        this->listaPtr.insertarPrimero(ptr);
    } else {
        if (d < dato) {
            if (izq == nullptr) {
                izq = new NodoArbolConLista<T, K>(d, ptr);
            } else {
                izq->put(d, ptr);
            }
        } else {
            if (der == nullptr) {
                der = new NodoArbolConLista<T, K>(d, ptr);
            } else {
                der->put(d, ptr);
            }
        }
    }
}

template<class T, class K>
NodoArbolConLista<T, K> *NodoArbolConLista<T, K>::remover(T d) {
    NodoArbolConLista<T, K> *aux;
    if (d == dato) {
        if (der != nullptr) {
            der->put(izq, nullptr);                     // ATENCION OJO AL PIOJO
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

template<class T, class K>
void NodoArbolConLista<T, K>::inorder(Cola<T> &R) {
    if (izq != nullptr)izq->inorder(R);
    for (unsigned int i = 0; !this->listaPtr.esVacia(); ++i)
        R.encolar(listaPtr.getDato(i));
    if (der != nullptr)der->inorder(R);
};


template<class T, class K>
class ArbolBinarioConLista {
private:
    NodoArbolConLista<T, class K> *raiz;
public:
    ArbolBinarioConLista();

    ~ArbolBinarioConLista();

    void put(T, Nodo<K> *);

    void remove(T);

    void inorder(Cola<T> &);

    bool esVacio();
};

template<class T, class K>
ArbolBinarioConLista<T, K>::ArbolBinarioConLista() {
    raiz = nullptr;
}

template<class T, class K>
ArbolBinarioConLista<T, K>::~ArbolBinarioConLista() {

}

template<class T, class K>
void ArbolBinarioConLista<T, K>::put(T dato, Nodo<K> *ptr) {
    if (raiz == nullptr) {
        raiz = new NodoArbolConLista<T, K>(dato, ptr);
    } else {
        raiz->put(dato, ptr);
    }
}

template<class T, class K>
void ArbolBinarioConLista<T, K>::remove(T dato) {
    NodoArbolConLista<T, K> *aux;
    if (raiz == nullptr)throw 1;
    aux = raiz;
    raiz = raiz->remover(dato);
    if (raiz != aux)
        delete aux;
}

template<class T, class K>
void ArbolBinarioConLista<T, K>::inorder(Cola<T> &R) {
    if (raiz != nullptr)
        raiz->inorder(R);
}

template<class T, class K>
bool ArbolBinarioConLista<T, K>::esVacio() {
    return raiz == nullptr;
}


#endif //MAILMANAGER_ARBOL_H
