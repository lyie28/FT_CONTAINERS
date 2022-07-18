#ifndef PAIR_HPP
# define PAIR_HPP

namespace ft
{
    
    template<class T1,class T2>
    class pair{ 
    
    public:
    typedef T1  first_type;
    typedef T2  second_type;
    T1  first; 
    T2 second;
    
    /*constructors*/
    /*void*/
    pair() :first(T1()), second(T2()) { }

    /*normal*/
    pair(const T1&x, const T2&y):first(x),second(y){} 
    
    /*copy*/
    template<class U,class V>
    pair(const pair<U,V>&p) : first(p.first), second(p.second) {}

    /*operator=*/
    pair& operator=( const pair& other )
    {
        first = other.first;
        second = other.second;
        return *this;
    }
};

    /*non-member functions*/
    template<class T1, class T2>
    pair<T1,T2> make_pair(T1 to1,T2 to2) 
    {
        return pair<T1,T2>(to1,to2);
    }

    template< class T1, class T2 >
    bool operator==( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs )
    {
        if (lhs.first == rhs.first && lhs.second == rhs.second)
            return (true);
        return (false);
    }

    template< class T1, class T2 >
    bool operator!=( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs )
    {
        if (!(lhs == rhs))
            return (true);
        return (false);
    }

    template <class T1, class T2>
    bool operator<(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    { 
        return lhs.first < rhs.first || (rhs.first == lhs.first && lhs.second < rhs.second);
    }

    template <class T1, class T2>
    bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    { 
        return !(rhs < lhs); 
    }

    template <class T1, class T2>
    bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    { 
        return rhs < lhs; 
    }

    template <class T1, class T2>
    bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    { 
        return !(lhs < rhs); 
    }
}

#endif