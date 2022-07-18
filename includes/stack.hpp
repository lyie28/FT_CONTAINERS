#ifndef STACK_HPP
# define STACK_HPP

# include "vector.hpp"
#include "tools.hpp"
#include <iostream>

/*stack creates a vector of type<T> but offers limited functions defined here*/
namespace ft
{
	template <class T, class C = ft::vector<T> >
	class stack
	{
		protected :
			C   c; //underlying container-> vector<T>

		public :

			typedef				C					container_type;
			typedef typename	C::value_type 		value_type;
			typedef typename	C::size_type		size_type;
			typedef typename	C::reference 		reference;
			typedef typename	C::const_reference 	const_reference;

			explicit stack(const C& myVector = C()) : c(myVector) { } 
			stack& operator=( const stack& other ) { this->c = other.c; return *this; }

			virtual ~stack() { return; }

			bool empty() const { return c.empty(); }
			
			size_type size() const { return c.size(); }

			value_type& top() { return c.back(); }
			
			const value_type& top() const { return c.back(); }

			void push(const value_type& x) { c.push_back(x); }
			
			void pop() { c.pop_back(); }

			/*friend keyword used so we can access protected value C from non-member function*/
			template <class T1, class C1>
			friend bool operator== (const stack<T1, C1>& lhs, const stack<T1, C1>& rhs);
			
			template <class T1, class C1>
			friend bool operator!=(const stack<T1, C1>& lhs, const stack<T1, C1>& rhs);
			
			template <class T1, class C1>
			friend bool operator<(const stack<T1, C1>& lhs, const stack<T1, C1>& rhs);
			
			template <class T1, class C1>
			friend bool operator<=(const stack<T1, C1>& lhs, const stack<T1, C1>& rhs);
			
			template <class T1, class C1>
			friend bool operator>(const stack<T1, C1>& lhs, const stack<T1, C1>& rhs);
			
			template <class T1, class C1>
			friend bool operator>=(const stack<T1, C1>& lhs, const stack<T1, C1>& rhs);
			
			template <class T1, class _C1>
			friend bool operator==(const stack<T1, _C1>& __x, const stack<T1, _C1>& __y);
};


	/*NON MEMBER FUNCTIONS*/
	/*relational operators*/
	template <class T, class container_type >
  	bool operator== (const stack<T,container_type>& lhs, const stack<T,container_type>& rhs)
	{
		return (lhs.c == rhs.c);
	}

  	template <class T, class container_type>
	bool operator!= (const stack<T, container_type>& lhs, const stack<T, container_type>& rhs)
	{
		return !(lhs.c == rhs.c);
	}

	template <class T, class container_type>
	bool operator<(const stack<T, container_type>& lhs, const stack<T, container_type>& rhs)
	{
		return (ft::lexicographical_compare(lhs.c.begin(), lhs.c.end(), rhs.c.begin(), rhs.c.end()));
	}

	template <class T, class container_type>
	bool operator>(const stack<T, container_type>& lhs, const stack<T, container_type>& rhs)
	{
		return (rhs.c < lhs.c);
	}

	template <class T, class container_type>
	bool operator<=(const stack<T, container_type>& lhs, const stack<T, container_type>& rhs)
	{
		return !(lhs.c > rhs.c);
	}

	template <class T, class container_type>
	bool operator>=(const stack<T, container_type>& lhs, const stack<T, container_type>& rhs)
	{
		return !(lhs.c < rhs.c);		
	}
}
#endif