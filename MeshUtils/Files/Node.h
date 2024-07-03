#ifndef NODE_H
#define NODE_H

template <typename T>
class Node{
	private:
		T* value;
		Node<T> *next,
			*prev;

	public: 
		Node();
		Node(T *value);
		
		~Node();

		T* get_value() const;
		void set_value(T* value);
		Node<T>* get_next()const;
		void set_next(Node<T> *node);
		Node<T>* get_prev()const;
		void set_prev(Node<T> *node);

		static Node<T>* get_most_prev(Node<T> *node);
		static Node<T>* get_most_next(Node<T> *node);
		static unsigned int get_neighborhood_size(Node<T> *resident);

		Node<T>& operator++();
		Node<T> operator++(int);
		Node<T>& operator--();
		Node<T> operator--(int);
};

template <typename T>
bool operator==(Node<T> &node, T &value);

template <typename T>
bool operator==(T &value, Node<T> &node);

template <typename T>
bool operator==(Node<T> &node_a, Node<T> &node_b);

template <typename T>
bool operator!=(Node<T> &node, T &value);

template <typename T>
bool operator!=(T &value, Node<T> &node);

template <typename T>
bool operator!=(Node<T> &node_a, Node<T> &node_b);


#include "Node.tpp"

#endif