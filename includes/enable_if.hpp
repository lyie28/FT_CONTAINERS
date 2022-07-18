#ifndef ENABLE_IF_HPP
#define ENABLE_IF_HPP

namespace  ft 
{
    /*if condition is false, T is void*/
    template< bool B, class T = void >
	struct enable_if 
    {
    };

    /*if condition is true, T is T*/
	template <class T>
	struct enable_if<true, T>
    { 
        typedef T type;
    };

    /*doesn't fall into any of the true defs*/
	template<typename T>
	struct is_integral
    {
        static const bool value = false;
    };

    /*valid integral types*/
    template<>
	struct is_integral<bool>
    {
        static const bool value = true;
    };

    template<>
	struct is_integral<const bool>
    {
        static const bool value = true;
    };

    template<>
	struct is_integral<int>
    { 
        static const bool value = true;
    };

    template<>
	struct is_integral<const int>
    {
        static const bool value = true;
    };

	template<>
    struct is_integral<unsigned int>
    {
        static const bool value = true;
    };

	template<>
	struct is_integral<const unsigned int>
    {
        static const bool value = true;
    };

	template<>
	struct is_integral<long>
    {
        static const bool value = true;
    };

	template<>
	struct is_integral<const long> 
    {
        static const bool value = true;
    };

	template<>
	struct is_integral<long long>
    {
        static const bool value = true;
    };

	template<>
	struct is_integral<const long long>
    {
        static const bool value = true;
    };

	template<>
	struct is_integral<unsigned long>
    {
        static const bool value = true;
    };

	template<>
	struct is_integral<const unsigned long>
    {
        static const bool value = true;
    };

	template<>
	struct is_integral<unsigned long long>
    {
        static const bool value = true;
    };

	template<>
	struct is_integral<const unsigned long long>
    {
        static const bool value = true;
    };

	template<>
	struct is_integral<short>
    { 
        static const bool value = true;
    };

	template<>
	struct is_integral<unsigned short>
    {
        static const bool value = true;
    };

	template<>
	struct is_integral<const unsigned short>
    {
        static const bool value = true;
    };

	template<>
	struct is_integral<char>
    {
        static const bool value = true;
    };

	template<>
	struct is_integral<const char>
    {
        static const bool value = true;
    };

	template<>
	struct is_integral<unsigned char>
    {
        static const bool value = true;
    };

	template<>
	struct is_integral<const unsigned char>
    {
        static const bool value = true;
    };

	template<>
	struct is_integral<float>
    {
        static const bool value = true;
    };

	template<>
	struct is_integral<const float>
    {
        static const bool value = true;
    };

	template<>
	struct is_integral<double>
    {
        static const bool value = true;
    };

	template<>
	struct is_integral<const double>
    {
        static const bool value = true;
    };

	template<>
	struct is_integral<long double>
    {
        static const bool value = true;
    };

	template<>
	struct is_integral<const long double>
    {
        static const bool value = true;
    };
}

#endif