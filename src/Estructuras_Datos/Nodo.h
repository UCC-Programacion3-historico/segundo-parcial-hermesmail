//
// Created by nelon on 27/10/2017.
//

#ifndef MAILMANAGER_NODO_H
#define MAILMANAGER_NODO_H

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

#endif //MAILMANAGER_NODO_H