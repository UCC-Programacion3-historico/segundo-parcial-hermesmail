//
// Created by nelon on 27/10/2017.
//

#ifndef MAILMANAGER_NODO_H
#define MAILMANAGER_NODO_H

template<class T>
class Nodo {
private:
    T dato;
    Nodo<T> *next;
public:
    Nodo() { next = nullptr; }

    Nodo(T d, Nodo<T> *n) {
        dato = d;
        next = n;
    }

    void setDato(T d) { dato = d; }

    void setNext(Nodo<T> *n) { next = n; }

    T getDato() { return dato; }

    Nodo<T> *getNext() { return next; }
};

#endif //MAILMANAGER_NODO_H