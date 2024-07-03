#include "Node.h"
#include <cstdint>

using namespace std;

// CONSTRUCTORS
template<typename T>
Node<T>::Node(T* value): 
	value(value), 
	next(NULL), 
	prev(NULL) {}

template<typename T>
Node<T>::Node(): Node(NULL){}

// DESTRUCTORS
template<typename T>
Node<T>::~Node(){
	delete value;
	
	if (next != NULL) {
		next->set_prev(NULL);
		set_next(NULL);
	}
	
	if (prev != NULL) {
		prev->set_next(NULL);
		set_prev(NULL);
	}
}

// METHODS
template<typename T>
T* Node<T>::get_value()const{return value;}

template<typename T>
void Node<T>::set_value(T* value){
	if (value != nullptr)
		delete this->value;

	this->value = value;
}

template<typename T>
Node<T>* Node<T>::get_next()const{return this->next;}

/**
 * Attempts to set next. By virtue, it also should manage the neighbor's states as well. No deallocation.
 * 
 * @param node if node is NULL, then method detaches, making the old next node's previous null and this's next null
*/
template<typename T>
void Node<T>::set_next(Node<T> *node){
	if (node == nullptr) {
		if (this->next == nullptr) return;
		
		this->next->prev = nullptr;
		this->next = nullptr;
		return;
	}

	this->set_next(nullptr);
	node->prev = this;
	this->next = node;
}

template<typename T>
Node<T>* Node<T>::get_prev()const{return this->prev;}

/**
 * Attempts to set prev. By virtue, it also should manage the neighbor's states as well. No deallocation.
 * 
 * @param node if prev is NULL, then method detatches. just like Node<T>->set_next
*/
template<typename T>
void Node<T>::set_prev(Node<T> *node){
	if (node == nullptr) {
		if (this->prev == nullptr) return;
		
		this->prev->next = nullptr;
		this->prev = nullptr;
		return;
	}

	this->set_prev(nullptr);
	node->next = this;
	this->prev = node;
}

/**
 * Attempts to get the most previous resident from sample resident.
*/
template<typename T>
Node<T>* Node<T>::get_most_prev(Node<T> *node) {
	while (node->get_prev() != nullptr)
		node = node->get_prev();
	return node;
};

/**
 * Attempts to get the most next resident from sample resident
*/
template<typename T>
Node<T>* Node<T>::get_most_next(Node<T> *node){
	while (node->get_next() != nullptr) 
		node = node->get_next();
	
	return node;
};

/**
 * Attempts to get the neighborhood size from a resident.
*/
template<typename T>
uint32_t Node<T>::get_neighborhood_size(Node<T> *resident){
	uint32_t result = 0;

	Node<T> *prev1 = resident->get_most_prev(resident);

	while (prev1 != nullptr) {
		prev1 = prev1->get_next();
		result++;
	}
	
	return result;
};

template<typename T>
Node<T>& Node<T>::operator++(){
	this = this->next;
	return *this;
};

template<typename T>
Node<T> Node<T>::operator++(int){
	Node<T> result = *this;
	this->operator++();
	return result;
};

template<typename T>
Node<T>& Node<T>::operator--(){
	this = this->prev;
	return *this;
};

template<typename T>
Node<T> Node<T>::operator--(int){
	Node<T> result = *this;
	this->operator--();
	return result;
};

// OPERATIONS
template <typename T>
bool operator==(Node<T> &node, T &value){return node.value == value;}

template <typename T>
bool operator==(T &value, Node<T> &node){return node==value;}

template <typename T>
bool operator==(Node<T> &node_a, Node<T> &node_b){return node_a == node_b.value;}

template <typename T>
bool operator!=(Node<T> &node, T &value){return !(node==value);};

template <typename T>
bool operator!=(T &value, Node<T> &node){return node!=value;};

template <typename T>
bool operator!=(Node<T> &node_a, Node<T> &node_b){return node_a!=node_b.value;};