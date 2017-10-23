//
// Created by nelon on 23/10/2017.
//

#ifndef MAILMANAGER_COLA_H
#define MAILMANAGER_COLA_H

template<class T>
class Nodo {
private:
    T dato;
    Nodo *next;
public:
    Nodo() { next = nullptr; }

    Nodo(T d, Nodo *n) {
        dato = d;
        next = n;
    }

    void setDato(T d) { dato = d; }

    void setNext(Nodo *n) { next = n; }

    T getDato() { return dato; }

    Nodo *getNext() { return next; }
};

template<class T>
class Cola {
private:
    Nodo<T> *frente;
    Nodo<T> *fondo;

public:
    Cola();

    ~Cola();

    void encolar(T dato);

    T desencolar();

    bool esVacia();

    void vaciar();

    T verFrente();
};

template<class T>
Cola<T>::Cola() {
    fondo = frente = nullptr;
}

template<class T>
Cola<T>::~Cola() {

}

template<class T>
void Cola<T>::encolar(T dato) {
    Nodo<T> *aux = new Nodo<T>(dato);

    if (fondo == nullptr && frente == nullptr) {
        frente = fondo = aux;
    } else {
        fondo->setNext(aux);
        fondo = aux;
    }
}

template<class T>
T Cola<T>::desencolar() {

    if (esVacia())
        throw 1;

    T tmp;
    Nodo<T> *aux = frente;

    frente = frente->getNext();
    tmp = aux->getDato();
    delete aux;

    if (frente == nullptr)
        fondo = frente;

    return tmp;
}

template<class T>
bool Cola<T>::esVacia() {
    return frente == nullptr;
}

template<class T>
void Cola<T>::vaciar() {

    while(frente != nullptr)
        desencolar();

}

template<class T>
T Cola<T>::verFrente() {
    if(esVacia())
        throw 404;
    return frente->getDato();
}

#endif //MAILMANAGER_COLA_H
