/*<COPYRIGHT JOAO REZENDE>*/
#pragma once
#ifndef STRUCTURES_ARRAY_STACK_H
#define STRUCTURES_ARRAY_STACK_H

#include <cstdint>
#include <stdexcept>

namespace structures {
    /**ArrayStack*/
template<typename T> class ArrayStack {
		T* contents;
		int top_;
		std::size_t max_size_;
		static const  auto DEFAULT_SIZE= 10u;

	public:
		ArrayStack();

		explicit ArrayStack(std::size_t max);

		~ArrayStack();

		void push(const T& data);

		T pop();

		T& top();

		void clear();

		std::size_t size();

		std::size_t max_size();

		bool empty();

		bool full();
	};
}  // namespace structures

#endif
/**DESTRUCTOR*/
template<typename T> structures::ArrayStack<T>::~ArrayStack() {	 	  	 	     	    	     	 	      	     	     	 	
	delete[] contents;
}

/**CONSTRUCTOR*/
template<typename T> structures::ArrayStack<T>::ArrayStack() {
	contents = new T[max_size_];
	top_ = -1;
}

/**SINGLE PARAMETER CONSTRUCTOR*/
template<typename T> structures::ArrayStack<T>::ArrayStack(std::size_t max) {
    max_size_= max;
	contents = new T[max];
	top_ = -1;
}

/**ADD ELEMENT*/
template<typename T>
void structures::ArrayStack<T>::push(const T& data) {
	if (full())
		throw std::out_of_range("PILHA CHEIA");
	contents[++top_]= data;
}

/**RETURN THE LAST ELEMENT OF THE STACK AND ERASE IT*/
template<typename T>
T structures::ArrayStack<T>::pop() {
	if (empty()) {
		throw std::out_of_range("PILHA VAZIA");
	} else {
		return contents[top_--];
	}
}

/**RETURN THE LAST ELEMENT*/
template<typename T>
T & structures::ArrayStack<T>::top() {	 	  	 	     	    	     	 	      	     	     	 	
	if (empty()) {
		throw std::out_of_range("LISTAVAZIA");
	} else {
		return contents[top_];
	}
}

/**CLEARS THE VECTOR*/
template<typename T>
void structures::ArrayStack<T>::clear() {
	top_= -1;
}

/**RETURNS THE SIZE OF THE ARRAY*/
template<typename T>
std::size_t structures::ArrayStack<T>::size() {
	return top_+1;
}

/**RETURNS THE TOTAL SIZE OF THE ARRAY*/
template<typename T>
std::size_t structures::ArrayStack<T>::max_size() {
	return max_size_;
}

/**RETURNS IF THE STACK IS EMPTY*/
template<typename T>
bool structures::ArrayStack<T>::empty() {
	return top_ == -1;
}

/**RETURNS IF THE STACK IS FULL*/
template<typename T>
bool structures::ArrayStack<T>::full() {
	return top_ == max_size_ - 1;
}	 	  	 	     	    	     	 	      	     	     	 	
