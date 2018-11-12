/** Copyright www.github.com/jrezzende */
#ifndef STRUCTURES_ARRAY_LIST_H
#define STRUCTURES_ARRAY_LIST_H

#include <cstdint>  // std::size_t
#include <stdexcept>  //  C++ exceptions
#include <cstring>  // c++ strings
#include <algorithm>  // c++ algorithms

namespace structures {
/** Class ArrayList */
template<typename T>
class ArrayList {
 public:
    ArrayList();
    explicit ArrayList(std::size_t max_size);
    ~ArrayList();

    void clear();
    void push_back(const T& data);
    void push_front(const T& data);
    void insert(const T& data, std::size_t index);
    void insert_sorted(const T& data);
    T pop(std::size_t index);
    T pop_back();
    T pop_front();
    void remove(const T& data);
    bool full() const;
    bool empty() const;
    bool contains(const T& data) const;
    std::size_t find(const T& data) const;
    std::size_t size() const;
    std::size_t max_size() const;
    T& at(std::size_t index);
    T& operator[](std::size_t index);
    const T& at(std::size_t index) const;
    const T& operator[](std::size_t index) const;

 private:
    T* contents;
    std::size_t size_;
    std::size_t max_size_;

    static const auto DEFAULT_MAX = 10u;
};

/** CONSTRUCTOR */
template<typename T>
structures::ArrayList<T>::ArrayList() {	 	  	 	     	    	     	 	      	     	     	 	
    size_ = max_size_ = 0;
    contents = new T[0];
}

/** SINGLE PARAMETER CONSTRUCTOR */
template<typename T>
structures::ArrayList<T>::ArrayList(std::size_t max_size) {
    size_ =  0;
    max_size_ = max_size;
    contents = new T[max_size_];
}

/** DESTRUCTOR */
template<typename T>
structures::ArrayList<T>::~ArrayList() {
    delete[] contents;
}

/** CLEARS THE LIST*/
template<typename T>
void structures::ArrayList<T>::clear() {
    size_ = 0;
}

/** PUSHES AN ELEMENT AT THE END OF THE LIST */
template<typename T>
void structures::ArrayList<T>::push_back(const T& data) {
    if (full())
        throw std::out_of_range("Lista cheia");
    contents[size_++] = data;
}

/** PUSHES AN ELEMENT AT THE BEGGININ OF THE LIST*/
template<typename T>
void structures::ArrayList<T>::push_front(const T& data) {
    if (full())
        throw std::out_of_range("Lista cheia");
    if (size_ > 0) {	 	  	 	     	    	     	 	      	     	     	 	
        for (int i = size_; i > 0; i--)
            contents[i] = contents[i-1];
    }
    contents[0] = data;
    size_++;
}

/** PUSHES AN ELEMENT TO A DESIRED POSITION */
template<typename T>
void structures::ArrayList<T>::insert(const T& data, std::size_t index) {
    if (full())
        throw std::out_of_range("Lista cheia");
    if (index > size_)
        throw std::out_of_range("Indice nao valido");
    auto temp = contents[index];
    contents[index] = data;
    for (int i = index + 1 ; i <= size_; i++)
        std::swap(temp, contents[i]);
    size_++;
}

/** PUSHES AN ELEMENT IN A SORTED LIST */
template<typename T>
void structures::ArrayList<T>::insert_sorted(const T& data) {
    if (full()) {
		throw std::out_of_range("Lista cheia");
	} else {
		std::size_t count = 0;
		while ((count < size()) && (strncmp(at(count), data, 3) < 0))
				count += 1;
			insert(data, count);
	}
}

/** RETURNS AN ELEMENT FROM A DESIRED POSITION */
template<typename T>
T structures::ArrayList<T>::pop(std::size_t index) {	 	  	 	     	    	     	 	      	     	     	 	
    if (empty())
       throw std::out_of_range("Lista vazia");
    if (index > size_-1)
        throw std::out_of_range("Indice invalido");
    auto data = contents[index];
    for (int i = index; i < size_; i++)
        contents[i - 1] = contents[i];
    size_--;
    return data;
}

/** RETURNS AN ELEMENT FROM THE LAST POSITION AND DELETES IT */
template<typename T>
T structures::ArrayList<T>::pop_back() {
    if (empty())
       throw std::out_of_range("Lista vazia");
    auto data = contents[--size_];
    contents[size_] = 0;
    return data;
}

/** RETURNS AN ELEMENT FROM THE FIRST POSITION AND DELETES IT */
template<typename T>
T structures::ArrayList<T>::pop_front() {
    if (empty())
        throw std::out_of_range("Lista vazia");
    auto data = contents[0];
    for (int i = 1; i < max_size_; i++)
        contents[i - 1] = contents[i];
    size_--;
    return data;
}

/** DELETES AN ELEMENT FROM A DESIRED POSITION */
template<typename T>
void structures::ArrayList<T>::remove(const T& data) {	 	  	 	     	    	     	 	      	     	     	 	
    int index = find(data);
    if (index > -1) {
        contents[index] = nullptr;
        for (int i = index; i < max_size_; i++)
            contents[i] = contents[i + 1];
        size_--;
    }
}

/** RETURNS IF THE LIST IS FULL */
template<typename T>
bool structures::ArrayList<T>::full() const {
    return size_ == max_size_;
}

/** RETURNS IF THE LIST IS EMPTY */
template<typename T>
bool structures::ArrayList<T>::empty() const {
    return size_ == 0;
}

/** CHECK IF THE LIST CONTAINS A DESIRED ELEMENT */
template<typename T>
bool structures::ArrayList<T>::contains(const T& data) const {
    for (int i = 0; i < size_; i++) {
        if (contents[i] == data)
            return true;
    }
    return false;
}

/** RETURNS THE INDEX OF A DESIRED DATA */
template<typename T>
std::size_t structures::ArrayList<T>::find(const T& data) const {
    for (int i = 0; i < size_; i++) {
        if (contents[i] == data)
            return i;
    }	 	  	 	     	    	     	 	      	     	     	 	
    return size_;
}

/** RETURNS THE ACTUAL SIZE OF THE LIST */
template<typename T>
std::size_t structures::ArrayList<T>::size() const {
    return size_;
}

/** RETURNS THE LIMIT OF THE LIST */
template<typename T> std::size_t structures::ArrayList<T>::max_size() const {
    return max_size_;
}

/** RETURNS THE REFERENCE OF AN ELEMENT OF A DESIRED POSITION */
template<typename T> T& structures::ArrayList<T>::at(std::size_t index) {
    if (index > size_)
        throw std::out_of_range("Lista vazia");
    return contents[index];
}

/** RETURNS AN ELEMENT FROM A DESIRED INDEX */
template<typename T>
T& structures::ArrayList<T>::operator[](std::size_t index) {
    if (index > size_)
        throw std::out_of_range("Lista vazia");
    return contents[index];
}

/** RETURNS THE REFERENCE OF AN ELEMENT OF A DESIRED POSITION */
template<typename T>
const T& structures::ArrayList<T>::at(std::size_t index) const {
    if (index > size_)
        throw std::out_of_range("Lista vazia");
    return contents[index];
}	 	  	 	     	    	     	 	      	     	     	 	

/** RETURNS AN ELEMENT FROM A DESIRED INDEX */
template<typename T>
const T& structures::ArrayList<T>::operator[](std::size_t index) const {
    if (index > size_)
        throw std::out_of_range("Lista vazia");
    return contents[index];
}

//-------------------------------------

/** Class ArrayListString */
class ArrayListString {
 public:
    ArrayListString();
    explicit ArrayListString(std::size_t max_size);
    ~ArrayListString();

    void clear();
    void push_back(const char *data);
    void push_front(const char *data);
    void insert(const char *data, std::size_t index);
    void insert_sorted(const char *data);
    char *pop(std::size_t index);
    char *pop_back();
    char *pop_front();
    void remove(const char *data);
    bool full() const;
    bool empty() const;
    bool contains(const char *data) const;
    std::size_t find(const char *data) const;
    std::size_t size() const;
    std::size_t max_size() const;
    char *at(std::size_t index);
    char *operator[](std::size_t index);
    const char *at(std::size_t index) const;
    const char *operator[](std::size_t index) const;

 private:
    ArrayList<char *> *list;
    static const auto DEFAULT_MAX = 100u;
};

/** CONSTRUCTOR */
structures::ArrayListString::ArrayListString(std::size_t max_size) {	 	  	 	     	    	     	 	      	     	     	 	
    list = new ArrayList<char*>(max_size);
}

/** CONSTRUCTOR */
structures::ArrayListString::~ArrayListString() {
    delete list;
}

/** CLEARS THE LIST */
void structures::ArrayListString::clear() {
    list->clear();
}

/** PUSHES AN ELEMENT AT THE END OF THE LIST */
void structures::ArrayListString::push_back(const char* data) {
    list->push_back(const_cast<char*>(data));
}

/** PUSHES AN ELEMENT AT THE BEGGINING OF THE LIST */
void structures::ArrayListString::push_front(const char* data) {
    list->push_front(const_cast<char*>(data));
}

/** PUSHES AN ELEMENT TO A DESIRED POSITION */
void structures::ArrayListString::insert(const char* data, std::size_t index) {
    list->insert(const_cast<char*>(data), index);
}

/** PUSHES AN ELEMENT IN A SORTED LIST */
void structures::ArrayListString::insert_sorted(const char* data) {
    list->insert_sorted(const_cast<char*>(data));
}

/** RETURNS AN ELEMENT FROM A DESIRED POSITION */
char* structures::ArrayListString::pop(std::size_t index) {
    return list->pop(index);
}	 	  	 	     	    	     	 	      	     	     	 	

/** RETURNS AN ELEMENT FROM THE LAST POSITION AND DELETES IT */
char* structures::ArrayListString::pop_back() {
    return list->pop_back();
}

/** RETURNS AN ELEMENT FROM THE FIRST POSITION AND DELETES IT */
char* structures::ArrayListString::pop_front() {
    return list->pop_front();
}

/** DELETES AN ELEMENT FROM A DESIRED POSITION */
void structures::ArrayListString::remove(const char* data) {
    list->remove(const_cast<char*>(data));
}

/** RETURNS IF THE LIST IS FULL */
bool structures::ArrayListString::full() const {
    return list->full();
}

/** RETURNS IF THE LIST IS EMPTY */
bool structures::ArrayListString::empty() const {
    return list->empty();
}

/** CHECK IF THE LIST CONTAINS A DESIRED ELEMENT */
bool structures::ArrayListString::contains(const char* data) const {
    return list->contains(const_cast<char*>(data));
}

/** RETURNS THE INDEX OF A DESIRED DATA */
std::size_t structures::ArrayListString::find(const char* data) const {
    return list->find(const_cast<char*>(data));
}

/** RETURNS THE ACTUAL SIZE OF THE LIST */
std::size_t structures::ArrayListString::size() const {	 	  	 	     	    	     	 	      	     	     	 	
    return list->size();
}

/** RETURNS THE LIMIT OF THE LIST */
std::size_t structures::ArrayListString::max_size() const {
    return list->max_size();
}

/** RETURNS THE REFERENCE OF AN ELEMENT IN A DESIRED POSITION */
char* structures::ArrayListString::at(std::size_t index) {
    return list->at(index);
}

/** RETURNS THE REFERENCE OF AN ELEMENT OF A DESIRED POSITION */
char* structures::ArrayListString::operator[](std::size_t index) {
    return list->at(index);
}

/** RETURNS THE REFERENCE OF AN ELEMENT OF A DESIRED POSITION */
const char* structures::ArrayListString::at(std::size_t index) const {
    return list->at(index);
}

/** RETURNS THE REFERENCE OF AN ELEMENT OF A DESIRED POSITION */
const char* structures::ArrayListString::operator[](std::size_t index) const {
    return list->at(index);
}


}  // namespace structures

#endif
	 	  	 	     	    	     	 	      	     	     	 	
