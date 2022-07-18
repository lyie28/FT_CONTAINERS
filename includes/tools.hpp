#ifndef TOOLS_HPP
#define TOOLS_HPP

#include "pair.hpp"
#include <functional>
#include <iostream>

namespace ft
{
    template <typename T>
    void swap(T &a, T &b)
    {
        T tmp;

        tmp = b;  
        b = a;
        a = tmp;
    }

    template <class value_type>
    struct tree_node
    {
        public:

        int bf;
        unsigned int height;
        value_type  pair;
        tree_node   *right;
        tree_node   *left;
        tree_node   *parent;
        /*need this as cannot access root->right in iterator file*/
        bool        is_end;

        tree_node() : bf(0), height(0), pair(), right(NULL), left(NULL), parent(NULL), is_end(false) {}
    
    };

    template <class T>
    struct less : std::binary_function<T, T, bool> 
    {
        bool operator() (const T& x, const T& y) const {return x<y;}
    };

    template <class It1, class It2 >
    bool lexicographical_compare(It1 it1_first, It1 it1_last, It2 it2_first, It2 it2_last)
    {
        /*is vec1 (it1) < vec2 (it2)*/

        //while still elements to check in vec1
        while (it1_first != it1_last)
        {
            //if vec2 has a size of 0 OR vec2[n] < vec1[n]
                if (it2_first == it2_last || *it2_first < *it1_first)
                    return false;
                else if (*it1_first < *it2_first) // if vec1[n] < vec2[n]] return true
                    return true;
                //if elements are same
                it1_first++;
                it2_first++;
        }
        //if vec2 is bigger than vec1 (as still has elements) return true, vec1 is lex less than than vec2
        //else if it2 is same length as vec1 and all elements equal, return false, vec1 not smaller than vec2, they are equal
        return (it2_first != it2_last);
    }

    template <class InputIterator1, class InputIterator2>
    bool equal (InputIterator1 begin1, InputIterator2 end1, InputIterator2 begin2)
    {
        while (begin1 != end1)
        {
            if (!(*begin1 != *begin2))
                return (false);
            ++begin1;
            ++begin2;
        }
        return (true);
    }
}

#endif