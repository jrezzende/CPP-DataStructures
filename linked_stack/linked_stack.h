/** <copyright github.com/jrezzende> */
#ifndef STRUCTURES_LINKED_STACK_H
#define STRUCTURES_LINKED_STACK_H

#include <stdexcept>  //  c++ exceptions

namespace structures {

/**CLASS LINKED STACK*/

template<typename T>
class LinkedStack {
 public:
    LinkedStack();  //  DEFAULT CONSTRUCTOR

    ~LinkedStack();  //  DEFAULT DESTRUCTOR

    void clear();  //  CLEARS THE STACK

    void push(const T& data);  //  PUSHES A NODE

    T pop();  // POPS A NODE

    T& top() const;  //  RETURN THE LAST NODE

    bool empty() const;  //  TRUE IF THE LIST IS EMPTY

    std::size_t size() const;  //  ACTUAL SIZE OF THE STACK

 private:
    class Node {
     public:
        explicit Node(const T& data):
            data_{data}
        {}
        Node(const T& data, Node* next):
            data_{data},
            next_{next}	 	  	 	     	    	     	 	      	     	     	 	
        {}

        T& data() {  // getter: info
            return data_;
        }
        const T& data() const {  // getter-constante: info
            return data_;
        }
        Node* next() {  // getter: próximo
            return next_;
        }
        const Node* next() const {  // getter-constante: próximo
            return next_;
        }

        void next(Node* next) {  // setter: próximo
            next_= next;
        }

     private:
        T data_;
        Node* next_;
    };

    Node* top_;  // nodo-topo
    std::size_t size_;  // tamanho
};

}  //  namespace structures

#endif

  // using namespaace structures

/**DEFAULT CONSTRUCTOR*/
template<typename T>
structures::LinkedStack<T>::LinkedStack() {	 	  	 	     	    	     	 	      	     	     	 	
    top_= nullptr;
    size_= 0;
}

/**DEFAULT DESTRUCTOR*/
template<typename T>
structures::LinkedStack<T>::~LinkedStack() {
    clear();
}

/** CLEARS THE STACK */
template<typename T>
void structures::LinkedStack<T>::clear() {
    Node* current= top_;
    Node* aux;
    while (current != nullptr) {
        aux= current;
        current= current->next();
        delete aux;
    }
    top_= nullptr;
    size_= 0;
}

/** PUSHES A NODE */
template<typename T>
void structures::LinkedStack<T>::push(const T& data) {
    Node* new_node= new Node(data);
    if (empty()) {
        top_= new_node;
    } else {
        new_node->next(top_);
        top_= new_node;
    }
    size_++;
}	 	  	 	     	    	     	 	      	     	     	 	

/** POPS THE LAST NODE */
template<typename T>
T structures::LinkedStack<T>::pop() {
    if (empty()) {
        throw std::out_of_range("LISTA VAZIA");
    } else if (size_ == 1) {
        Node* current= top_;
        T temp= current->data();
        top_= nullptr;
        delete current;
        size_--;
        return temp;
    } else {
        Node *current, *prev;
        T temp;
        current= top_;
        temp= current->data();
        prev= current->next();
        delete current;
        size_--;
        top_= prev;
        return temp;
    }
}

/** RETURN THE LAST NODE'S DATA */
template<typename T>
T& structures::LinkedStack<T>::top() const {
    if (empty())
        throw std::out_of_range("LISTA VAZIA");
    return top_->data();
}

/** TRUE IF THE LIST IS EMPTY */
template<typename T>
bool structures::LinkedStack<T>::empty() const {	 	  	 	     	    	     	 	      	     	     	 	
  return size_ == 0;
}

/** ACTUAL SIZE OF THE STACK */
template<typename T>
std::size_t structures::LinkedStack<T>::size() const {
  return size_;
}
