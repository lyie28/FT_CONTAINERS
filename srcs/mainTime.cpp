#include <iostream>
#include "vectorTests.cpp"
#include "stackTests.cpp"
#include "mapTests.cpp"

#include "../includes/map.hpp"

#include <sys/time.h>

typedef void (*ft_ptr)();

void	time_calculate( std::string str, ft_ptr my_function)
{
	struct timeval start, end;
    /*get time pre function*/
    gettimeofday(&start, 0);
    /*launch function*/
	(*(my_function))();
    /*get time at end of function*/
    gettimeofday(&end, 0);
    long seconds = end.tv_sec - start.tv_sec;
    long micro = end.tv_usec - start.tv_usec;
    double time_taken = seconds + micro * 1e-6;
    std::cerr << "Time taken by " << str << " is : " << std::fixed << time_taken << " sec" << std::endl;
}

void	vectorTests()
{
    std::cout << "-------------------------------------------" << std::endl;
    std::cout << "TESTING VECTOR" << std::endl << std::endl;
    std::cout << "TESTING CONSTRUCTORS" << std::endl << std::endl;
	constructTests();
    std::cout << "-------------------------------------------" << std::endl;
    std::cout << "TESTING EXTRAS" << std::endl << std::endl;
	miscTests();
    std::cout << "-------------------------------------------" << std::endl;
    std::cout << "TESTING ITERATORS" << std::endl << std::endl;
	iteratorTests();
    std::cout << "-------------------------------------------" << std::endl;
    std::cout << "TESTING REV ITERATORS" << std::endl << std::endl;
	reverseIteratorTests();
    std::cout << "-------------------------------------------" << std::endl;
    std::cout << "TESTING CAPACITY FUNCTIONS" << std::endl << std::endl;
	capacityTests();
    std::cout << "-------------------------------------------" << std::endl;
    std::cout << "TESTING ACCESS FUNCTIONS" << std::endl << std::endl;
	accessTests();
    std::cout << "-------------------------------------------" << std::endl;
    std::cout << "TESTING NON MEMBER FUNCTIONS" << std::endl << std::endl;
	nonMemberTests();
    std::cout << "-------------------------------------------" << std::endl;
    std::cout << "TESTING MODIFIER FUNCTIONS" << std::endl << std::endl;
	modifierTests();
    std::cout << "-------------------------------------------" << std::endl;
    std::cout << "TESTING INSERTS" << std::endl << std::endl;
	insertTest();
}

void	stackTests()
{
    std::cout << "-------------------------------------------" << std::endl;
    std::cout << "TESTING STACK" << std::endl << std::endl;
    std::cout << "TESTING CONSTRUCTORS, POP, PUSH, TOP, EMPTY & SIZE" << std::endl << std::endl;
	popPushStack();
    std::cout << "-------------------------------------------" << std::endl;
    std::cout << "TESTING NON MEMBER FUNCTIONS" << std::endl << std::endl;
	nonMemberstack();
    std::cout << "-------------------------------------------" << std::endl;
}

void mapTests()
{
    std::cout << "-------------------------------------------" << std::endl;
    std::cout << "TESTING MAP" << std::endl << std::endl;
    mapConstructorsAcess();
    std::cout << "-------------------------------------------" << std::endl;
    std::cout << "TESTING GET_ALLOCATOR" << std::endl << std::endl;
    mapAllocator();
    std::cout << "-------------------------------------------" << std::endl;
    std::cout << "TESTING ITERATOR" << std::endl << std::endl;
    mapBiIterator();
    std::cout << "-------------------------------------------" << std::endl;
    std::cout << "TESTING NON MEMBER" << std::endl << std::endl;
    mapNonMember();
    std::cout << "-------------------------------------------" << std::endl;
    std::cout << "TESTING WITH DIFFERENT CMP" << std::endl << std::endl;
    mapWithDiffComp();
    std::cout << "-------------------------------------------" << std::endl;
    std::cout << "TESTING ERASE + SIZE" << std::endl << std::endl;
    mapErase();
    std::cout << "-------------------------------------------" << std::endl;
    std::cout << "TESTING INSERT + EMPTY" << std::endl << std::endl;
    mapInsert();
    std::cout << "-------------------------------------------" << std::endl;
    std::cout << "TESTING SWAP IN CLASS" << std::endl << std::endl;
    mapSwap();
    std::cout << "-------------------------------------------" << std::endl;
    std::cout << "TESTING FIND-COUNT" << std::endl << std::endl;
    findCount();
}

int main(void)
{
    time_calculate( "VECTOR", &vectorTests );
    time_calculate( "STACK", &stackTests );
    time_calculate( "MAP", &mapTests );
}