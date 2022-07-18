#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "tools.hpp"
# include <iostream>
# include <memory>
# include "reverse_iterator.hpp"
# include "enable_if.hpp"


namespace	ft
{
	template < class T, class Alloc = std::allocator<T> >
	class vector
	{
		/*member types*/
		public:
		
			typedef 			T										value_type;	
			typedef		 		Alloc 									allocator_type;
			/*equiv T& of std::allocator<T>*/
			typedef typename 	allocator_type::reference 				reference;
			/*equiv const T& of std::allocator<T>*/
			typedef typename 	allocator_type::const_reference 		const_reference;
			/*equiv of T* of std::allocator<T>*/
			typedef typename 	allocator_type::pointer 				pointer;
			/*equiv of const T* of std::allocator<T>*/
			typedef typename 	allocator_type::const_pointer 			const_pointer;
			typedef 			T* 										iterator;
			typedef const		T*										const_iterator;
			typedef typename 	ft::reverse_iterator<iterator> 			reverse_iterator;
			typedef				ft::reverse_iterator<const_iterator>	const_reverse_iterator;
			typedef				std::size_t								size_type;
			typedef				std::ptrdiff_t 							difference_type;

		
		/*protected members-> protected for stack*/
		protected:
			allocator_type  _allocator;
			size_type		_size;
			size_type		_capacity;
			pointer			_array;
		
		public:
		
		/*CLASSICS*/
		/*empty constructor: we set internal allocator so we can allocate and deallocate memory*/
		explicit vector(const allocator_type& alloc = allocator_type()) : _allocator(alloc), _size(0),_capacity(0), _array(NULL) 
		{
			return;
		}

		/*fill constructor: a vector of n lots of val*/
		vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()): _allocator(alloc), _size(n), _capacity(n), _array(NULL)
		{
			if (n > 0)
			{
				/*allocate using allocate*/
				_array = this->_allocator.allocate(this->_size);

				/*fill using construct*/
				for (size_type i = 0; i < n; i++)
					this->_allocator.construct(this->_array + i, val);
			}
			return;
		}

		/*range constructor
		InputIterator: forward/bi-drection/random access iterator to a valid T
		enable if: Needed because of ambiguity with 2 template arguments and fill constructor- if not ft::vector<int> myVec(10, 9); passes here
		->type only exists if ft_is_integral is true (thus, value exists)
		->void ** could be anything, but very unlikely to accidentally pass something of void **
		-> = 0, allows us to add this extra parametre*/
		template <class InputIterator>
		vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIterator>::value, void **>::type = 0) :
			_allocator(alloc), _size(0), _capacity(0), _array(NULL)
		{
			InputIterator	tmp;
			size_t			rangeSize;

			/*get size + set capacity and size*/
			rangeSize = 0;
			for (tmp  = first; tmp != last ; tmp++)
				rangeSize++;
			this->_size = rangeSize;
			this->_capacity = rangeSize;

			if (rangeSize > 0)
			{
				/*allocate using allocate*/
				_array = _allocator.allocate(this->_capacity);
				
				/*fill using construct*/
				pointer it = this->_array;
				for (;first != last; first++)
				{
					this->_allocator.construct(it, *first);
					it++;
				}
			}
			return;
		}

		/*copy constructor*/
		vector(const vector& x) : _allocator(x._allocator), _size(x._size), _capacity(x._size), _array(NULL)
		{
			if (x._size > 0)
			{
				/*allocate using allocate*/
				this->_array = this->_allocator.allocate(this->_capacity);

				/*fill using construct*/
				for (size_type i = 0, size = x._size; i < size; i++)
					this->_allocator.construct(this->_array + i, *(x._array + i));
			}
			return;
		}

		/*operators*/
		vector& operator=(const vector& x)
		{
			if (*this != x)
			{
			this->clear();
			if (_capacity < x._size)
			{
				this->_allocator.deallocate(this->_array, this->_capacity);
				this->_capacity = x._size;
				if (x._size <= 0)
					return *this;
				this->_array = this->_allocator.allocate(this->_capacity);
			}
			this->_size = x._size;
			for (size_type i = 0; i < x._size; i++)
				this->_allocator.construct(_array + i, *(x._array + i));
			}
			return *this;
		}

		/*destructor*/
		virtual ~vector() 
		{
			
			for (size_t i = 0;  i < _size; i++)
					this->_allocator.destroy(this->_array + i);
			_allocator.deallocate(_array,_size);
		};

		/*ALLOCATOR*/
		allocator_type get_allocator(void) const
		{
			return _allocator ;
		}

		/*ITERATORS*/
		iterator begin()
		{
			return iterator(this->_array);
		}

		const_iterator begin() const
		{
			
			return const_iterator(this->_array);
		}	

		reverse_iterator rbegin()
		{
			return reverse_iterator(this->end());
		}

		const_reverse_iterator rbegin() const
		{
			return const_reverse_iterator(this->end());
		}
			
		iterator end()
		{
			return iterator(_array + _size);
		}

		const_iterator end() const
		{
			return const_iterator(this->_array + this->_size);
		}	

		reverse_iterator rend()
		{
			return reverse_iterator(begin());
		}

		const_reverse_iterator rend() const
		{
			return const_reverse_iterator(begin());
		}

		/*CAPACITY*/
		size_type size() const
		{
			return this->_size;
		}

		size_type max_size() const
		{
			return this->_allocator.max_size();
		}

		size_type	capacity() const
		{
			return this->_capacity;
		}

		bool empty() const
		{
			if (this->_size == 0)
				return (true);
			else
				return (false);
		}

		/*increase capapcity of vector*/
		void	reserve(size_type new_capacity)
		{
			if (new_capacity > this->max_size())
				throw std::length_error("vector::reserve");
			if (new_capacity <= this->_capacity)	
				return ;
			pointer new_array = _allocator.allocate(new_capacity);
			for (size_type i = 0; i < new_capacity; i++)
			{
				if (i < _size)
				{
					_allocator.construct(new_array + i, *(_array + i));
					_allocator.destroy(_array + i);  
				}
			}
			if (_capacity != 0)
				_allocator.deallocate(_array, _capacity);
			_capacity = new_capacity;
			_array = new_array;
		}

		/*acess*/
		T &operator[](size_type index)
		{
			return *(_array + index);
		}

		const_reference operator[](size_type index) const
		{
			return *(_array + index);
		}

		reference front(void)
		{
			
			return *(this->begin());
		}

		const_reference front(void) const
		{
			
			return *(this->begin());
		}

		T &back(void)
		{
			
			int pos = _size -1;
			if (pos < 0)
				pos = 0;
			return (_array[pos]);
		}

		const_reference back(void) const
		{
			int pos = _size -1;
			if (pos < 0)
				pos = 0;
			return (_array[pos]);
		}

		T &at(size_type index)
		{
			
			if (index < _size && index >= 0)
				return *(_array + index);
			else
				throw std::out_of_range("ERROR: Element out of range");
		}

		T &at(size_type index) const
		{
			if (index < _size && index >= 0)
				return *(_array + index);
			else
				throw std::out_of_range("ERROR: Element out of range");
		}

		/*modifiers*/

		void push_back(const T& val)
		{
			if (_capacity == 0)
				this->reserve(1);
			else if (_capacity <= _size)
				this->reserve(linux_capacity_caclulator(_size + 1));
			this->_allocator.construct(this->_array + this->_size, val);
			_size++;
		}

		void	pop_back()
		{
			if (this->_size > 0)
			{
				this->_size--;
				_allocator.destroy(this->_array + this->_size);
			}
		}

		void resize(size_type new_size, T value = T())
		{
			size_type size = this->size();
			if (size > new_size) {
				for (size_type i = new_size; i != size; ++i) {
					_allocator.destroy(_array + i);
				}
			} 
			else if (new_size > size) {
				if (new_size > capacity()) {
					reserve(linux_capacity_caclulator(new_size));
				}
				for (size_type i = size; i != new_size; ++i) {
					_allocator.construct(_array + i, value);
				}
			}
			_size = new_size;
		}

		size_t	linux_capacity_caclulator(size_t n)
		{
			if (n <= _size * 2)
				return (_size * 2);
			return (n);
		}

		/*SINGLE ELEMENT*/
		iterator insert (iterator position, const value_type& val)
		{
			/*get offset as diff_type*/
			difference_type offset = position - this->_array;
			if (_capacity < _size + 1)
				reserve(linux_capacity_caclulator(_size + 1));
			pointer cursor = _array + _size;
			pointer stop = _array + offset;
			/*copy each value[n] into value[n+1]*/
			for(; cursor != stop; cursor--) 
			{
				this->_allocator.construct(cursor, *(cursor - 1));
				this->_allocator.destroy(cursor - 1);
			}
			/*now we are read to insert element into position*/
			this->_allocator.construct(stop, val);
			_size++;
			return (stop);
		}

		/*FILL*/
		void insert (iterator position, size_type n, const value_type& val)
		{
			/*get offset as diff_type*/
			difference_type offset = position - this->_array;
			if (n == 0)
				return;
			if (_capacity < _size + n)
				reserve(linux_capacity_caclulator(_size + n));
			/*start cursor at last element of new array*/
			pointer cursor = this->_array + this->_size + n - 1;
			/*stop just after what we are going to insert*/
			pointer stop = this->_array + offset + n - 1;
			for(; cursor != stop; cursor--) 
			{
				/*from end to start, fill new array values with those which will be filled*/
				this->_allocator.construct(cursor, *(cursor - n));
				this->_allocator.destroy(cursor - n);
			}
			this->_size += n;
			while (n > 0)
			{
				/*from end to start, fill now empty places with val*/
				this->_allocator.construct(this->_array + offset - 1 + n, val);
				n--;
			}
			return;
		}

		/*RANGE: need enable_if to differentiate between fill and range inserts*/
		template<class InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, void **>::type = 0) 
		{
			if (first == last)
				return;
			/*get offset as diff_type*/
			difference_type offset = position - this->_array;
			/*get size of range as int*/
			size_type n = 0;
			for (InputIterator it = first; it != last; it++)
				n++;
			if (_capacity < _size + n)
				reserve(linux_capacity_caclulator(_size + n));
			/*start cursor at last element of new array*/
			pointer cursor = this->_array + this->_size + n - 1;
			/*stop just after what we are going to insert*/
			pointer stop = this->_array + offset + n - 1;
			for(; cursor != stop; cursor--) 
			{
				/*from end to start, fill new array values with those which will be filled*/
				this->_allocator.construct(cursor, *(cursor - n));
				this->_allocator.destroy(cursor - n);
			}
			this->_size += n;
			while (n > 0)
			{
				last--;
				/*from end to start, fill now empty places with val*/
				this->_allocator.construct(this->_array + offset - 1 + n, *last);
				n--;
			}
			return;
		}

		/*erase element at position*/
		iterator erase (iterator position)
		{
			iterator cursor = position;
			iterator ite = this->end();

			for (; (cursor + 1) != ite; cursor++)
				cursor[0] = cursor[1];
			_allocator.destroy(this->_array + _size - 1);
			this->_size--;
			return (position);
		}

		iterator erase (iterator first, iterator last)
		{
			for(; first != last; last--)
				erase(first);
			return (first);
		}

		void	clear()
		{
			if (_size == 0)
				return ;
			for (size_type i = 0, size = this->_size; i < size; i++)
				this->_allocator.destroy(this->_array + i);
			this->_size = 0;
			return ;
		}

		template <class InputIterator>
		void assign (InputIterator first, InputIterator last)
		{
			clear();
			insert(begin(), first, last);
		}
		
		void assign (size_type n, const value_type& val)
		{
			this->clear();
			this->_size = n;
			if (this->_capacity < n)
			{
				this->_allocator.deallocate(this->_array, this->_capacity);
				this->_capacity = n;
				if (n > 0)
					this->_array = this->_allocator.allocate(this->_capacity);
				else
					return;
			}
			for(size_type i = 0; i < n; i++)  
			{
				this->_allocator.construct(this->_array + i, val);
			}
			return;
		}

		void swap (vector& y)
		{
			/*calls swap function defined in tools.hpp*/
			ft::swap(_array, y._array);
			ft::swap(this->_size, y._size);
			ft::swap(_capacity, y._capacity);
		}

	};

	/*NON MEMBER FUNCTIONS*/
	/*relational operators*/
	template <class T, class Alloc>
  	bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		if (lhs.size() == rhs.size())
		{
			for (size_t i = 0; i < lhs.size(); i++)
			{
				if (lhs[i] != rhs[i])
					return false;
			}
			return true;
		}
		return false;
	}

  	template <class T, class Alloc>
	bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return !(lhs == rhs);
	}

	/* less-than comparison uses lexicographical compare function defined in tools*/
	template <class T, class Alloc>
	bool operator<(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class T, class Alloc>
	bool operator>(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (rhs < lhs);
	}

	template <class T, class Alloc>
	bool operator<=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return !(lhs > rhs);
	}

	template <class T, class Alloc>
	bool operator>=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return !(lhs < rhs);		
	}

	template <class T, class Alloc>
	void swap (vector<T,Alloc>& x, vector<T,Alloc>& y)
	{
		x.swap(y);
	}
}
#endif