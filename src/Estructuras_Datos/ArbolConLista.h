//
// Created by nelon on 23/10/2017.
//

#ifndef MAILMANAGER_ARBOL_H
#define MAILMANAGER_ARBOL_H

#include "Cola.h"
#include "NodoArbolConLista.h"

template<class T, class K>
class ArbolBinarioConLista {
private:
    NodoArbolConLista<T, K> *raiz;
public:
    ArbolBinarioConLista();

    ~ArbolBinarioConLista();

    void put(T, Nodo<K> *);

    void remove(T);

    void inorder(Cola<K> &);

    void inorderRango(Cola<K> &, string, string);

    bool esVacio();

    Lista<Nodo<K> *> &getLista(T);
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
void ArbolBinarioConLista<T, K>::inorder(Cola<K> &R) {
    if (raiz != nullptr)
        raiz->inorder(R);
}

template<class T, class K>
void ArbolBinarioConLista<T, K>::inorderRango(Cola<K> &R,string desde,string hasta) {
    if (raiz != nullptr)
        raiz->inorderRango(R,desde,hasta);
}

template<class T, class K>
bool ArbolBinarioConLista<T, K>::esVacio() {
    return raiz == nullptr;
}

template<class T, class K>
Lista<Nodo<K> *> &ArbolBinarioConLista<T, K>::getLista(T d) {
    if (raiz != nullptr)
        return raiz->getLista(d);
}

#endif //MAILMANAGER_ARBOL_H