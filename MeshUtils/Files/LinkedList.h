#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Node.h"
#include <vector>
#include <cstdint>

template <typename T>
class LinkedList {
	private:
		Node<T>* head;
		Node<T>* tail;
		uint32_t count;
		
	
	public:
		LinkedList();
		LinkedList(T &data);
		//LinkedList(Node<T>* data);

		~LinkedList();

		Node<T>* get_head() const;
		Node<T>* get_tail() const;
		uint32_t size() const;
		void clear();
		Node<T>* get_node(uint32_t i);
		uint32_t find_index(T* comparison)const;

		void extract(Node<T> *node);
		void remove(Node<T> *node);
		void insert(Node<T> *before, Node<T> *node);
		void insert(Node<T> *before, T *value);
		void insert(Node<T> *node);
		void insert(T *value);
		std::vector<T>* to_vector()const;
		std::vector<T*>* to_vector_of_pointers()const;
		void detatch_all();
};

#include "LinkedList.tpp"

#endif