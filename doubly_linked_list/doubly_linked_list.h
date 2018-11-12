// Copyright github.com/jrezzende
#ifndef STRUCTURES_DOUBLY_LINKED_LIST_H
#define STRUCTURES_DOUBLY_LINKED_LIST_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ Exceptions

namespace structures {
template<typename T>
/**CLASS DOUBLYLINKEDLIST*/
class DoublyLinkedList {
 public:
/**CONSTRUCTOR*/
    DoublyLinkedList() {}
/**DESTRUCTOR*/
    ~DoublyLinkedList() {
        clear();
    }
/**CLEARS THE LIST*/
    void clear() {
        while (!empty())
           pop_front();
    }
/**INSERTS A NODE AT THE END OF THE LIST*/
    void push_back(const T& data) {
        insert(data, size_);
    }
/**INSERTS A NODE AT THE FRONT OF THE LIST*/
    void push_front(const T& data) {
        Node *novo;
        novo = new Node(data);
        if (novo == nullptr)
            throw std::out_of_range("LISTA CHEIA!!!");
        if (empty()) {
            head = novo;
        } else {
            novo -> next(head);
            head -> prev(novo);
            head = novo;
        }	 	  	 	     	    	     	 	      	     	     	 	
        size_++;
    }
/**INSERTS NODE IN GIVEN INDEX*/
    void insert(const T& data, std::size_t index) {
        if (index > size_)
            throw std::out_of_range("ERRO DE INDICE");
        if (index == 0) {
            push_front(data);
        } else {
            Node *novo;
            novo = new Node(data);
            if (novo == nullptr)
                throw std::out_of_range("LISTA CHEIA!!!");
            if (index == size_) {
                Node *atual = end();
                atual -> next(novo);
                novo -> prev(atual);
            } else {
                Node *atual = find_index(index);
                novo -> next(atual);
                novo -> prev(atual -> prev());
                atual -> prev() -> next(novo);
                atual -> prev(novo);
            }
        size_++;
        }
    }
/**INSERTS NODE IN A SORTED POS*/
    void insert_sorted(const T& data) {
        if (empty()) {
            push_front(data);
        } else {
            Node *atual;
            std::size_t posicao;
            atual = head;
            posicao = 0;
            while (atual -> next() != NULL && data > atual -> data()) {	 	  	 	     	    	     	 	      	     	     	 	
                atual = atual -> next();
                posicao++;
            }
            if (posicao ==0) {
                push_front(data);
            } else {
                Node *novo = new Node(data);
                if (data > atual -> data()) {
                    atual -> next(novo);
                    novo -> prev(atual);
                } else {
                    novo ->prev(atual->prev());
                    novo -> next(atual);
                    atual -> prev() -> next(novo);
                    atual -> prev(novo);
                }
                size_++;
            }
        }
    }
/**POP A NODE IN A GIVEN INDEX*/
    T pop(std::size_t index) {
        if (empty())
            throw std::out_of_range("LISTA VAZIA!!!");
        if (index >= size())
            throw std::out_of_range("ERRO DE INDICE");
        if (index == 0)
            return pop_front();
        Node *anterior = find_index(index);
        T data = anterior -> data();
        anterior -> prev() -> next(anterior -> next());
        if (anterior -> next() != nullptr)
            anterior -> next() -> prev(anterior -> prev());
        size_--;
        delete anterior;
        return data;
    }	 	  	 	     	    	     	 	      	     	     	 	
/**POP LAST NODE*/
    T pop_back()  {
        return pop(size_ - 1u);
    }
/**POP FIRST NODE*/
    T pop_front() {
         if (empty())
            throw std::out_of_range("LISTA VAZIA!!!");
        Node * atual = head;
        T volta = atual -> data();
        head = atual -> next();
        if (head != nullptr)
             head -> prev(nullptr);
        size_--;
        delete atual;
        return volta;
    }
/**REMOVE NODE GIVEN SPECIFIC DATA*/
    void remove(const T& data) {
        pop(find(data));
    }
/**TRUE IF LIST IS EMPTY*/
    bool empty() const {  //  lista vazia
        return size() == 0u;
    }
/**TRUE IF LIST CONTAINS SUCH DATA*/
    bool contains(const T& data) const {
        return find(data) != size_;
    }
/**ACCESS DATA FROM GIVEN INDEX*/
    T& at(std::size_t index) {
        if (index >= size())
            throw std::out_of_range("ERRO DE INDICE");
        auto posicao = index == 0?
        head:find_index(index);
        return posicao->data();
    }	 	  	 	     	    	     	 	      	     	     	 	
/**CONST ACCESS DATA FROM GIVEN INDEX*/
    const T& at(std::size_t index) const {
        if (index >= size())
            throw std::out_of_range("ERRO DE INDICE");
        auto posicao = index == 0?
        head:find_index(index);
        return posicao->data();
    }
/**RETURNS INDEX OF GIVEN DATA*/
    std::size_t find(const T& data) const {
        std::size_t temp = 0;
        Node *posicao = head;
        while (temp < size()) {
            if (posicao->data() == data)
                break;
            posicao = posicao->next();
            temp++;
           }
        return temp;
    }
/**RETURNS ACTUAL SIZE OF THE LIST*/
    std::size_t size() const {
        return size_;
    }
 private :
    class Node {
     public:
        explicit Node(const T& data):
            data_{data}
        {}
        Node(const T& data, Node* next):
            data_{data},
            next_{next}
        {}
        Node(const T& data, Node* prev, Node* next):
            data_{data},
            prev_{prev},
            next_{next}	 	  	 	     	    	     	 	      	     	     	 	
        {}
        T& data() {
            return data_;
        }
        const T& data() const {
            return data_;
        }

        Node* prev() {
            return prev_;
        }
        const Node* prev() const {
            return prev_;
        }

        void prev(Node* node) {
            prev_ = node;
        }

        Node* next() {
            return next_;
        }
        const Node* next() const {
            return next_;
        }
        void next(Node* node) {
            next_ = node;
        }
     private :
        T data_;
        Node* prev_{nullptr};
        Node* next_{nullptr};
    };
    Node* head{nullptr};
    std::size_t size_{0u};

    Node* end() {	 	  	 	     	    	     	 	      	     	     	 	
        auto it = head;
        for (auto i = 1u; i < size(); ++i) {
           it = it->next();
        }
        return it;
    }
    Node* find_index(std::size_t index) {
        auto it = head;
        for (auto i = 1u; i <= index; ++i) {
           it = it->next();
        }
        return it;
    }
};
}  // namespace structures

#endif  //  STRUCTURES_DOUBLY_LINKED_LIST_H
