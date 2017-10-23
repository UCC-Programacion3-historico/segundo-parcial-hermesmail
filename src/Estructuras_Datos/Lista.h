//
// Created by nelon on 23/10/2017.
//

#ifndef MAILMANAGER_LISTA_H
#define MAILMANAGER_LISTA_H

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
class Lista {
private:
    Nodo<T> *inicio;
public:
    Lista();

    ~Lista();

    bool esVacia();

    int getTamanio();

    Nodo<T> *getInicio() const;

    void insertarPrimero(T dato);
    //Es mas eficiente insertar al principio que al final

    void remover(/*vaya uno a saber*/);

    T getDato(unsigned int);
};

template<class T>
Lista<T>::Lista() {
    inicio = nullptr;
}

template<class T>
Lista<T>::~Lista() {
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
int Lista<T>::getTamanio() {
    Nodo<T> *aux = inicio;
    int cont = 0;
    while (aux != nullptr) {
        cont++;
        aux = aux->getNext();
    }
    return cont;
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


#endif //MAILMANAGER_LISTA_H
