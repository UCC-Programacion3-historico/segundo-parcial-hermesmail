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
    Lista<K> listaPtr;
    int bal;

    int altura();

    void actualizarEstado();

public:

    NodoArbolConLista(T, K);

    T getDato();

    void put(T, K);

    void put(NodoArbolConLista<T, K> *);

    NodoArbolConLista<T, K> *remover(T, K);

    void inorder(vector<K> &);

    void inorderRango(vector<K> &, string, string);

    Lista<K> &getLista(T);

    void vaciar();

    void print(bool, string);

    void rotacionSimpleIzquierda();
};

template<class T, class K>
NodoArbolConLista<T, K>::NodoArbolConLista(T dato, K ptr) {
    this->dato = dato;
    this->listaPtr.insertarPrimero(ptr);
    izq = nullptr;
    der = nullptr;
    bal = 0;
}

template<class T, class K>
T NodoArbolConLista<T, K>::getDato() {
    return dato;
}

template<class T, class K>
void NodoArbolConLista<T, K>::put(T d, K ptr) {
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
    if (ptr == nullptr) return;
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
NodoArbolConLista<T, K> *NodoArbolConLista<T, K>::remover(T d, K ptr) {
    NodoArbolConLista<T, K> *aux;
    if (d == dato) {
        this->listaPtr.remover(ptr);   //T de esta lista Nodo<email> *
        if (listaPtr.esVacia()) {
            if (der != nullptr) {
                der->put(izq);
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
    Nodo<K> *aux = listaPtr.getInicio();

    while (aux != nullptr) {
        R.push_back(aux->getDato());
        aux = aux->getNext();
    }
    if (der != nullptr)der->inorder(R);
}

template<class T, class K>
void NodoArbolConLista<T, K>::inorderRango(vector<K> &R, string desde, string hasta) {
    if (this->getDato() > hasta) {
        if (izq != nullptr) {
            izq->inorderRango(R, desde, hasta);
        }
    } else {
        if (this->getDato() < desde) {
            if (der != nullptr) {
                der->inorderRango(R, desde, hasta);
            }
        } else {
            Nodo<K> *aux = this->listaPtr.getInicio();
            while (aux != nullptr) {
                R.push_back(aux->getDato());
                aux = aux->getNext();
            }
            if (izq != nullptr) {
                izq->inorderRango(R, desde, hasta);
            }
            if (der != nullptr) {
                der->inorderRango(R, desde, hasta);
            }
        }
    }
}

template<class T, class K>
Lista<K> &NodoArbolConLista<T, K>::getLista(T d) {
    if (this->dato == d)
        return this->listaPtr;
    if (this->dato > d && this->izq != nullptr)
        return izq->getLista(d);
    if (this->dato < d && this->der != nullptr)
        return der->getLista(d);
    throw -1;
}

template<class T, class K>
void NodoArbolConLista<T, K>::vaciar() {
    if (izq != nullptr)
        izq->vaciar();
    if (der != nullptr)
        der->vaciar();
    delete this;
};

template<class T, class K>
int NodoArbolConLista<T, K>::altura() {
    int left, right;

    if (izq == nullptr && der == nullptr)
        return 0;

    if (izq == nullptr)
        return 1 + der->altura();

    if (der == nullptr)
        return 1 + izq->altura();

    left = this->izq->altura();
    right = this->der->altura();

    if (left > right)
        return left + 1;
    else
        return right + 1;
}

template<class T, class K>
void NodoArbolConLista<T, K>::actualizarEstado() {
    this->bal = izq->altura() - der->altura();
}

template<class T, class K>
void NodoArbolConLista<T, K>::print(bool esDerecho, string identacion) {
    if (der != nullptr) {
        der->print(true, identacion + (esDerecho ? "     " : "|    "));
    }
    cout << identacion;
    if (esDerecho) {
        cout << " /";
    } else {
        cout << " \\";
    }
    cout << "-- ";
    cout << dato << endl;
    if (izq != nullptr) {
        izq->print(false, identacion + (esDerecho ? "|    " : "     "));
    }
}

template<class T, class K>
void NodoArbolConLista<T, K>::rotacionSimpleIzquierda() {
    NodoArbolConLista<T, K> *aux = this;
    this->izq;
//    aux->der = raiz->izq;
//    raiz->izq = aux;
//    // actualizamos los balances, según la fórmula
//    aux->bal -= 1 +  max( raiz->bal, 0 );
//    raiz->bal -= 1 -  min( aux->bal, 0 );
}

#endif //MAILMANAGER_NODOARBOLCONLISTA_H
