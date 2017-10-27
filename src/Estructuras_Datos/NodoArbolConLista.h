//
// Created by nelon on 27/10/2017.
//

#ifndef MAILMANAGER_NODOARBOLCONLISTA_H
#define MAILMANAGER_NODOARBOLCONLISTA_H

template<class T, class K>
class NodoArbolConLista {
private:
    NodoArbolConLista<T, K> *izq, *der;
    T dato;
    Lista<Nodo<K> *> listaPtr;
public:
    NodoArbolConLista(T, Nodo<K> *);

    T getDato();

    void put(T, Nodo<K> *);

    NodoArbolConLista<T, K> *remover(T d);

    void inorder(Cola<K> &); //ver tipo de retorno

    void inorderRango(Cola<K> &, string, string);

    Lista<Nodo<K> *> &getLista(T);
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

template<class T, class K>
void NodoArbolConLista<T, K>::put(T d, Nodo<K> *ptr) {
    if (d == dato) {
        if (listaPtr.getDato(0) != ptr)
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
void NodoArbolConLista<T, K>::inorder(Cola<K> &R) {
    if (izq != nullptr)izq->inorder(R);
    for (unsigned int i = 0; !this->listaPtr.esVacia(); ++i)
        R.encolar(listaPtr.getDato(i)->getDato());          // muy fiero el getdato(i)  recorre muchas veces la lista
    if (der != nullptr)der->inorder(R);
}

template<class T, class K>
void NodoArbolConLista<T, K>::inorderRango(Cola<K> &R, string desde, string hasta) {
    if (izq != nullptr && this->getDato() >= desde)
        izq->inorder(R);

    if (this->getDato() >= desde && this->getDato() <= hasta) {
        Nodo<Nodo<K> *> *aux = this->listaPtr.getInicio();
        while (aux != nullptr) {
            R.encolar(aux->getDato()->getDato());
            aux = aux->getNext();
        }
    }

    if (der != nullptr && this->getDato() <= hasta)
        der->inorder(R);
}

template<class T, class K>
Lista<Nodo<K> *> &NodoArbolConLista<T, K>::getLista(T d) {
    if (this->dato == d)
        return this->listaPtr;      //capaz que haiga que copiarlos
    if (this->izq != nullptr)
        return izq->getLista(d);
    if (this->der != nullptr)
        return der->getLista(d);
    throw -1;
}

#endif //MAILMANAGER_NODOARBOLCONLISTA_H
