/** Copyright www.github.com/jrezzende */
#ifndef STRUCTURES_ARRAY_LIST_H
#define STRUCTURES_ARRAY_LIST_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ exceptions
#include <algorithm>  // c++ algorithms

namespace structures {
/** Class ArrayList */
template<typename T>
class ArrayList {
 public:
    ArrayList();  // constructor
    explicit ArrayList(std::size_t max_size);  // single parameter constructor
    ~ArrayList();
    void clear();  // limpa
    void push_back(const T& data);  // empurra pra tras
    void push_front(const T& data);  // empurra pra frente
    void insert(const T& data, std::size_t index);  // adiciona
    void insert_sorted(const T& data);  // insere na lista ordenada
    T pop(std::size_t index);  // retorna o elemento dado pelo index e o remove
    T pop_back();  // retorna o elemento do final e o remove
    T pop_front();  // retorna o elemento do começo e o remove
    void remove(const T& data);  // remove o elemento que contém tal data
    bool full();  // retorna se a lista está cheia
    bool empty();  // retorna se a lista está vazia
    bool contains(const T& data);  // retorna se o elemento possui tal data
    std::size_t find(const T& data);  // retorna o index de tal data
    std::size_t size();  // retorna o tamanho atual da lista
    std::size_t max_size();  // retorna o tamanho máximo da lista
    T& at(std::size_t index);  // retorna a referência do elemento em tal index
    T& operator[](std::size_t index);  // operator[]

 private:
    T* contents;
    std::size_t size_;
    std::size_t max_size_;
    static const auto DEFAULT_MAX = 10u;
};

}  // namespace structures

#endif

/** EMPTY CONSTRUCTOR */
template<typename T>
structures::ArrayList<T>::ArrayList() {	 	  	 	     	    	     	 	      	     	     	 	
    size_= max_size_= 0;
    contents= new T[max_size_];
}

/** SINGLE PARAMETER CONSTRUCTOR */
template<typename T>
structures::ArrayList<T>::ArrayList(std::size_t max_size) {
    size_= 0;
    max_size_= max_size;
    contents= new T[max_size_];
}
/** DESTRUCTOR */
template<typename T>
structures::ArrayList<T>::~ArrayList() {
    delete[] contents;
}
/**CLEARS THE LIST*/
template<typename T>
void structures::ArrayList<T>::clear() {
    size_= 0;
}
/**PUSHES A DATA AT THE END OF THE LIST*/
template<typename T>
void structures::ArrayList<T>::push_back(const T& data) {
    if (full())
        throw std::out_of_range("LISTA CHEIA");
    contents[size_++]= data;
}
/**PUSHES AN ELEMENT AT THE BEGGININ OF THE LIST*/
template<typename T>
void structures::ArrayList<T>::push_front(const T& data) {
    if (full()) {
        throw std::out_of_range("LISTA CHEIA");
    } else {
        for (int i= size_; i > 0; i--)
            std::swap(contents[i], contents[i - 1]);
    }	 	  	 	     	    	     	 	      	     	     	 	
    contents[0]= data;
    size_++;
}
/**PUSHES AN ELEMENT TO A DESIRED POSITION*/
template<typename T>
void structures::ArrayList<T>::insert(const T& data, std::size_t index) {
    if (full()) {
        throw std::out_of_range("LISTA CHEIA");
    } else if (index < 0 || index >= size_) {
        throw std::out_of_range("INDEX OUT OF BOUNDS");
    } else {
        for (int i= size_; i > index; i--)
            std::swap(contents[i - 1], contents[i]);
        contents[index]= data;
        size_++;
    }
}
/**PUSHES AN ELEMENT IN A SORTED LIST*/
template<typename T>
void structures::ArrayList<T>::insert_sorted(const T& data) {
    contents[size_++]= data;
    for (int i = 0; i < size_; i++) {
        for (int j = 0; j < size_; j++) {
            if (contents[i] < contents[j])
                std::swap(contents[i], contents[j]);
        }
    }
}
/**RETURNS AN ELEMENT FROM A DESIRED POSITION*/
template<typename T>
T structures::ArrayList<T>::pop(std::size_t index) {
    if (index < 0 || index >= size_) {
        throw std::out_of_range("INDEX OUT OF BOUNDS");
    } else if (empty()) {
        throw std::out_of_range("LISTA VAZIA");
    } else {	 	  	 	     	    	     	 	      	     	     	 	
        auto t= contents[index];
        for (int i= index; i < size_; i++) {
            contents[index]= contents[index + 1];
        }
        size_--;
        return t;
    }
}
/**RETURNS AN ELEMENT FROM THE LAST POSITION AND DELETES IT*/
template<typename T>
T structures::ArrayList<T>::pop_back() {
    if (empty())
        throw std::out_of_range("LISTA VAZIA");
    else
        return contents[--size_];
}
/**RETURNS AN ELEMENT FROM THE FIRST POSITION AND DELETES IT*/
template<typename T>
T structures::ArrayList<T>::pop_front() {
    if (empty())
        throw std::out_of_range("LISTA VAZIA");
    auto t= contents[0];
    for (int i= 1; i < size_; i++)
        contents[i - 1]= contents[i];
    size_--;
    return t;
}
/**DELETES AN ELEMENT FROM A DESIRED POSITION*/
template<typename T>
void structures::ArrayList<T>::remove(const T& data) {
    int index= find(data);
    if (index > -1) {
        contents[index]= -1;
    for (int i= index; i < size_; i++)
        contents[i - 1]= 1;
    size_--;
    }	 	  	 	     	    	     	 	      	     	     	 	
}
/**RETURNS IF THE LIST IS FULL*/
template<typename T>
bool structures::ArrayList<T>::full() {
    return size_ == max_size_;
}
/**RETURNS IF THE LIST IS EMPTY*/
template<typename T>
bool structures::ArrayList<T>::empty() {
    return size_ == 0;
}
/**CHECK IF THE LIST CONTAINS A DESIRED ELEMENT*/
template<typename T>
bool structures::ArrayList<T>::contains(const T& data) {
    if (empty()) {
        throw std::out_of_range("LISTA VAZIA");
    } else {
        for (int i= 0; i < size_; i++) {
            if (contents[i] == data)
                return true;
        }
        return false;
    }
}
/**RETURNS THE INDEX OF A DESIRED DATA*/
template<typename T>
std::size_t structures::ArrayList<T>::find(const T& data) {
    if (empty()) {
        throw std::out_of_range("LISTA VAZIA");
    } else {
        for (int i= 0; i < size_; i++) {
            if (contents[i] == data)
                return i;
        }
        return size_;
    }	 	  	 	     	    	     	 	      	     	     	 	
}
/**RETURNS THE ACTUAL SIZE OF THE LIST*/
template<typename T>
std::size_t structures::ArrayList<T>::size() {
    return size_;
}
/**RETURNS THE LIMIT OF THE LIST*/
template<typename T>
std::size_t structures::ArrayList<T>::max_size() {
    return max_size_;
}
/**RETURNS THE REFERENCE OF AN ELEMENT OF A DESIRED POSITION*/
template<typename T>
T& structures::ArrayList<T>::at(std::size_t index) {
    if (index < 0 || index > size_ - 1) {
        throw std::out_of_range("INDEX OUT OF BOUNDS");
    } else {
        return contents[index];
    }
}
/**CREATES ANOTHER LIST FROM A DESIRED ELEMENT*/
template<typename T>
T& structures::ArrayList<T>::operator[](std::size_t index) {
    if (empty())
        throw std::out_of_range("LISTA VAZIA");
    return contents[index];
}
	 	  	 	     	    	     	 	      	     	     	 	
