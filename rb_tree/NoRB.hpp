/** Copyright www.github.com/jrezzende */
#ifndef NO_RB_HPP
#define NO_RB_HPP

#include <vector>

#define RB_RUBRO true
#define RB_NEGRO false

template <typename T>
/**CLASS NORB*/
class NoRB {
 private:
    T* dado;    //!< Atributo onde é guardado o valor representado pelo nó
    NoRB<T>* esquerda;  //!< Atributo que aponta para menor nó descendente
    NoRB<T>* direita;   //!< Atributo que aponta para maior nó descendente
    NoRB<T>* pai;       //!< Atributo que aponta para nó ascendente
    bool cor;           //!< Atributo que indica a cor do nó
    std::vector<NoRB<T>*> elementos;  // Elementos acessados durante o
                                            // percurso realizado.
 public:
    /**single param ctor*/
    explicit NoRB(const T& dado);  // single param ctor
    virtual ~NoRB();  // dtor
    /**single param ctor*/
    NoRB<T>* getPai();  // retorna pai
    /**single param ctor*/
    bool getCor(NoRB<T>* nodo);  // this->cor
    /**single param ctor*/
    std::vector<NoRB<T>*> getElementos();  // vectort
    /**single param ctor*/
    NoRB<T>* getEsquerda();  // left
    /**single param ctor*/
    NoRB<T>* getDireita();  // right
    /**single param ctor*/
    NoRB<T>* inserir(const T& dado, NoRB<T>* arv);  // insert
    /**single param ctor*/
    NoRB<T>* remover(NoRB<T>* arv, const T& dado);  // remove
    /**single param ctor*/
    NoRB<T>* minimo(NoRB<T>* nodo);  // minimum
    /**single param ctor*/
    T* getDado();  // data
    /**single param ctor*/
    T* busca(const T& dado, NoRB<T>* arv);  // search
    /**single param ctor*/
    void preOrdem(NoRB<T>* nodo);  // preorder
    /**single param ctor*/
    void emOrdem(NoRB<T>* nodo);  // inorder
    /**single param ctor*/
    void posOrdem(NoRB<T>* nodo);  // postorder
    /**single param ctor*/
    NoRB<T>* roda_esq(NoRB<T>* nodo);  // rotateleft
    /**single param ctor*/
    NoRB<T>* roda_dir(NoRB<T>* nodo);  // rotateright
    /**single param ctor*/
    NoRB<T>* roda_dupla_esq(NoRB<T>* nodo);  // doubleleft
    /**single param ctor*/
    NoRB<T>* roda_dupla_dir(NoRB<T>* nodo);  // doubleright
    /**single param ctor*/
    NoRB<T>* insercaoBinaria(const T& key, NoRB<T>* node);  // insert
    /**single param ctor*/
    NoRB<T>* passoCE_esq(NoRB<T>* atual, NoRB<T>* pai, NoRB<T>* avo);  // a
    /**single param ctor*/
    NoRB<T>* passoCE_dir(NoRB<T>* atual, NoRB<T>* pai, NoRB<T>* avo);  // a
    /**single param ctor*/
    NoRB<T>* passoCED(NoRB<T>* w, NoRB<T>* raiz);  // a
    /**single param ctor*/
    NoRB<T>* passoCED_esq(NoRB<T>* w, NoRB<T>* raiz);  // a
    /**single param ctor*/
    NoRB<T>* passoCED_dir(NoRB<T>* w, NoRB<T>* raiz);  // a
    /**single param ctor*/
    NoRB<T>* remocaoBinaria(NoRB<T>* arv, const T& dado);  // a
    /**single param ctor*/
    NoRB<T>* fixViolacao(NoRB<T>* arv);  // a
};

template <typename T>
NoRB<T>::NoRB(const T& dado) : esquerda{nullptr}, direita{nullptr},
                                           pai{nullptr}, cor{RB_NEGRO} {	 	  	 	     	    	     	 	      	     	     	 	
    this->dado = new T(dado);
}

template <typename T>
NoRB<T>::~NoRB() {
    delete dado;
    delete esquerda;
    delete direita;
}

template <typename T>
NoRB<T>* NoRB<T>::getPai() {
    return pai;
}

template <typename T>
bool NoRB<T>::getCor(NoRB<T>* node) {
    if (node != nullptr) {
        return node->cor;
    } else {
        return RB_NEGRO;
    }
}

template <typename T>
std::vector<NoRB<T>*> NoRB<T>::getElementos() {
    return elementos;
}

template <typename T>
NoRB<T>* NoRB<T>::getEsquerda() {
    return esquerda;
}

template <typename T>
NoRB<T>* NoRB<T>::getDireita() {	 	  	 	     	    	     	 	      	     	     	 	
    return direita;
}

template <typename T>
NoRB<T>* NoRB<T>::inserir(const T& dado, NoRB<T>* arv) {
    arv = insercaoBinaria(dado, arv);
    return fixViolacao(arv);
}

template <typename T>
NoRB<T>* NoRB<T>::fixViolacao(NoRB<T>* arv) {
    if (getCor(arv->direita) == RB_RUBRO) {
        if (getCor(arv->direita->direita) == RB_RUBRO) {
            return roda_dir(arv);
        }
        if (getCor(arv->direita->esquerda) == RB_RUBRO) {
            return roda_dupla_dir(arv);
        }
    }
    if (getCor(arv->esquerda) == RB_RUBRO) {
        if (getCor(arv->esquerda->esquerda) == RB_RUBRO) {
            return roda_esq(arv);
        }
        if (getCor(arv->esquerda->direita) == RB_RUBRO) {
            return roda_dupla_esq(arv);
        }
    }

    return arv;
}

template <typename T>
NoRB<T>* NoRB<T>::remover(NoRB<T>* arv, const T& dado) {
    if (arv == nullptr) {
        throw "Dado Nao Encontrado";
    }	 	  	 	     	    	     	 	      	     	     	 	
    if (dado < *arv->dado) {
        arv->esquerda = remover(arv->esquerda, dado);
    } else if (dado > *arv->dado) {
        arv->direita = remover(arv->direita, dado);
    } else if (arv->esquerda != nullptr && arv->direita != nullptr) {
        *arv->dado = *minimo(arv->direita)->dado;
        arv->direita = remover(arv->direita, *arv->dado);
    } else if (arv->esquerda == nullptr && arv->direita == nullptr) {
        delete arv;
        return nullptr;
    } else {
        NoRB* temp = arv;
        if(arv->esquerda != nullptr)
            arv = arv->esquerda;
        else
            arv = arv->direita;
        arv->pai = temp->pai;
        temp->esquerda = nullptr;
        temp->direita = nullptr;
        delete temp;
        return arv;
    }

    return fixViolacao(arv);
}

template <typename T>
NoRB<T>* NoRB<T>::minimo(NoRB<T>* nodo) {
    while (nodo->esquerda != nullptr) {
        nodo = nodo->esquerda;
    }
    return nodo;
}

template <typename T>
T* NoRB<T>::getDado() {	 	  	 	     	    	     	 	      	     	     	 	
    return dado;
}

template <typename T>
T* NoRB<T>::busca(const T& dado, NoRB<T>* arv) {
    while (arv != nullptr && dado != *arv->getDado()) {
        if (dado < *arv->getDado()) {
            arv = arv->getEsquerda();
        } else {
            arv = arv->getDireita();
        }
    }
    if (arv == nullptr) {
        throw std::runtime_error("Dado não encontrado");
    } else {
        return arv->getDado();
    }
}

template <typename T>
void NoRB<T>::preOrdem(NoRB<T>* nodo) {
    if (nodo != nullptr) {
        elementos.push_back(nodo);
        preOrdem(nodo->getEsquerda());
        preOrdem(nodo->getDireita());
    }
}

template <typename T>
void NoRB<T>::emOrdem(NoRB<T>* nodo) {
    if (nodo != nullptr) {
        emOrdem(nodo->getEsquerda());
        elementos.push_back(nodo);
        emOrdem(nodo->getDireita());
    }
}	 	  	 	     	    	     	 	      	     	     	 	

template <typename T>
void NoRB<T>::posOrdem(NoRB<T>* nodo) {
    if (nodo != nullptr) {
        posOrdem(nodo->getEsquerda());
        posOrdem(nodo->getDireita());
        elementos.push_back(nodo);
    }
}

template <typename T>
NoRB<T>* NoRB<T>::roda_esq(NoRB<T>* arv) {
    NoRB<T> *raiz;
    raiz = arv->esquerda;
    arv->esquerda = raiz->direita;
    raiz->direita = arv;

    raiz->pai = arv->pai;
    arv->pai = raiz;
    if (arv->esquerda != nullptr) {
        arv->esquerda->pai = arv;
    }

    NoRB<T>* aux = raiz->direita;
    if (getCor(aux->direita) == RB_RUBRO) {
        if(raiz->pai != nullptr) {
            raiz->cor = RB_RUBRO;
        } else {
            raiz->cor = RB_NEGRO;
        }
        raiz->esquerda->cor = RB_NEGRO;
        raiz->direita->cor = RB_NEGRO;

    } else {
        raiz->cor = RB_NEGRO;
        aux->cor = RB_RUBRO;
    }	 	  	 	     	    	     	 	      	     	     	 	
    return raiz;
}

template <typename T>
NoRB<T>* NoRB<T>::roda_dir(NoRB<T>* arv) {
    NoRB<T> *raiz;
    raiz = arv->direita;
    arv->direita = raiz->esquerda;
    raiz->esquerda = arv;

    raiz->pai = arv->pai;
    arv->pai = raiz;
    if (arv->direita != nullptr) {
        arv->direita->pai = arv;
    }

    NoRB<T>* aux = raiz->esquerda;
    if (getCor(aux->esquerda) == RB_RUBRO) {
        if(raiz->pai != nullptr) {
            raiz->cor = RB_RUBRO;
        } else {
            raiz->cor = RB_NEGRO;
        }
        raiz->esquerda->cor = RB_NEGRO;
        raiz->direita->cor = RB_NEGRO;

    } else {
        raiz->cor = RB_NEGRO;
        aux->cor = RB_RUBRO;
    }
    return raiz;
}

template <typename T>
NoRB<T>* NoRB<T>::roda_dupla_dir(NoRB<T>* arv) {
    arv->direita = roda_esq(arv->direita);
    return roda_dir(arv);
}	 	  	 	     	    	     	 	      	     	     	 	

template <typename T>
NoRB<T>* NoRB<T>::roda_dupla_esq(NoRB<T>* arv) {
    arv->esquerda = roda_dir(arv->esquerda);
    return roda_esq(arv);
}

template <typename T>
NoRB<T>* NoRB<T>::passoCE_esq(NoRB<T>* atual, NoRB<T>* pai, NoRB<T>* avo) {
    NoRB<T>* tio = avo->direita;
    if (getCor(tio) == RB_RUBRO) {
        pai->cor = RB_NEGRO;
        avo->cor = RB_RUBRO;
        tio->cor = RB_NEGRO;
        atual = avo;
    } else {
        if (pai->direita == atual) {
            roda_esq(pai);
            atual = atual->esquerda;
        }
        pai->cor = RB_NEGRO;
        avo->cor = RB_RUBRO;
        roda_dir(avo);
    }
    return atual;
}

template <typename T>
NoRB<T>* NoRB<T>::passoCE_dir(NoRB<T>* atual, NoRB<T>* pai, NoRB<T>* avo) {
    NoRB<T>* tio = avo->esquerda;
    if (getCor(tio) == RB_RUBRO) {
        pai->cor = RB_NEGRO;
        avo->cor = RB_RUBRO;
        tio->cor = RB_NEGRO;
        atual = avo;
    } else {	 	  	 	     	    	     	 	      	     	     	 	
        if (pai->esquerda == atual) {
            roda_dir(pai);
            atual = atual->direita;
        }
        pai->cor = RB_NEGRO;
        avo->cor = RB_RUBRO;
        roda_esq(avo);
    }
    return atual;
}

template <typename T>
NoRB<T>* NoRB<T>::insercaoBinaria(const T& dado, NoRB<T>* arv) {
    if (dado < *arv->dado) {
        if (arv->esquerda == nullptr) {
            arv->esquerda = new NoRB<T>(dado);
            arv->esquerda->pai = arv;
            arv->esquerda->cor = RB_RUBRO;
        } else {
            arv->esquerda = inserir(dado, arv->esquerda);
        }
    } else {
        if (arv->direita == nullptr) {
            arv->direita = new NoRB<T>(dado);
            arv->direita->pai = arv;
            arv->direita->cor = RB_RUBRO;
        } else {
            arv->direita = inserir(dado, arv->direita);
        }
    }
    return arv;
}

template <typename T>
NoRB<T>* NoRB<T>::passoCED(NoRB<T>* w, NoRB<T>* raiz) {
    while (w != raiz) {                             //  Cond. de término
        if (w == w->pai->esquerda) {	 	  	 	     	    	     	 	      	     	     	 	
            w = passoCED_esq(w, raiz);              //  Esquerda
        } else {
            w = passoCED_dir(w, raiz);              //  Direita
        }
    }
    return w;
}

template <typename T>
NoRB<T>* NoRB<T>::passoCED_esq(NoRB<T>* w, NoRB<T>* raiz) {
    NoRB<T>* y;
    y = w->pai->direita;                                //  Irmão da direita
    if (getCor(y) == RB_RUBRO) {
        y->cor = RB_NEGRO;                              //  Caso 1
        w->pai->cor = RB_RUBRO;                         //  Caso 1
        roda_esq(w->pai);                               //  Caso 1
        y = w->pai->direita;                            //  Reseta Caso 1
    }
    if (getCor(y->esquerda) == RB_NEGRO && getCor(y->direita) == RB_NEGRO) {
        y->cor = RB_RUBRO;                              //  Caso 2
        w = w->pai;                                     //  Sobe Caso 2
    } else {
        if (getCor(y->direita) == RB_NEGRO) {
            y->esquerda->cor = RB_NEGRO;                //  Caso 3
            y->cor = RB_RUBRO;                          //  Caso 3
            roda_dir(y);                                //  Caso 3
            y = w->pai->direita;                        //  Caso 3
        }
        y->cor = getCor(w->pai);                           //  Caso 4
        w->pai->cor = RB_NEGRO;                         //  Caso 4
        y->direita->cor = RB_NEGRO;                     //  Caso 4
        roda_esq(w->pai);                               //  Caso 4
        w = raiz;                                       //  Caso 4
    }
    return w;
}	 	  	 	     	    	     	 	      	     	     	 	

template <typename T>
NoRB<T>* NoRB<T>::passoCED_dir(NoRB<T>* w, NoRB<T>* raiz) {
    NoRB<T>* y;
    y = w->pai->esquerda;                               //  Irmão da direita
    if (getCor(y) == RB_RUBRO) {
        y->cor = RB_NEGRO;                              //  Caso 1
        w->pai->cor = RB_RUBRO;                         //  Caso 1
        roda_dir(w->pai);                               //  Caso 1
        y = w->pai->esquerda;                           //  Reseta Caso 1
    }
    if (getCor(y->direita) == RB_NEGRO && getCor(y->esquerda) == RB_NEGRO) {
        y->cor = RB_RUBRO;                              //  Caso 2
        w = w->pai;                                     //  Sobe Caso 2
    } else {
        if (getCor(y->esquerda) == RB_NEGRO) {
            y->direita->cor = RB_NEGRO;                 //  Caso 3
            y->cor = RB_RUBRO;                          //  Caso 3
            roda_esq(y);                                //  Caso 3
            y = w->pai->esquerda;                       //  Caso 3
        }
        y->cor = w->pai->cor;                           //  Caso 4
        w->pai->cor = RB_NEGRO;                         //  Caso 4
        y->esquerda->cor = RB_NEGRO;                    //  Caso 4
        roda_dir(w->pai);                               //  Caso 4
        w = raiz;                                       //  Caso 4
    }
    return w;
}

template <typename T>
NoRB<T>* NoRB<T>::remocaoBinaria(NoRB<T>* arv, const T& dado) {
    if (arv == nullptr) {
        return arv;
    }
    if (dado < *(arv->getDado())) {	 	  	 	     	    	     	 	      	     	     	 	
        arv->esquerda = remover(arv->getEsquerda(), dado);
        return arv;
    }
    if (dado > *(arv->getDado())) {
        arv->direita = remover(arv->getDireita(), dado);
        return arv;
    }
    if (arv->getDireita() != nullptr && arv->getEsquerda() != nullptr) {
        NoRB<T>* tmp = minimo(arv->getDireita());
        arv->dado = tmp->getDado();
        arv->direita = remover(arv->getDireita(), *(arv->dado));
        return arv;
    }
    if (arv->getDireita() != nullptr) {
        NoRB<T>* filho = (arv->getDireita());
        return filho;
    } else if (arv->getEsquerda() != nullptr) {
        NoRB<T>* filho = (arv->getEsquerda());
        return filho;
    } else {
        delete arv;
        return nullptr;
    }
}

#endif /* NO_RB_HPP */	 	  	 	     	    	     	 	      	     	     	 	
