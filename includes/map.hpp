#ifndef MAP_HPP
# define MAP_HPP

#include "pair.hpp"
#include "tools.hpp"
#include "iterator_map.hpp"
#include "reverse_iterator.hpp"
#include "enable_if.hpp"

namespace ft
{
	template <class Key, class Value, class Cmp= ft::less<Key>, class Alloc=  std::allocator< pair<const Key, Value> > >
	class map
	{
		public:
		typedef Key 							key_type;
		typedef Value 							mapped_type;
		typedef ft::pair<const Key, Value> 		value_type;
		typedef Cmp 							key_compare; //the cmp function, defaults to ft::less<key>

		typedef Alloc											allocator_type;
		typedef typename Alloc::reference 						reference;
		typedef typename Alloc::const_reference 				const_reference;
		typedef typename Alloc::pointer 						pointer;
		typedef typename Alloc::const_pointer 					const_pointer;

		typedef tree_node<value_type>* 								Tnode;  
		typedef tree_node<value_type> 								theTnode;
		/*rebind allows us to allocate items of a different type to the normal allocator*/
		/*Member type other is the equivalent allocator type to allocate elements of type Type*/
		typedef typename Alloc::template rebind<theTnode>::other 	node_allocator_type;

		typedef ft::map_iterator<value_type> 							iterator; 
		typedef ft::const_map_iterator<value_type> 						const_iterator; 
		typedef typename ft::reverse_iterator<iterator> 				reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator> 			const_reverse_iterator;
		typedef typename std::size_t 									size_type;
		typedef typename std::ptrdiff_t									difference_type;

		protected:
		/*keep pointers to beginning and end*/
		Tnode 							root;
		Tnode							_end; //end = root->right

		allocator_type					_allocator;
		node_allocator_type 			node_allocator;
		size_type 						_size;
		Cmp 							_comp;

		public:
		
		/*member class: value_compare, compares first elements of key pairs*/
		class value_compare : public std::binary_function<value_type, value_type, bool>
		{
			protected:
			/*the compare function provided in map template*/
				Cmp _comp;
			
			public:
			/*types inherited from std::binary_function*/
				typedef bool 		result_type;
				typedef value_type 	first_argument_type;
				typedef value_type 	second_argument_type;

			value_compare (Cmp c) : _comp(c) {}
			
			bool operator() (const value_type& x, const value_type& y) const
			{
				return _comp(x.first, y.first);
			}
		};	

		/*CONSTRUCTORS*/

		/*empty*/
		explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) :  _allocator(alloc), node_allocator(), _comp(comp)			
		{	
			_size = 0;
			/*allocate and set up pointers to beginning and end*/
			root = node_allocator.allocate(1);			
			node_allocator.construct(root, tree_node<value_type>());
			_end = node_allocator.allocate(1);
			node_allocator.construct(_end, tree_node<value_type>());
			_end->is_end = true;

			/*link root<>end*/
			root->right = this->_end;
			_end->parent = root;
			
		}

		/*range*/
		template <class InputIterator>
		map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIterator>::value, bool>::type = 0) :  _allocator(alloc), node_allocator(), _comp(comp)
		{
			_size = 0;
			/*allocate and set up pointers to beginning and end*/
			root = node_allocator.allocate(1);
			node_allocator.construct(root, tree_node<value_type>());
			_end = node_allocator.allocate(1);
			node_allocator.construct(_end, tree_node<value_type>());
			_end->is_end = true;

			/*link root<>end*/
			_end->parent = root;
			root->right = this->_end;

			/*use insert to fill with values from range*/
			insert(first, last);
		}

		/*copy*/
		map(const map& src) : _allocator(src._allocator),  node_allocator(src.node_allocator), _comp(src._comp)
		{
			/*standard setup*/
			_size = 0;
			root = node_allocator.allocate(1);
			node_allocator.construct(root, tree_node<value_type>());
			_end = node_allocator.allocate(1);
			node_allocator.construct(_end, tree_node<value_type>());
			root->right = this->_end;
			_end->is_end = true;
			_end->parent = root;

			/*insert copy's tree*/
			this->insert(src.begin(), src.end());
		}
		
		map& operator=(const map& copy)
		{
			if (this->_allocator != copy._allocator)
			{
				/*if new alloc is diff to old alloc, dealloc with old alloc before alloc with new alloc*/
				this->clear();
				node_allocator.destroy(_end);
				node_allocator.deallocate(_end, 1);
				node_allocator.destroy(root);
				node_allocator.deallocate(root, 1);
				this->_allocator = copy._allocator;
				root = node_allocator.allocate(1);
				node_allocator.construct(root, tree_node<value_type>());
				_end = node_allocator.allocate(1);
				node_allocator.construct(_end, tree_node<value_type>());
			}
			else
			{
				this->_allocator = copy._allocator;
				this->clear();
			}
			/*reset details*/
			_size = 0;
			_end->is_end = true;
			root->right = _end;
			_end->parent = root;
			
			/*copy all other elements*/
			this->_comp = copy._comp;
			this->_allocator = copy._allocator;
			this->node_allocator = copy.node_allocator;

			/*insert copy's tree*/
			this->insert(copy.begin(), copy.end());
			return(*this);
		}

		~map()
		{	
			this->clear();
			node_allocator.destroy(_end);
			node_allocator.deallocate(_end, 1);
			node_allocator.destroy(root);
			node_allocator.deallocate(root, 1);
		}

		allocator_type get_allocator() const
		{
			return _allocator;
		}

		/*access functions*/
		mapped_type& operator[](const key_type& k)
		{
			iterator it = find(k);

			if (it != end())
				return it->second;
			/*create pair to add into tree*/
			value_type to_add = value_type(k, mapped_type());
			/*get ret iterator from the insert*/
			ft::pair<iterator, bool> ret = (this->insert(to_add));
			/*return the value from the key pair stored in the pointer of the first element of pair*/
			return (*(ret.first)).second;
		}

		/*iterator functions*/
		iterator begin(void)
		{
			if (_size == 0)
				return iterator(end());
			Tnode tmp = root;
			while(tmp->left)
				tmp = tmp->left;
			return iterator(tmp);
		}

		const_iterator begin(void) const
		{
			if (_size == 0)
				return const_iterator(end());
			Tnode tmp = root;
			while (tmp->left)
				tmp = tmp->left;
			return const_iterator(tmp);
		}

		reverse_iterator rbegin(void)
		{
			iterator it = end();
			return reverse_iterator(it); 
		}
		
		const_reverse_iterator rbegin(void) const
		{
			const_iterator it = end();
			return const_reverse_iterator(it); 
		}

		iterator end(void)
		{
			return iterator(_end);
		}

		const_iterator end(void) const
		{
			return const_iterator(_end);
		}

		reverse_iterator rend(void)
		{
			iterator it = begin();
			return reverse_iterator(it);
		}

		const_reverse_iterator rend(void) const
		{
			const_iterator it = begin();
			return const_reverse_iterator(it);
		}

		/*capacity functions*/
		bool empty() const
		{
			if (_size == 0)
				return true;
			return false;
		}

		size_type size() const
		{
			return _size;
		}

		size_type max_size() const
		{
			return node_allocator.max_size();
		}

		/*lookup functions*/
		/*returns 1 if key exists in tree and 0 if doesn't exist*/
		size_type count( const Key& key ) const
		{
			if (find(key) != end())
				return 1;
			return 0;
		}
		
		/*returns a pair with first element pointing to first element that is not less (>=) than the key
		and second pointing to first element that is greater than key*/
		ft::pair<iterator,iterator> equal_range( const Key& key )
		{
				iterator ret1;
				iterator ret2;
				ret1 = lower_bound(key);
				ret2 = upper_bound(key);
				return ft::make_pair(ret1, ret2);
		}

		ft::pair<const_iterator,const_iterator> equal_range( const Key& key ) const
		{
				const_iterator ret1;
				const_iterator ret2;
				ret1 = lower_bound(key);
				ret2 = upper_bound(key);
				return make_pair<const_iterator, const_iterator>(ret1, ret2);
		}

		private:
		Tnode upper_rec( Tnode node, const Key& key, Tnode last) const
		{
		if (!node)
				return (last);
			if (node == _end)
				return(upper_rec(node->left, key, node));
			if (_comp(node->pair.first, key) || node->pair.first == key)
				return(upper_rec(node->right, key, last));
			return(upper_rec(node->left, key, node));
		}

		Tnode lower_rec( Tnode node, const Key& key, Tnode last) const
		{
			if (!node)
				return (last);
			if (node == _end)
				return(lower_rec(node->left, key, node));
			if (_comp(node->pair.first, key)) //if node is less than key
				return(lower_rec(node->right, key, last));
			return(lower_rec(node->left, key, node)); //else >=
		}

		public:
		/*first element that is greater than the key (not equal to but less function == false) using comp function*/
		iterator upper_bound( const Key& key )
		{
			if (_size == 0)
				return end();
			return iterator(upper_rec(root, key, 0));
		}

		const_iterator upper_bound( const Key& key ) const
		{
			if (_size == 0)
				return end();
			return const_iterator(upper_rec(root, key, 0));
		}

		/*first element that is not less than the key (>=) using comp function*/
		iterator lower_bound( const Key& key )
		{
			if (_size == 0)
				return end();
			Tnode tmp = lower_rec(root, key, 0);
			if (!tmp)
				return end();
			return (iterator(tmp));
		}

		const_iterator lower_bound( const Key& key ) const
		{
			if (_size == 0)
				return end();
			Tnode tmp = lower_rec(root, key, 0);
			if (!tmp)
				return end();
			return (const_iterator(tmp));
		}

		/*observer functions*/
		key_compare key_comp() const
		{
			return _comp;
		}

		value_compare value_comp() const
		{
			return value_compare(this->_comp);
		}

		/*UP TO HERE*/
		/*modifier functions*/
		
		private: 
		Tnode balanceAct(Tnode node)
		{
			/*checks height of rh and lh side of node and rotates if imbalanced*/
			int bf = getBF(node);
			int bf2;
			if (bf == 2)
			{
				/*does rotations and returns new root*/
				bf2 = getBF(node->left);
				if (bf2 == 1)
					return rotateToRight(node);
				else if (bf2 == -1)
					return caseLR(node);
			}
			else if (bf == -2) 
			{
				/*does rotations and returns new root*/
				bf2 = getBF(node->right);
				if (bf2 == 1)
					return caseRL(node);
				if (bf2 == -1)
					return rotateToLeft(node);
			}
			/*no rotations, returns normal root*/
			return node;
		}

		/*Example:
		        10    --->      5
			  5				 4	    10
		   4			          
		*/
		Tnode rotateToRight(Tnode node)
		{
			Tnode new_root = node->left; //new_root = 5
			Tnode node_new_left = new_root->right; //10->left = NULL

			new_root->right = node; //5->right = 10
			node->left = node_new_left; //10->left = NULL
			if (node_new_left) //if this exists
				node_new_left->parent = node; //set new parent
			new_root->parent = node->parent; //
			node->parent = new_root; //set new node parent
			node->height = getHeight(node); //update height
			new_root->height = getHeight(new_root); //update height

			return new_root; //return the new root
		}
	
		/*Example:
		        10    --->      6
			  5				 5	   10
	          	6		          
		*/
		Tnode caseLR(Tnode node)
		{
			Tnode stick = node->left; // stick = 5
			Tnode new_root = stick->right; //new_root = 6!

			stick->right = new_root->left;  //5->right = NULL
			if (new_root->left) { //if exists, set parent
				new_root->left->parent = stick;
			}

			node->left = new_root->right; //10 left = NULL
			if (new_root->right) //if exists, set parent
				new_root->right->parent = node;

			new_root->right = node; //6_>right = 1-
			new_root->parent = node->parent;
			node->parent = new_root;
			new_root->left = stick; //6->left = 5
			stick->parent = new_root;

			/*update heights*/
			stick->height = getHeight(stick);
			node->height = getHeight(node);
			new_root->height = getHeight(new_root);

			return new_root;
		}

		/*Example:
		        10              --->     11
			  		12		          10	12
					    12	          
		*/
		Tnode rotateToLeft(Tnode node)
		{
			Tnode new_root = node->right;
			
			Tnode node_new_right = new_root->left;

			new_root->left = node;
			node->right = node_new_right;
			if (node_new_right)
				node_new_right->parent = node;
			new_root->parent = node->parent;
			node->parent = new_root;
			node->height = getHeight(node);
			new_root->height = getHeight(new_root);

			return new_root;
		}

		/*Example:
		        10         --->     11
			  		12		      10	12
				 11	          
		*/
		Tnode caseRL(Tnode node)
		{
			Tnode stick = node->right;
			Tnode new_root = stick->left;

			stick->left = new_root->right;
			if (new_root->right)
				new_root->right->parent = stick;

			node->right = new_root->left;
			if (new_root->left)
				new_root->left->parent = node;

			new_root->left = node;
			new_root->parent = node->parent;
			node->parent = new_root;
			new_root->right = stick;
			stick->parent = new_root;

			stick->height = getHeight(stick);
			node->height = getHeight(node);
			new_root->height = getHeight(new_root);
			return new_root;
		}

		unsigned getHeight(Tnode node) const
		{
			unsigned int ls_height;
			unsigned int rs_height;
			if (node->left)
				ls_height = node->left->height;
			else
				ls_height = 0;
			if (node->right)
				rs_height = node->right->height;
			else
				rs_height = 0;
			if (ls_height >= rs_height)
				return (ls_height + 1);
			return (rs_height + 1);
		}

		int getBF(Tnode node)
		{
			unsigned int ls_height;
			if (node->left)
				ls_height = node->left->height;
			else
				ls_height = 0;
			unsigned int rs_height;
			if (node->right)
				rs_height = node->right->height;
			else
				rs_height = 0;
			return (ls_height - rs_height);
		}

		Tnode insert_rec(const value_type& value, Tnode node, Tnode& inserted, Tnode parent = 0)
		{
			/*arrives here when first element is inserted and in recursive call when we reach NULL branch where we can insert node*/
			if (!node || _size == 0)
			{
				if (_size == 0)
				{
					_allocator.construct(&root->pair, value);
					inserted = root;
					_size++;
					return inserted;
				}
				Tnode new_node;
				new_node = node_allocator.allocate(1);
				node_allocator.construct(new_node, tree_node<value_type>());
				_allocator.construct(&new_node->pair, value);
				new_node->right = NULL;
				new_node->left = NULL;
				new_node->parent = parent;
				inserted = new_node;
				_size++;
				return inserted;
			}
			/*else call insert recursively*/
			/*if value to insert is smaller than current node*/
			if (_comp(value.first, node->pair.first))
			{
				/*now move to left*/
				node->left = insert_rec(value, node->left, inserted, node);
			}
			else if (_comp(node->pair.first, value.first)) /*if value to insert is bigger than current node*/
			{
				/*now move to right*/
				node->right = insert_rec(value, node->right, inserted, node);
			}
			else /*already in tree: quit but change inserted to the place of existing node*/
			{
				inserted = node;
				return (NULL);
			}
			/*gives all inserted nodes a height*/
			node->height = getHeight(node);
			/*return value here is most important, will be the new root once functions have all ran LIFO*/
			return balanceAct(node);
		}
		


		public:

		ft::pair<iterator, bool> insert(const value_type& value)
		{
			iterator check = find(value.first);
			if (check != end())
				return ft::make_pair(iterator(check), false);
			Tnode inserted = 0;
			/*temporarily unplug end!*/
			root->right = _end->left;
			if (_end->left)
				_end->left->parent = root;
			Tnode ret = insert_rec(value, root, inserted);
			if (_size != 1)
				root = ret;
			/*replug in end*/
			_end->is_end = true;
			_end->left = root->right;
			if (root->right)
				root->right->parent = _end;
			root->right = this->_end;
			_end->parent = root;
			return ft::make_pair(iterator(inserted), true);
		}

		/*range*/
		template< class InputIterator >
		void insert( InputIterator first, InputIterator last)
		{
			while(first != last)
			{
				insert(*first);
				first++;
			}
		}

		/*hint placement not compatible with my model*/
		template< class InputIterator >
		iterator insert( InputIterator hint, const value_type & value )
		{
			iterator test = find(value.first);
			if (test != end())
				return test;
			/*need to iterate through tree in any case to maintain corrected BF so cannot optimise using hint*/
			(void)hint;
			return (insert(value)).first;

		}

		void clear_nodes( Tnode tmp )
		{
			if (tmp->left)
				clear_nodes(tmp->left);
			if (tmp->right)
				clear_nodes(tmp->right);
			if (tmp)
			{
				node_allocator.destroy(tmp);
				node_allocator.deallocate(tmp, 1);
			}
		}

		void clear( void )
		{
			clear_nodes(root);
			_end = node_allocator.allocate(1);
			node_allocator.construct(_end, tree_node<value_type>());
			root = node_allocator.allocate(1);
			node_allocator.construct(root, tree_node<value_type>());
			_end->is_end = true;
			root->right = this->_end;
			_end->parent = root;
			_size = 0;
		}

		private:

		Tnode erase_rec( Tnode node, const Key& key)
		{
			if (!node)
				return node;
			if (_comp(key, node->pair.first))
			{
				node->left = erase_rec(node->left, key);
			}
			else if (_comp(node->pair.first, key))
			{
				node->right = erase_rec(node->right, key);
			}
			else
			{
 				if (node->left == NULL) //LEAF OR DEMI-LEAF
				{
					Tnode tmp = node->right;
					if (node->right)
						tmp->parent = node->parent;
					node_allocator.destroy(node);
					node_allocator.deallocate(node, 1);
					return tmp;
				}
				else if (node->right == NULL) //DEMI-LEAF
				{
					Tnode tmp = node->left;
					tmp->parent = node->parent;
					node_allocator.destroy(node);
					node_allocator.deallocate(node, 1);
					return tmp;
				}
				else /*CASE THREE CONTINUES BOTH SIDES*/
				{
					Tnode successor;
					successor = node->right;
					while (successor->left)
						successor = successor->left;
					Key *ptr;
					ptr = (Key*)(&node->pair.first);
					node->pair.second = successor->pair.second;
					*ptr =  successor->pair.first;
					node->right = erase_rec(node->right, successor->pair.first);
				}
			}
			/*gives all inserted nodes a height*/
			node->height = getHeight(node);
			return balanceAct(node);
		}

		public:

		void erase( iterator it )
		{
			if (it.ptr == NULL)
				return;
			if (_size == 1)
			{
				this->clear();
				return;
			}
			Tnode tmp = it.ptr;
			/*temporarily unplug end!*/
			root->right = _end->left;
			if (_end->left)
				_end->left->parent = root;
			Tnode new_root = erase_rec(root, tmp->pair.first);
			_size--;
			if (new_root)
			{
				root = new_root;
			}
			/*plug end back in!*/
			_end->is_end = true;
			_end->left = root->right;
			if (root->right)
				root->right->parent = _end;
			root->right = _end;
			_end->parent = root;

		}

		void erase( iterator first, iterator last )
		{
			Key next;
			Key last_key;
			last_key = last->first;
			iterator tmp;
			next = first->first;
			first = find(next);
			while (first != end() && first->first != last_key)
			{
				tmp = first;
				tmp++;
				if (tmp != end())
					next = tmp->first;
				erase(first);
				first = find(next);
			}
			return;
		}

		size_type erase( const Key& key )
		{
			iterator it = find(key);
			if (it != end())
			{
				erase(it);
				return (1);
			}
			return (0);
		}

		private:
		Tnode find_rec( Tnode node, const Key& key) const
		{
			if (!node)
				return (_end);
			if (node == _end)
				return(find_rec(node->left, key));
			if (!_comp(node->pair.first, key) && !_comp(key, node->pair.first))
				return node;
			if (_comp(node->pair.first, key))
				return(find_rec(node->right, key));
			return(find_rec(node->left, key));
		}

		public:
		const_iterator find( const Key& key ) const
		{
			if (_size == 0)
				return end();
			return const_iterator(find_rec(root, key));
		}
		
		iterator find( const Key& key )
		{
			if (_size == 0)
				return end();
			return iterator(find_rec(root, key));
		}

		void	swap(map& src)
		{
			ft::swap(root, src.root);
			ft::swap(_end, src._end);
			ft::swap(_size, src._size);
		}
	};

	/*NON-MEMBER FUNCTIONS*/
	template <class Key, class T, class Compare, class Alloc >
  	bool operator== ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
	{
		if (lhs.size() != rhs.size())
			return (false);
		typename ft::map<Key, T, Compare, Alloc>::const_iterator it = rhs.begin();
		typename ft::map<Key, T, Compare, Alloc>::const_iterator it2 = lhs.begin();
		while (it != rhs.end())
		{
			if (*it != *it2)
				return (false);
			++it2;
			++it;
		}
		return (true);
	}

	template <class Key, class T, class Compare, class Alloc>
  	bool operator!= ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
	{
			if (!(lhs == rhs))
				return true;
			return false;
	}

	template <class Key, class T, class Compare, class Alloc>
  	bool operator< ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class Key, class T, class Compare, class Alloc>
  	bool operator>  ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
	{
		return (!(lhs < rhs) && !(lhs == rhs));
	}

	template <class Key, class T, class Compare, class Alloc>
  	bool operator<= ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
	{
		return (!(lhs > rhs));
	}

	template <class Key, class T, class Compare, class Alloc>
  	bool operator>= ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
	{
		return (!(lhs < rhs));
	}

	template <class Key, class T, class Compare, class Alloc>
  	void swap (map<Key,T,Compare,Alloc>& x, map<Key,T,Compare,Alloc>& y)
	{
		x.swap(y);
	}
}
#endif