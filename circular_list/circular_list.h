/** <copyright github.com/jrezzende> */
#ifndef STRUCTURES_CIRCULAR_LIST_H
#define STRUCTURES_CIRCULAR_LIST_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // c++ Exceptions

namespace structures {
/**CLASS CIRCULARLIST*/
template<typename T>
class CircularList {
 public:
    CircularList() {}
    ~CircularList();
    void clear();
    void push_back(const T& data);
    void push_front(const T& data);
    void insert(const T& data, std::size_t index);
    void insert_sorted(const T& data);
    T& at(std::size_t index);
    const T& at(std::size_t index) const;
    T pop(std::size_t index);
    T pop_back();
    T pop_front();
    void remove(const T& data);
    bool empty() const;
    bool contains(const T& data) const;
    std::size_t find(const T& data) const;
    std::size_t size() const;

 private:
class Node {
 public :
    explicit Node(const T& data):
        data_{data}
    {}

    explicit Node(const T& data, Node* next):
        data_{data},
        next_{next}	 	  	 	     	    	     	 	      	     	     	 	
        {}

    T& data() {  // getter: dado
        return data_;
    }

    const T& data() const {  // getter const: dado
        return data_;
    }

    Node* next() {  // getter: próximo
        return next_;
    }

    const Node* next() const {  // getter const: próximo
        return next_;
    }

    void next(Node* node) {  // setter: próximo
        next_ = node;
    }
 private :
    T data_;
    Node* next_{nullptr};
};
    Node* end() {  //  último nodo da lista
        auto it = head;
        for (auto i = 1u; i < size(); ++i) {
            it = it->next();
        }
        return it;
    }
    Node* indexPrev(std::size_t index) const {
        auto it = head;
        for (auto i = 1u; i < index; ++i) {
            it = it->next();
        }	 	  	 	     	    	     	 	      	     	     	 	
        return it;
    }
    Node* head{nullptr};
    std::size_t size_{0u};
};
}  //  namespace structures

/**DEFAULT CONSTRUCTOR*/
template<typename T>
structures::CircularList<T>::~CircularList() {
    clear();
}

/**CLEARS THE LIST*/
template<typename T>
void structures::CircularList<T>::clear() {
    while (size_)
        pop_front();
}

/**PUSHES A NODE INTO THE BACK OF THELIST*/
template<typename T>
void structures::CircularList<T>::push_back(const T& data) {
    if (empty())
        return push_front(data);
    Node* new_node = new Node(head->data(), head->next());
    if (!new_node)
        throw std::out_of_range("LIST IS FULL!");
    head->next(new_node);
    head->data() = data;
    head = new_node;
    size_++;
}

/**PUSHES A NODE INTO THE FRONT OF THE LIST*/
template<typename T>
void structures::CircularList<T>::push_front(const T& data) {	 	  	 	     	    	     	 	      	     	     	 	
    Node* new_node = new Node(data);
    if (!new_node)
        throw std::out_of_range("LIST IS FULL!");
    if (empty()) {
        head = new_node;
        head->next(head);
    } else {
        new_node->data() = head->data();
        new_node->next(head->next());
        head->next(new_node);
        head->data() = data;
    }
    size_++;
}

/**PUSHES A NODE INTO DESIRED POSITION*/
template<typename T>
void structures::CircularList<T>::insert(const T& data, std::size_t index) {
    if (index > size_|| index < 0) {
        throw std::out_of_range("INDEX OUT OF BOUNDS!");
    }
    if (index == 0) {
        push_front(data);
    } else if (index == size_) {
        push_back(data);
    } else {
    Node* new_node = new Node(data);
        if (new_node == nullptr) {
            throw std::out_of_range("LIST IS FULL!");
        }
        Node* prev = indexPrev(index);
        Node* next = prev->next();
        new_node->next(next);
        prev->next(new_node);
        size_++;
    }	 	  	 	     	    	     	 	      	     	     	 	
}

/**PUSHES A NODE INTO A SORTED LIST*/
template<typename T>
void structures::CircularList<T>::insert_sorted(const T& data) {
    Node* current;
    std::size_t pos;
    if (empty()) {
        push_front(data);
    } else {
        current = head;
        pos = 0;
        while (current -> next() != head && data > current -> data()) {
            current = current -> next();
            pos++;
        }
        if (data > current->data())
            insert(data, pos + 1);
        else
            insert(data, pos);
    }
}

/**ACESSES A GIVEN INDEX DATA*/
template<typename T>
T& structures::CircularList<T>::at(std::size_t index) {
    if (empty())
        throw std::out_of_range("LIST IS EMPTY!");
    if (index >= size())
        throw std::out_of_range("INDEX OUT OF BOUNDS!");
    Node* current = head;
    for (int i = 0; i < index; ++i) {
        current = current->next();
    }
    return current->data();
}	 	  	 	     	    	     	 	      	     	     	 	

/**CONST ACCESS A GIVEN INDEX DATA*/
template<typename T>
const T& structures::CircularList<T>::at(std::size_t index) const {
    if (empty())
        throw std::out_of_range("LIST IS EMPTY!");
    if (index >= size())
        throw std::out_of_range("INDEX OUT OF BOUNDS!");
    Node* current = head;
    for (int i = 0; i < index; ++i) {
        current = current->next();
    }
    return current->data();
}

/**DELETES AND RETURNS INDEX DATA*/
template<typename T>
T structures::CircularList<T>::pop(std::size_t index) {
    if (empty()) {
        throw std::out_of_range("LIST IS EMPTY");
    }
    if (index >= size()) {
        throw std::out_of_range("INDEX OUT OF BOUNDS!");
    }
    if (index == 0) {
        return pop_front();
    }
    Node* prev = indexPrev(index);
    Node* toBePopped = prev->next();
    T temp = toBePopped->data();
    prev->next(toBePopped->next());
    size_--;
    delete toBePopped;
    return temp;
}

/**DELETES AND RETURNS LAST DATA*/
template<typename T>
T structures::CircularList<T>::pop_back() {	 	  	 	     	    	     	 	      	     	     	 	
    return pop(size_ - 1);
}
/**DELETES AND RETURNS FIRST DATA*/
template<typename T>
T structures::CircularList<T>::pop_front() {
    if (empty()) {
        throw std::out_of_range("LIST IS EMPTY!");
    }
    Node* toBePopped;
    T temp = head->data();
        if (size_ == 1) {
        toBePopped = head;
        head = nullptr;
    } else {
        toBePopped = head->next();
        head->next(toBePopped->next());
        head->data() = toBePopped->data();
    }
    size_--;
    delete toBePopped;
    return temp;
}
/**REMOVES GIVEN DATA'S NODE*/
template<typename T>
void structures::CircularList<T>::remove(const T& data) {
    pop(find(data));
}
/**TRUE IF EMPTY*/
template<typename T>
bool structures::CircularList<T>::empty() const {
    return size() == 0;
}
/**TRUE IF CONTAINS DATA*/
template<typename T>
bool structures::CircularList<T>::contains(const T& data) const {
    return find(data) != size();
}	 	  	 	     	    	     	 	      	     	     	 	
/**RETURNS INDEX OF GIVEN DATA*/
template<typename T>
std::size_t structures::CircularList<T>::find(const T& data) const {
    std::size_t index = 0u;
    Node* current = head;
    while (index < size()) {
        if (current->data() == data)
            break;
        current = current->next();
        index++;
    }
    return index;
}
/**RETURNS ACTUAL SIZE*/
template<typename T>
std::size_t structures::CircularList<T>::size() const {
    return size_;
}

#endif  //  STRUCTURES_CIRCULAR_LIST_H
