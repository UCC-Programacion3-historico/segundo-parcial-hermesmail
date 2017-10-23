//
// Created by nelon on 23/10/2017.
//

#ifndef MAILMANAGER_ARBOL_H
#define MAILMANAGER_ARBOL_H

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
};


#endif //MAILMANAGER_ARBOL_H
