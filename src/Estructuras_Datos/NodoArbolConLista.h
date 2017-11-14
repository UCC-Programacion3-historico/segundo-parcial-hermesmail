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
    int balance;

    //funciones privadas para balancear
    int calculaBalance(NodoArbolConLista<T, K> *);

    int altura();

    NodoArbolConLista<T, K> *balancearNodo(NodoArbolConLista<T, K> *);

    NodoArbolConLista<T, K> *rotacionII(NodoArbolConLista<T, K> *, NodoArbolConLista<T, K> *);

    NodoArbolConLista<T, K> *rotacionDD(NodoArbolConLista<T, K> *, NodoArbolConLista<T, K> *);

    NodoArbolConLista<T, K> *rotacionDI(NodoArbolConLista<T, K> *, NodoArbolConLista<T, K> *);

    NodoArbolConLista<T, K> *rotacionID(NodoArbolConLista<T, K> *, NodoArbolConLista<T, K> *);

    NodoArbolConLista<T, K> *mayor();

public:
    NodoArbolConLista(T, K);

    T getDato();

//    NodoArbolConLista<T, K> *put(NodoArbolConLista<T, K> *);

    NodoArbolConLista<T, K> *put(T, K);

    NodoArbolConLista<T, K> *remover(T, K);

    void inorder(vector<K> &);

    void inorderRango(vector<K> &, string, string);

    Lista<K> &getLista(T);

    void vaciar();

    void print(bool, string);
};

template<class T, class K>
NodoArbolConLista<T, K>::NodoArbolConLista(T dato, K ptr) {
    this->dato = dato;
    this->listaPtr.insertarPrimero(ptr);
    izq = nullptr;
    der = nullptr;
    balance = 0;
}

template<class T, class K>
T NodoArbolConLista<T, K>::getDato() {
    return dato;
}

template<class T, class K>
//NodoArbolConLista<T, K> *NodoArbolConLista<T, K>::put(NodoArbolConLista<T, K> *NN) {
NodoArbolConLista<T, K> *NodoArbolConLista<T, K>::put(T dato, K ptr) {
//    if (ptr == nullptr)return;   no se que pasa aca
    if (this->dato == dato) {
        if (this->listaPtr.getInicio()->getDato() != ptr)
            this->listaPtr.insertarPrimero(ptr);
    } else {
        if (this->dato > dato) {
            if (this->izq == nullptr) {
                this->izq = new NodoArbolConLista<T, K>(dato, ptr);
                if (this->der != nullptr)       //calculo de balance para evitar la recursividad
                    this->balance = 0;
                else
                    this->balance = -1;
            } else {
                this->izq = this->izq->put(dato, ptr);
                return balancearNodo(this);
            }
        } else {
            if (this->der == nullptr) {
                this->der = new NodoArbolConLista<T, K>(dato, ptr);
                if (this->izq != nullptr)
                    this->balance = 0;
                else
                    this->balance = 1;
            } else {
                this->der = this->der->put(dato, ptr);
                return balancearNodo(this);
            }
        }
    }
}

template<class T, class K>
NodoArbolConLista<T, K> *NodoArbolConLista<T, K>::remover(T d, K ptr) {
    if (this == nullptr)
        throw -1;
    if (this->dato == d) {
        this->listaPtr.remover(ptr);
        if (listaPtr.esVacia()) {
            if (this->izq == nullptr && this->der == nullptr) {
                delete this;
                return nullptr;
            }
            if (this->izq == nullptr && this->der != nullptr) {
                NodoArbolConLista<T, K> *tmp = this->der;
                delete this;
                return tmp;
            }
            if (this->izq != nullptr && this->der == nullptr) {
                NodoArbolConLista<T, K> *tmp = this->izq;
                delete this;
                return tmp;
            }
            if (this->izq != nullptr && this->der != nullptr) {
                NodoArbolConLista<T, K> *NM = this->izq->mayor();
                this->dato = NM->dato;
                this->listaPtr = NM->listaPtr;
                this->izq = this->izq->remover(this->dato, this->listaPtr.getInicio()->getDato());
            }
        } else {
            return this;
        }
    } else {
        if (this->dato > d) {
            this->izq = this->izq->remover(d, ptr);
        } else {
            if (this->dato < d) {
                this->der = this->der->remover(d, ptr);
            }
        }
    }
    return balancearNodo(this);
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
int NodoArbolConLista<T, K>::calculaBalance(NodoArbolConLista<T, K> *ptr) {
    int left = 0, right = 0;
    if (ptr->izq != nullptr)
        left = ptr->izq->altura();
    if (ptr->der != nullptr)
        right = ptr->der->altura();
    return right - left;
}

template<class T, class K>
NodoArbolConLista<T, K> *NodoArbolConLista<T, K>::balancearNodo(NodoArbolConLista<T, K> *ptr) { //ptr a nodo a balancear
    ptr->balance = calculaBalance(ptr);
    NodoArbolConLista<T, K> *n1;
    if (this->balance == -2) {
        n1 = ptr->izq;
        if (n1->balance == -1) {
            ptr = rotacionII(ptr, n1);
        } else if (n1->balance == 1) {
            ptr = rotacionID(ptr, n1);
        } else if (n1->balance == 0)
            ptr = rotacionII(ptr, n1);
    }
    if (this->balance == 2) {
        n1 = ptr->der;
        if (n1->balance == 1) {
            ptr = rotacionDD(ptr, n1);
        } else if (n1->balance == -1) {   // capaz sea else
            ptr = rotacionDI(ptr, n1);
        } else if (n1->balance == 0)
            ptr = rotacionDD(ptr, n1);
    }
    return ptr;
}

template<class T, class K>
int NodoArbolConLista<T, K>::altura() {
    int left, right;

    if (this->izq == nullptr /*&& this->der == nullptr*/)
//        return 1;
        if (this->der == nullptr)
            return 1;

    if (this->izq == nullptr)
        return 1 + this->der->altura();

    if (this->der == nullptr)
        return 1 + this->izq->altura();

    left = this->izq->altura();
    right = this->der->altura();

    if (left > right)
        return left + 1;
    else
        return right + 1;
}

template<class T, class K>
NodoArbolConLista<T, K> *NodoArbolConLista<T, K>::rotacionII(NodoArbolConLista<T, K> *n, NodoArbolConLista<T, K> *n1) {
    n->izq = n1->der;
    n1->der = n;
    if (n1->balance == 1) {
        n->balance = 0;
        n1->balance = 0;
    } else {
        n->balance = -1;
        n1->balance = 1;
    }
    return n1;
};

template<class T, class K>
NodoArbolConLista<T, K> *NodoArbolConLista<T, K>::rotacionDD(NodoArbolConLista<T, K> *n, NodoArbolConLista<T, K> *n1) {
    n->der = n1->izq;
    n1->izq = n;
    if (n1->balance == 1) {
        n->balance = 0;
        n1->balance = 0;
    } else {
        n->balance = 1;
        n1->balance = -1;
    }
    return n1;
};

template<class T, class K>
NodoArbolConLista<T, K> *NodoArbolConLista<T, K>::rotacionDI(NodoArbolConLista<T, K> *n, NodoArbolConLista<T, K> *n1) {
    NodoArbolConLista<T, K> *n2 = n1->izq;
    n->der = n2->izq;
    n2->izq = n;
    n1->izq = n2->der;
    n2->der = n1;

    if (n2->balance == 1)
        n->balance = -1;
    else
        n->balance = 0;

    if (n2->balance == -1)
        n1->balance = 1;
    else
        n1->balance = 0;

    n2->balance = 0;
    return n2;
};

template<class T, class K>
NodoArbolConLista<T, K> *NodoArbolConLista<T, K>::rotacionID(NodoArbolConLista<T, K> *n, NodoArbolConLista<T, K> *n1) {
    NodoArbolConLista<T, K> *n2 = n1->der;
    n->izq = n2->der;
    n2->der = n;
    n1->der = n2->izq;
    n2->izq = n1;

    if (n2->balance == 1)
        n1->balance = -1;
    else
        n1->balance = 0;
    if (n2->balance == -1)
        n->balance = 1;
    else
        n->balance = 0;

    n2->balance = 0;
    return n2;
};

//devuelve el mayor valor de los menores de un nodo
template<class T, class K>
NodoArbolConLista<T, K> *NodoArbolConLista<T, K>::mayor() {
    if (this->der == nullptr)
        return this;
    this->der->mayor();
}

#endif //MAILMANAGER_NODOARBOLCONLISTA_H
