/*<COPYRIGHT JOAO REZENDE>*/
#ifndef STRUCTURES_ARRAY_QUEUE_H
#define STRUCTURES_ARRAY_QUEUE_H

#include <cstdint>
#include <stdexcept>

namespace structures {
	template<typename T>
	/**ArrayQueue*/
class ArrayQueue {
	public:
	    /**CONSTRUCTOR*/
		ArrayQueue();
        /**SINGLE PARAMETER CONSTRUCTOR*/
		explicit ArrayQueue(std::size_t max);
        /**DESTRUCTOR*/
		~ArrayQueue();
        /**ADD DATA TO THE BEGGINING OF THE QUEUE*/
		void enqueue(const T& data);
        /**RETURN THE FIRST DATA OF THE QUEUE*/
		T dequeue();
        /**RETURN THE LAST ELEMENT OF THE QUEUE*/
		T& back();
        /**CLEAR THE QUEUE*/
		void clear();
        /**RETURNS THE ACTUAL SIZE OF THE QUEUE*/
		std::size_t size();
        /**RETURNS THE MAX SIZE OF THE QUEUE*/
		std::size_t max_size();
        /**RETURNS IF THE QUEUE IS EMPTY*/
		bool empty();
        /**RETURNS IF THE QUEUE IS FULL*/
		bool full();

	private:
		T * contents;
		std::size_t size_;
		std::size_t max_size_;

		static const auto DEFAULT_SIZE = 10u;
	};
}  // namespace structures
#endif

template<typename T>
structures::ArrayQueue<T>::ArrayQueue(std::size_t max) {	 	  	 	     	    	     	 	      	     	     	 	
    size_= 0;
    max_size_= max;
    contents= new T[max_size_];
}

template<typename T>
structures::ArrayQueue<T>::~ArrayQueue() {
    delete[] contents;
}

template<typename T>
void structures::ArrayQueue<T>::enqueue(const T& data) {
    if (full())
        throw std::out_of_range("LISTA CHEIA");
    else
        contents[size_++]= data;
}

template<typename T>
T structures::ArrayQueue<T>::dequeue() {
	if (empty()) {
        throw std::out_of_range("LISTA VAZIA");
    } else {
        auto aux = contents[0];
        for (int i = 0; i < size_; i++)
            contents[i] = contents[i+1];
        size_--;;
        return aux;
    }
}

template<typename T>
T& structures::ArrayQueue<T>::back() {
    if (empty()) {
        throw std::out_of_range("LISTA VAZIA");
    }	 	  	 	     	    	     	 	      	     	     	 	
    return contents[size_ - 1];
}

template<typename T>
void structures::ArrayQueue<T>::clear() {
    size_= 0;
}

template<typename T>
std::size_t structures::ArrayQueue<T>::size() {
	return size_;
}

template<typename T>
std::size_t structures::ArrayQueue<T>::max_size() {
	return max_size_;
}

template<typename T>
bool structures::ArrayQueue<T>::empty() {
	return size_ == 0;
}

template<typename T>
bool structures::ArrayQueue<T>::full() {
	return size_ == max_size_;
}
	 	  	 	     	    	     	 	      	     	     	 	
