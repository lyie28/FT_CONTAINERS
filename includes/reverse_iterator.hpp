#ifndef REVERSE_ITERATOR_HPP
# define    REVERSE_ITERATOR_HPP

# include "iterator_traits.hpp"
# include <cstddef>  // for ptrdiff_t

namespace ft
{
	template <typename _Iter>
	class reverse_iterator
	{
	private:
		_Iter														_myIt;

	public:
		typedef _Iter                                            	iterator_type;
		typedef typename iterator_traits<_Iter>::difference_type	difference_type;
		typedef typename iterator_traits<_Iter>::reference       	reference;
		typedef typename iterator_traits<_Iter>::pointer        	pointer;
		typedef typename iterator_traits<_Iter>::iterator_category  category;
	
		/*void constructor*/
		reverse_iterator() : _myIt() {}
		
		/*normal constructor*/
		explicit reverse_iterator(_Iter theIt) : _myIt(theIt) {}
		
		template <class T>
		/*copy constructor*/
		reverse_iterator(const reverse_iterator<T>& _toCopy) : _myIt(_toCopy.base()) {}

		template <class T>
		reverse_iterator& operator=(const reverse_iterator<T>& _toCopy)
		{ 
			_myIt = _toCopy.base();
			return *this; 
		}
		
		_Iter base() const 
		{
			return _myIt;
		}
		
		reference operator*() const 
		{
			_Iter _tmp = _myIt; 
			return *--_tmp;
		}

		reverse_iterator  operator+( difference_type x) const
		{
			return reverse_iterator(_myIt - x);
		}
		
		reverse_iterator  operator-( difference_type x) const
		{
			return reverse_iterator(_myIt + x);
		}
		
		reference operator[](difference_type index)
		{
			return *(*this + index);
		}

		pointer operator->() const
		{
			_Iter _tmp = _myIt; 
			return &(*--_tmp);
		}

		reverse_iterator operator++(int)
		{
			reverse_iterator tmp(*this);
			this->operator++();
			return (tmp);
		}

		reverse_iterator operator--(int)
		{
			reverse_iterator tmp(*this);
			this->operator--();
			return tmp;
		}

		reverse_iterator& operator++()
		{
			_myIt--;
			return *this;
		}
		reverse_iterator& operator--()
		{
			_myIt++;
			return *this;
		}

		reverse_iterator&  operator+=( difference_type x)
		{
			_myIt -= x;
			return *this;
		}

		reverse_iterator&  operator-=( difference_type x)
		{
			_myIt += x;
			return *this;
		}
	};

	
	/*non-member functions*/
	template <class Iterator1, class Iterator2>
    typename reverse_iterator<Iterator1>::difference_type operator-(const reverse_iterator<Iterator1> & lhs, const reverse_iterator<Iterator2>& rhs)
    {
        return rhs.base() - lhs.base();
    }

	template <class Iterator>
	reverse_iterator<Iterator> operator+ (typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it)
    {
        return (rev_it + n);
    }
	
	template <class Iterator1, class Iterator2>
	bool operator!=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
	{
		return lhs.base() != rhs.base();
	}

	template <class Iterator1, class Iterator2>
	bool operator>(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
    {
        return lhs.base() < rhs.base();
    }

	template <class Iterator1, class Iterator2>
	bool operator>=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
    {
        return lhs.base() <= rhs.base();
    }

	template <class Iterator1, class Iterator2>
	bool operator<(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
    {
        return lhs.base() > rhs.base();
    }

	template <class Iterator1, class Iterator2>
	bool operator<=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
    {
        return lhs.base() >= rhs.base();
    }

	template <class Iterator1, class Iterator2>
	bool operator==(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
    {
        return lhs.base() == rhs.base();
    }
}

#endif