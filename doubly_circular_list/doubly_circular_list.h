/** <copyright github.com/jrezzende> */
#ifndef STRUCTURES_DOUBLY_CIRCULAR_LIST_H
#define STRUCTURES_DOUBLY_CIRCULAR_LIST_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // c++ exceptions

namespace structures {
/**CLASS DOUBLECIRCULARLIST*/
template<typename T>
class DoublyCircularList {
 public:
    DoublyCircularList() {}
    ~DoublyCircularList();
    void clear();
    void push_back(const T& data);
    void push_front(const T& data);
    void insert(const T& data, std::size_t index);
    void insert_sorted(const T& data);
    T pop(std::size_t index);
    T pop_back();
    T pop_front();
    void remove(const T& data);
    bool empty() const;
    bool contains(const T& data) const;
    T& at(std::size_t index);
    const T& at(std::size_t index) const;
    std::size_t find(const T& data) const;
    std::size_t size() const;

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
    Node* last_index(std::size_t index) {
        auto it = head;
        for (auto i = 1u; i <= index; ++i) {
           it = it->next();
        }
        return it;
    }
    Node* prev_index(std::size_t index) const {
        auto it = head;
        for (auto i = 1u; i < index; ++i) {
           it = it->next();
        }
        return it;
    }
};

}  // namespace structures

/**DESTRUCTOR*/
template<typename T>
structures::DoublyCircularList<T>::~DoublyCircularList() {
    clear();
}
/**CLEARS THE LIST*/
template<typename T>
void structures::DoublyCircularList<T>::clear() {
    while (!empty())
        pop_front();
}
/**PUSHES A NODE INTO THE END OF THE LIST*/
template<typename T>
void structures::DoublyCircularList<T>::push_back(const T& data) {	 	  	 	     	    	     	 	      	     	     	 	
        insert(data, size_);
}
/**PUSHES A NODE INTO THE BEGGINING OF THE LIST*/
template<typename T>
void structures::DoublyCircularList<T>::push_front(const T& data) {
    Node* new_node = new Node(data);
    if (!new_node)
        throw std::out_of_range("LIST IS FULL!");
    if (empty()) {
        head = new_node;
        head->next(head);
        head->prev(head);
    } else {
        new_node->next(head);
        new_node->prev(head->prev());
        head->prev()->next(new_node);
        head->prev(new_node);
        head = new_node;
    }
    size_++;
}
/**PUSHES A NODE INTO DESIRED POSITION*/
template<typename T>
void structures::DoublyCircularList<T>
::insert(const T& data, std::size_t index) {
    if (index > size())
        throw std::out_of_range("INDEX OUT OF BOUNDS!");
    if (empty() || index == 0) {
        push_front(data);
    } else {
        Node* new_node = new Node(data);
        if (!new_node)
            throw std::out_of_range("LIST IS FULL!");
        Node* current = last_index(index);
        new_node->next(current);
        new_node->prev(current->prev());
        current->prev()->next(new_node);
        current->prev(new_node);
        size_++;
    }	 	  	 	     	    	     	 	      	     	     	 	
}
/**PUSHES A NODE INTO A SORTED LIST*/
template<typename T>
void structures::DoublyCircularList<T>::insert_sorted(const T& data) {
    if (empty()) {
        push_front(data);
    } else {
        Node*  current;
        std::size_t pos;
        current = head;
        pos = 0;
        while (current -> next() != head && data > current -> data()) {
            current = current -> next();
            pos++;
        }
        if (pos == 0) {
                push_front(data);
        } else {
            Node* new_node = new Node(data);
            if (data > current->data()) {
                current->next(new_node);
                new_node->prev(current);
            } else {
                new_node->prev(current->prev());
                new_node->next(current);
                current->prev()->next(new_node);
                current->prev(new_node);
            }
            size_++;
        }
    }
}
/**RETURNS AND REMOVES A NODE FROM THE LIST*/
template<typename T>
T structures::DoublyCircularList<T>::pop(std::size_t index) {
    if (empty())
        throw std::out_of_range("LIST IS EMPTY!");
    if (index >= size())
        throw std::out_of_range("INDEX OUT OF BOUNDS!");
    if (index == 0)
        return pop_front();
    auto anterior = last_index(index);
    T temp = anterior->data();
    anterior->prev()->next(anterior->next());
    anterior->next()->prev(anterior->prev());
    size_--;
    delete anterior;
    return temp;
}	 	  	 	     	    	     	 	      	     	     	 	
/**RETURNS AND REMOVES THE LAST NODE OF THE LIST*/
template<typename T>
T structures::DoublyCircularList<T>::pop_back() {
    return pop(size_ - 1);
}
/**RETURNS AND REMOVES THE FIRST NODE OF THE LIST*/
template<typename T>
T structures::DoublyCircularList<T>::pop_front() {
    if (empty())
        throw std::out_of_range("LIST IS EMPTY!");
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
/**REMOVES SPECIFIC NODE'S DATA*/
template<typename T>
void structures::DoublyCircularList<T>::remove(const T& data) {
    pop(find(data));
}
/**TRUE IF LIST IS EMPTY*/
template<typename T>
bool structures::DoublyCircularList<T>::empty() const {
    return size() == 0u;
}
/**TRUE IF LIST CONTAINS SUCH DATA*/
template<typename T>
bool structures::DoublyCircularList<T>::contains(const T& data) const {	 	  	 	     	    	     	 	      	     	     	 	
    return find(data) != size_;
}
/**DATA ACCESS AT INDEX*/
template<typename T>
T& structures::DoublyCircularList<T>::at(std::size_t index) {
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
/**CONST DATA ACCESS*/
template<typename T>
const T& structures::DoublyCircularList<T>::at(std::size_t index) const {
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
/**RETURNS NODE'S INDEX*/
template<typename T>
std::size_t structures::DoublyCircularList<T>::find(const T& data) const {
    std::size_t temp = 0;
    Node* pos = head;
    while (temp < size()) {
        if (pos->data() == data)
            break;
        pos = pos->next();
        temp++;
       }	 	  	 	     	    	     	 	      	     	     	 	
    return temp;
}
/**RETURNS ACTUAL SIZE OF THE LIST*/
template<typename T>
std::size_t structures::DoublyCircularList<T>::size() const {
    return size_;
}
#endif  //  STRUCTURES_DOUBLY_CIRCULAR_LIST_H
