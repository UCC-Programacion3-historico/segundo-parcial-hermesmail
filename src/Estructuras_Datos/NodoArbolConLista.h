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

    void put(NodoArbolConLista<T, K> *);

    NodoArbolConLista<T, K> *remover(T, Nodo<K> *);

    void inorder(vector<K> &); //ver tipo de retorno

    void inorderRango(vector<K> &, string, string);

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
        if (listaPtr.getInicio()->getDato() != ptr)
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
void NodoArbolConLista<T, K>::put(NodoArbolConLista<T, K> *ptr) {
    //hay forma de que sean iguales??
    if (ptr == nullptr) return;// ojo con esto
    if (ptr->getDato() < this->dato) {
        if (izq == nullptr)
            izq = ptr;
        else
            izq->put(ptr);
    } else {
        if (der == nullptr)
            der = ptr;
        else
            der->put(ptr);
    }
}

template<class T, class K>
NodoArbolConLista<T, K> *NodoArbolConLista<T, K>::remover(T d, Nodo<K> *ptr) {
    NodoArbolConLista<T, K> *aux;
    if (d == dato) {
        this->listaPtr.remover(ptr);   //T de esta lista Nodo<K> *
        if (listaPtr.esVacia()) {
            if (der != nullptr) {
                der->put(izq);                     // ATENCION OJO AL PIOJO
                return der;
            }
            return izq;
        }
        return this;
    }
    if (d < dato) {
        if (izq == nullptr)
            throw 1;
        aux = izq;
        izq = izq->remover(d, ptr);
        if (izq != aux)
            delete aux;

    } else {
        if (der == nullptr)
            throw 1;
        aux = der;
        der = der->remover(d, ptr);
        if (der != aux)
            delete aux;
    }
    return this;
}

template<class T, class K>
void NodoArbolConLista<T, K>::inorder(vector<K> &R) {
    if (izq != nullptr)izq->inorder(R);
    Nodo<Nodo<email> *> *aux = listaPtr.getInicio();

    while (aux != nullptr) {
        R.push_back(aux->getDato()->getDato());
        aux = aux->getNext();
    }
    if (der != nullptr)der->inorder(R);
}

template<class T, class K>
void NodoArbolConLista<T, K>::inorderRango(vector<K> &R, string desde, string hasta) {
    if (izq != nullptr && this->getDato() >= desde)
        izq->inorder(R);

    if (this->getDato() >= desde)
        if (this->getDato() <= hasta) {
            Nodo<Nodo<K> *> *aux = this->listaPtr.getInicio();
            while (aux != nullptr) {
                R.push_back(aux->getDato()->getDato());
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
    if (this->dato > d && this->izq != nullptr)
        return izq->getLista(d);
    if (this->dato < d && this->der != nullptr)
        return der->getLista(d);
    throw -1;
}

#endif //MAILMANAGER_NODOARBOLCONLISTA_H
