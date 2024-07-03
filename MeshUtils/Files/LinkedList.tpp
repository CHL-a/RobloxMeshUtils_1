
#include "LinkedList.h"
#include <iostream>

using namespace std;

// CONSTRUCTORS
template <typename T>
LinkedList<T>::LinkedList(T &data) {
	Node<T> *newNode = new Node(data);

	this->head = newNode;
	this->tail = newNode;
	this->count = 1;
}

template <typename T>
LinkedList<T>::LinkedList() : head(NULL), tail(NULL), count(0) {}

// DESTRUCTORS
template <typename T>
LinkedList<T>::~LinkedList() {this->clear();}

// METHODS
template <typename T>
Node<T> *LinkedList<T>::get_head() const { return this->head; }

template <typename T>
Node<T> *LinkedList<T>::get_tail() const { return this->tail; }

template <typename T>
uint32_t LinkedList<T>::size() const { return this->count; }

/**
 * Inserts a `node` before the node `before`. Nodes, to the right and including `before` are shifted to the right. Node param `node` now owns the position `before` was in. 
 * 
 * No code sample because idk how the code documentation works.
 * @param before The node to be shifted right. Can be null, resulting appending `node` to the end of the list
 * @param node A resident of a neighborhood availible for getting the head and tail.
*/
template <typename T>
void LinkedList<T>::insert(Node<T> *before, Node<T> *node) {
	Node<T> *m_prev = Node<T>::get_most_prev(node);
	Node<T> *m_next = Node<T>::get_most_next(node);

	this->count += Node<T>::get_neighborhood_size(node);

	// set head and tail
	if (before == NULL) {
		if (this->head == NULL){
			this->head = m_prev;
			this->tail = m_next;
		}else{
			this->tail->set_next(m_prev);
			this->tail = m_next;
		}
	} else if (before == this->head) {
		this->head->set_prev(m_next);
		this->head = m_prev;
	} else {
		Node<T> *other = before->get_prev();

		other->set_next(m_prev);
		before->set_prev(m_next);
	}
}

template <typename T>
void LinkedList<T>::insert(Node<T> *before, T *value){
	this->insert(before, new Node<T>(value));
}

/**
 * Appends node to end
*/
template <typename T>
void LinkedList<T>::insert(Node<T> *node){
	this->insert(nullptr, node);
}

/**
 * Appends value to end
*/
template <typename T>
void LinkedList<T>::insert(T *value){
	this->insert(nullptr, value);
}

/**
 * Extracts node from list and decreases size without dealloc
 * what to do if attempting to extract node in empty list?
 * 
 * @param node Node inside list
 */
template <typename T>
void LinkedList<T>::extract(Node<T> *node) {
	if (this->count == 1)
		this->head = this->tail = nullptr;
	else if (node == this->head) {
		this->head = this->head->get_next();
		node->set_next(nullptr);
	} else if (node == this->tail) {
		this->tail = this->tail->get_prev();
		node->set_prev(nullptr);
	} else{
		Node<T> *prev = node->get_prev(),
			*next = node->get_next();

		node->set_prev(nullptr);
		node->set_next(nullptr);

		prev->set_next(next);
	}

	this->count --;
};

/**
 * Directly extracts and deletes node with dealloc
 */
template <typename T>
void LinkedList<T>::remove(Node<T> *node){
	this->extract(node);
	delete node;
};

template <typename T>
void LinkedList<T>::clear() {
	while (head != nullptr)
		remove(head);
}

template <typename T>
Node<T>* LinkedList<T>::get_node(uint32_t i){
	Node<T>* current = this->head;

	for (unsigned int j = 0; j < i && current != nullptr; j++) {
		current = current->get_next();
	}
	
	return current;
};

template <typename T>
vector<T>* LinkedList<T>::to_vector()const{
	vector<T> *result = new vector<T>();
	result->resize(this->count);

	Node<T> *current = this->head;
	unsigned int i = 0;

	while (current != nullptr) {
		result->at(i++) = *(current->get_value());
		current = current->get_next();

	}
	
	return result;
}

template <typename T>
vector<T*>* LinkedList<T>::to_vector_of_pointers()const{
	vector<T*> *result = new vector<T*>();
	result->resize(this->count);

	Node<T> *current = this->head;
	uint32_t i = 0;

	while (current != nullptr) {
		T* referral = current->get_value();
		result->at(i++) = referral;
		current = current->get_next();
	}
	
	return result;
}

/**
 * Attempts to return an index within linked list. Returns size if not found
 */
template <typename T>
uint32_t LinkedList<T>::find_index(T* comparison)const{
	uint32_t i;
	Node<T> *current = head;
	for (i = 0; i < count; i++) {
		if (*current == *comparison)
			break;

		current = current->get_next();
	}
	
	return i;
};

/**
 * Alternate delete: dereferences all values, not nodes
 */
template <typename T>
void LinkedList<T>::detatch_all() {
	for (Node<T> *current = head; 
		current != nullptr;
		current=current->get_next())
		current->set_value(nullptr);
};


/**
 * Extracts list from this and instantiates a new list in heap. Splits the list from new_begin, making it's the left side part of this and the return value becomes anything on the right
 * 
 * @param result New list that part of the extract is going into
 * @param new_begin Signifies the head of the new list.
* /
template <typename T>
void extract_list(LinkedList<T> *result , Node<T> *new_begin){
	Node<T>* n_tail = new_begin->get_prev();
	
	new_begin->set_prev(nullptr);
	
	// set this's states
	if (new_begin->get_next() == nullptr) {
		this->extract(new_begin);
	} else if (new_begin == this->head){
		this->head = this->tail = nullptr;
		this->count = 0;
	} else {
		this->tail = n_tail;

		this->count -= Node<T>::get_neighborhood_size(new_begin);
	}
	
	// insert into
	result->insert(nullptr, new_begin);

};
*/
