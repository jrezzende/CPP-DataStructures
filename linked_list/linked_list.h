/** <copyright github.com/jrezzende> */

#ifndef STRUCTURES_LINKED_LIST_H
#define STRUCTURES_LINKED_LIST_H

#include <cstdint>      // size_t
#include <stdexcept>   //   C++ exceptions
#include <algorithm>  // standard algorithms

namespace structures {

/** CLASS LINKED LIST */

template<typename T>
class LinkedList {
 public:
    LinkedList();  //  DEFAULT CONSTRUCTOR
    ~LinkedList();  //  DEFAULT DESTRUCTOR
    void clear();  //  CLEARS THE ENTIRE LIST
    void push_back(const T& data);  //  PUSHES A NODE AT THE END OF THE LIST
    void push_front(const T& data);  //  PUSHES A NODE AT THE BEGGINING
    void insert(const T& data, std::size_t index);   //  INSERT A NODE AT POS
    void insert_sorted(const T& data);  //  INSERT A NODE IN A SORTED POSITION
    T& at(std::size_t index);  //  REFERENCES A NODE FROM DESIRED POSITION
    T pop(std::size_t index);  //  REMOVES AND RETURNS A NODE FROM POS
    T pop_back();  //  REMOVES AND RETURNS A NODE FROM THE LAST POSITION
    T pop_front();  //  REMOVES AND RETURNS A NODE FROM THE FIRST POSITION
    void remove(const T& data);  //  REMOVES A NODE FROM A DESIRED POSITION
    bool empty() const;  //  TRUE IF THE LIST IS EMPTY
    bool contains(const T& data) const;  //  TRUE IF THE LIST CONTAINS SUCH DATA
    std::size_t find(const T& data) const;  //  RETURN THE INDEX OF A DATA
    std::size_t size() const;  //  ACTUAL SIZE OF THE LIST

 private:
    class Node {  // Elemento
     public:
        explicit Node(const T& data):
            data_{data}	 	  	 	     	    	     	 	      	     	     	 	
        {}

        Node(const T& data, Node* next_node):
            data_{data},
            next_node_{next_node}
        {}
        //  novo constructor
        Node():
        data_{NULL},
        next_node_{NULL}
        {}

        T& data() {  //  getter: dado
            return data_;
        }

        const T& data() const {  //  getter const: dado
            return data_;
        }

        Node* next_node() {  //  getter: próximo
            return next_node_;
        }

        const Node* next_node() const {  //  getter const: próximo
            return next_node_;
        }

        void next_node(Node* node) {  //  setter: próximo
            next_node_ = node;
        }

     private:
        T data_;
        Node* next_node_{nullptr};
    };

    Node* end() {  //  último nodo da lista
        auto it = head;
        for (auto i = 1u; i < size(); ++i) {	 	  	 	     	    	     	 	      	     	     	 	
            it = it->next_node();
        }
        return it;
    }

    Node* head{nullptr};
    std::size_t size_{0u};
};

}  // namespace structures

#endif

  //  using namespace structures

/** DEFAULT CONSTRUCTOR */
template<typename T>
structures::LinkedList<T>::LinkedList() {
    size_ = 0;
}

/** DEFAULT DESTRUCTOR */
template<typename T>
structures::LinkedList<T>::~LinkedList() {
    clear();
}

/** CLEARS THE ENTIRE LIST */
template<typename T>
void structures::LinkedList<T>:: clear() {
    Node* current = head;
    Node* next_node;
    while (current != nullptr) {
       next_node = current->next_node();
       delete current;
       current = next_node;
    }	 	  	 	     	    	     	 	      	     	     	 	
    head = nullptr;
    size_ = 0;
}


/** PUSHES A NODE AT THE END OF THE LIST */
template<typename T>
void structures::LinkedList<T>::push_back(const T& data) {
	auto new_node= new Node(data);
	if (new_node == nullptr) {
		throw std::out_of_range("LISTA CHEIA!");
	}
    if (empty())
        head= new_node;
    else
        end()->next_node(new_node);
	size_++;
}

/** PUSHES A NODE AT THE BEGGINING OF THE LIST */
template<typename T>
void structures::LinkedList<T>::push_front(const T& data) {
    auto new_node= new Node(data);
    if (new_node == nullptr)
        throw std::out_of_range("LISTA VAZIA!");
	if (empty()) {
		head= new_node;
	} else {
        new_node->next_node(head);
        head = new_node;
    }
	size_++;
}

/** INSERT A NODE IN POS */
template<typename T>
void structures::LinkedList<T>::insert(const T& data, std::size_t index) {	 	  	 	     	    	     	 	      	     	     	 	
    if (index > size_ || index < 0)
        throw std::out_of_range("ERRO DE INDICE!");
    if (empty()) {
        auto new_node = new Node(data);
        new_node->next_node(head);
        head = new_node;
    } else {
        auto aux = head;
        for (int i = 1; i < index; i++)
            aux = aux->next_node();
        aux->next_node(new Node(data, aux->next_node()));
    }
	size_++;
}

/** INSERT A NODE IN A SORTED POS */
template<typename T>
void structures::LinkedList<T>::insert_sorted(const T& data) {
    if (empty()) {
        push_front(data);
    } else {
        auto aux= head;
        int pos= 1;
        while (aux->next_node() != nullptr && data > aux->data()) {
            aux= aux->next_node();
            pos++;
        }
        if (data > aux->data())
            insert(data, pos + 1);
        else
            insert(data, pos);
    }
}

/** REFERENCES A NODE FROM DESIRED POSITION */
template<typename T>
T& structures::LinkedList<T>::at(std::size_t index) {	 	  	 	     	    	     	 	      	     	     	 	
    if (index > size_ || index < 0)
        throw std::out_of_range("ERRO DE INDICE!");
    auto aux = head;
    for (int i = 0; i < index; i++) {
        aux = aux->next_node();
    }
    return aux->data();
}

/** REMOVES AND RETURNS A NODE FROM DESIRED POS */
template<typename T>
T structures::LinkedList<T>::pop(std::size_t index) {
    if (size_ == 0) {
        throw std::out_of_range("LISTA VAZIA!");
    } else {
    if (index > size_ || index < 0)
	throw std::out_of_range("ERRO DE INDICE!");
    auto prev_node = head;
    auto next_node = prev_node->next_node();
    T temp;
    for (int i = 0; i < index - 2; i++) {
        prev_node = prev_node->next_node();
        next_node = next_node->next_node();
        }
    prev_node->next_node(next_node->next_node());
    temp= next_node->data();
    next_node->next_node(nullptr);
    next_node = nullptr;
    free(next_node);
    size_--;
    return temp;
    }
}

/** REMOVES AND RETURNS A NODE FROM THE LAST POSITION */
template<typename T>
T structures::LinkedList<T>::pop_back() {	 	  	 	     	    	     	 	      	     	     	 	
    if (size_ == 0)
        throw std::out_of_range("Erro! Lista vazia.");
    auto prev_node= head;
    auto next_node= head;
    T temp;
    while (next_node->next_node() != nullptr) {
        prev_node = next_node;
        next_node = next_node->next_node();
    }
    temp= next_node->data();
    next_node->next_node(nullptr);
    next_node = nullptr;
    free(next_node);
    prev_node->next_node(nullptr);
    size_--;
    return temp;
}

/** REMOVES AND RETURNS THE NODE FROM THE FIRST POSITION */
template<typename T>
T structures::LinkedList<T>::pop_front() {
    if (size_ == 0) {
        throw std::out_of_range("LISTA VAZIA!");
    } else if (size_ == 1) {
	auto temp = head->data();
	clear();
	return temp;
        }
    auto aux = head->next_node();
    auto temp = head->data();
    head = aux;
    size_--;
    return temp;
}

/** REMOVE NODE WITH SPECIFIC DATA */
template<typename T>
void  structures::LinkedList<T>::remove(const T& data) {	 	  	 	     	    	     	 	      	     	     	 	
    if (size_ == 0)
        throw std::out_of_range("LISTA VAZIA!");
    pop(find(data));
}

/**TRUE IF THE LIST IS EMPTY */
template<typename T>
bool structures::LinkedList<T>::empty() const {
    if (size_ == 0) {
        return true;
    } else {
        return false;
    }
}

/** TRUE IF THE LIST CONTAINS SUCH DATA */
template<typename T>
bool structures::LinkedList<T>::contains(const T& data) const {
    auto aux = head;
    for (int i = 0; i < size_; i++) {
        if (aux->data() == data)
            return true;
        aux = aux->next_node();
    }
    free(aux);
    return false;
}

/** SEARCH POSITION OF THE DATA */
template<typename T>
std::size_t structures::LinkedList<T>::find(const T& data) const {
    if (empty())
        throw std::out_of_range("LISTA VAZIA!");
    auto aux = head;
    for (int i = 0; i < size_; i++) {
        if (aux->data() == data)
            return i;
        aux = aux->next_node();
    }	 	  	 	     	    	     	 	      	     	     	 	
    return size_;
}

/** RETURNS THE SIZE OF THE LIST */
template<typename T>
std::size_t structures::LinkedList<T>::size() const {
    return size_;
}
