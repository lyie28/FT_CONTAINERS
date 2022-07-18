#ifndef ITERATOR_TRAITS_HPP
# define ITERATOR_TRAITS_HPP

#include <iterator>

namespace ft
{
  template<typename _Iterator>
  struct iterator_traits
  {
    typedef typename _Iterator::iterator_category iterator_category;
    typedef typename _Iterator::value_type        value_type;
    typedef typename _Iterator::difference_type   difference_type;
    typedef typename _Iterator::pointer           pointer;
    typedef typename _Iterator::reference         reference;
  };

  /*Specialization for pointer types: AKA used for our reverse iterator*/
  template<typename _Tp>
  struct iterator_traits<_Tp*>
  {
    typedef std::random_access_iterator_tag iterator_category;
    typedef _Tp                             value_type;
    typedef std::ptrdiff_t                  difference_type;
    typedef _Tp*                            pointer;
    typedef _Tp&                            reference;
  };

  /* Specialization for const pointer types: AKA used for our reverse const pointers.*/
  template<typename _Tp>
    struct iterator_traits<const _Tp*>
    {
      typedef std::random_access_iterator_tag iterator_category;
      typedef _Tp                         value_type;
      typedef std::ptrdiff_t                   difference_type;
      typedef const _Tp*                  pointer;
      typedef const _Tp&                  reference;
    };
}
#endif