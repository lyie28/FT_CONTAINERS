#ifndef ITERATOR_MAP_HPP
# define ITERATOR_MAP_HPP

# include "iterator_traits.hpp"
# include "tools.hpp"
#include <iostream>

namespace ft
{
	template <typename _T>
	class map_iterator
	{

	public:
		/*value attributes*/
		typedef _T 									value_type;
		typedef _T* 								pointer;
		typedef _T& 								reference;
		/*node attributes*/
		typedef tree_node<_T>* 						npointer;
		typedef tree_node<_T>*						Tnode;

		typedef typename iterator_traits<npointer>::difference_type	difference_type;
		typedef std::bidirectional_iterator_tag 					iterator_category;
		
		npointer                       			 ptr;
	
	public:
		/*constructors*/
		map_iterator() : ptr(NULL) {}
		
		//normal construct
		explicit map_iterator(Tnode node) : ptr(node) {}
		
		//copy
		map_iterator(const map_iterator& copy) : ptr(copy.ptr) {}
		
		map_iterator& operator=(const map_iterator& copy)
		{ 
			ptr = copy.ptr; 
			return *this; 
		}
		
		virtual ~map_iterator(void) { return; }
		
		reference operator*() const
		{
			return this->ptr->pair;
		}

		pointer operator->() const
		{
			return &(this->ptr->pair);
		}

		map_iterator& operator++()
		{
			npointer next;

			if (!ptr)
				return *this;
			/*if no rh element*/
			if (ptr->right == NULL)
			{
				next = ptr;
				/*go up through parents until you get to a left-hand connected paren (e.g it is a higher val than child)*/
				while (next->parent && next == next->parent->right)
					next = next->parent;
				next = next->parent;
				ptr = next;
				return (*this);
			}
			/*if there is a rh element, go right and then as far left as possible*/
			next = ptr->right;
			while (next->left)
				next = next->left;
			ptr = next;
			return (*this);
		}
		
		map_iterator operator++(int)
		{
			map_iterator tmp(*this);
			this->operator++();
			return (tmp);
		}

		map_iterator& operator--()
		{
			Tnode tmp = ptr;			
			if (!tmp)
				return *this;
			if (tmp->left)
			{
				/*get further right of left-hand element*/
				tmp = tmp->left;
				while (tmp->right != NULL)
					tmp = tmp->right;
				this->ptr = tmp;
				return (*this);
			}
			/*go up through parents until you get to a right-hand connected paren (e.g it is a lower val than child)*/
			while (tmp->parent && tmp == tmp->parent->left)
				tmp = tmp->parent;
			tmp = tmp->parent;
			ptr = tmp;
			return (*this);
		}

		map_iterator operator--(int) //TODO
		{
			
			map_iterator tmp(*this);
			this->operator--();
			return tmp;
		}
		
		bool operator==(const map_iterator& rhs) const
		{
			return this->ptr == rhs.ptr;
		}
			
			
		bool operator!=(const map_iterator& rhs) const
		{
			return this->ptr != rhs.ptr;
		}
	};

	template <class _T>
	class const_map_iterator
	{

	public:
		/*value attributes*/
		typedef _T								value_type;
		/*const reference + pointer*/
		typedef const value_type				&reference;
		typedef const value_type				*pointer;

		/*node attributes*/
		typedef tree_node<_T>*					Tnode;
		typedef tree_node<_T>* 					npointer;

		typedef typename iterator_traits<npointer>::difference_type	difference_type;
		typedef std::bidirectional_iterator_tag 					iterator_category;
		
		npointer                       			 ptr;
	
	public:
		/*constructors*/
		/*void*/
		const_map_iterator() : ptr(NULL) {}
		
		/*normal constructor*/
		explicit const_map_iterator(Tnode node) : ptr(node) {}
		
		/*copy constructor*/
		template <class T>
		const_map_iterator(const map_iterator<T>& copy) : ptr(copy.ptr) {}
		
		template <class T>
		const_map_iterator& operator=(const map_iterator<T>& copy)
		{ 
			this->ptr = copy.ptr; 
			return *this; 
		}
		
		~const_map_iterator(void) { return; }
		
		reference operator*() const
		{
			return (this->ptr->pair);
		}
		
		pointer operator->(void) const
		{
			return &(this->ptr->pair);
		}
	
		const_map_iterator& operator++()
		{
			npointer next;

			if (!ptr)
				return *this;
			/*if no rh element*/
			if (ptr->right == NULL)
			{
				next = ptr;
				/*go up through parents until you get to a left-hand connected paren (e.g it is a higher val than child)*/
				while (next->parent && next == next->parent->right)
					next = next->parent;
				next = next->parent;
				ptr = next;
				return (*this);
			}
			/*if there is a rh element, go right and then as far left as possible*/
			next = ptr->right;
			while (next->left)
				next = next->left;
			ptr = next;
			return (*this);
		}
		
		const_map_iterator operator++(int)
		{
			const_map_iterator tmp(*this);;
			this->operator++();
			return tmp;
		}

		const_map_iterator& operator--()
		{
			Tnode tmp = ptr;			
			if (!tmp)
				return *this;
			if (tmp->left)
			{
				/*get further right of left-hand element*/
				tmp = tmp->left;
				while (tmp->right != NULL)
					tmp = tmp->right;
				this->ptr = tmp;
				return (*this);
			}
			/*go up through parents until you get to a right-hand connected paren (e.g it is a lower val than child)*/
			while (tmp->parent && tmp == tmp->parent->left)
				tmp = tmp->parent;
			tmp = tmp->parent;
			ptr = tmp;
			return (*this);
		}
		const_map_iterator operator--(int)
		{
			const_map_iterator tmp(*this);
			this->operator--();
			return tmp;
		}
		
		bool operator==(const const_map_iterator& rhs) const
		{
			return this->ptr == rhs.ptr;
		}			
			
		bool operator!=(const const_map_iterator& rhs) const
		{
			return this->ptr != rhs.ptr;
		}
	};
}
#endif

