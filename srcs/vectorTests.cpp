#ifndef STD
#include "../includes/vector.hpp"
namespace opt=ft;
#else
#include <vector>
namespace opt=std;
#endif

void vectorPrinterInt(opt::vector<int> vec)
{
    opt::vector<int>::iterator it;
    opt::vector<int>::iterator ite = vec.end();
    std::cout << "Vector: ";
    for(it = vec.begin(); it != ite; it++)
    {
        std::cout << "[ " << *it << "] ";
    }
    std::cout << "\n";
    
    return;
}

void vectorPrinterChar(opt::vector<char> vec)
{
    opt::vector<char>::iterator it;
    opt::vector<char>::iterator ite = vec.end();
    std::cout << "Vector: ";
    for(it = vec.begin(); it != ite; it++)
    {
        std::cout << "[ " << *it << "] ";
    }
    std::cout << "\n";
    
    return;
}

opt::vector<int> getSeqVec(int size, int starting_value)
{
    opt::vector<int> myVec;
    for(int i = starting_value; i < (starting_value + size); i++)
    {
        myVec.push_back(i);
    }
    return (myVec);
}

void constructTests(void)
{
    std::cout << "testings constructors" << std::endl;
    std::cout << "Constructor type 1: empty container constructor" << std::endl;
    opt::vector<int> con1;
    vectorPrinterInt(con1);

    std::cout << "Constructor type 2: fill constructor: 10, 'z'" << std::endl;
    opt::vector<char> con2(10, 'z');
    vectorPrinterChar(con2);

    opt::vector<int> conExtra = getSeqVec(10, 0);
    std::cout << "Reverse iterator range constructor test: Count for 9->0" << std::endl;
    opt::vector<int> con3(conExtra.rbegin(), conExtra.rend());
    vectorPrinterInt(con3);

    std::cout << "Constructor type 3: range constructor 0->4" << std::endl;
    opt::vector<int> con4(conExtra.begin(), conExtra.begin() + 5);
    vectorPrinterInt(con4);

    std::cout << "Constructor type 4: copy constructor, copies prev" << std::endl;
    opt::vector<int> con5(con4);
    vectorPrinterInt(con5);

    return;
}

void miscTests(void)
{
    std::cout << "creating vectors" << std::endl;
    opt::vector<int> vec1;
    opt::vector<int> vec2;
    opt::vector<int> vec3;
    opt::vector<int> vec4;
    opt::vector<int> vec5;
    vec1 = getSeqVec(10, 0);
    vec2 = getSeqVec(10, 100);
    vec4 = getSeqVec(50, 5);
    vec5 = getSeqVec(20, 20);
    std::cout << "MY VECTORS: " << std::endl;
    vectorPrinterInt(vec1);
    vectorPrinterInt(vec2);
    vectorPrinterInt(vec3);
    vectorPrinterInt(vec4);
    vectorPrinterInt(vec5);
    std::cout << "\n";
    vec1 = vec3;
    std::cout << "Vec1 = vec3... VEC1 NOW:" << std::endl;
    vectorPrinterInt(vec1);
    vec3 = vec2;
    std::cout << "Vec3 = vec2... VEC3 NOW:" << std::endl;
    vectorPrinterInt(vec3);
    vec3 = vec4;
    std::cout << "Vec3 = vec4... VEC3 NOW:" << std::endl;
    vectorPrinterInt(vec3);
    vec4 = vec5;
    std::cout << "Vec4 = vec5... VEC5 NOW:" << std::endl;
    vectorPrinterInt(vec5);

    std::cout << "Testing get_allocator:" << std::endl;
    opt::vector<int> testAlloc;
    int *test;

    test = testAlloc.get_allocator().allocate(10);
    for (int i = 0; i < 10; i++)
    {
        testAlloc.get_allocator().construct(test + i, i);
    }
    std::cout << "allocated and constructed int * with values 0-9 using get_allocator. Int * conntains :" << std::endl;
    for (int i = 0; i < 10; i++)
       std::cout << test[i];
    std::cout << std::endl;
    for (int i = 0; i < 10; i++)
       testAlloc.get_allocator().destroy(&test[i]);
    testAlloc.get_allocator().deallocate(test, 10);
}

template<typename T>
void iteratorMaths(T it1, T it2, T start, T end)
{
    std::cout << "Test: ++ and *" << std::endl;
    for (; it1 != end; it1++)
        std::cout << "[" << *it1 << "] ";
    std::cout << std::endl;
    std::cout << "Test: -- and *" << std::endl;
    it1--;
     for (; it1 != start; it1--)
        std::cout << "[" << *it1 << "] ";
    std::cout << "[" << *it1 << "] " << std::endl;;
    std::cout << "*(++it1): " << *(++it1) << std::endl;
    std::cout << " Now it1 is: " << *it1 << std::endl;
    std::cout << "*(--it1): " << *(--it1) << std::endl;
    std::cout << " Now it1 is: " << *it1 << std::endl;
    std::cout << "*it1++: " << *it1++ << std::endl;
    std::cout << " Now it1 is: " << *it1 << std::endl;
    std::cout << "*it1--: " << *it1-- << std::endl;
    std::cout << " Now it1 is: " << *it1 << std::endl;
    it2 = it1 + 5;
    std::cout << "it2 = it1 + 5. *It2 =" << *it2 << std::endl;
    std::cout << "is it2 > it1?" << std::endl;
    if (it2 > it1)
        std::cout << "YES" << std::endl;
    std::cout << "is it1 < it12?" << std::endl;
    if (it1 < it2)
        std::cout << "YES" << std::endl;
    std::cout << "is it2 <= it1?" << std::endl;
    if(it2 <= it1)
        std::cout << "YES" << std::endl;
    else
        std::cout << "NO" << std::endl;
    it2 = it2 - 2;
    std::cout << "it2 = it2 - 2. *It2 =" << *it2 << std::endl;
    it2 = it1;
    std::cout << "it2 = it1. *It2 =" << *it2 << std::endl;
    if (it2 == it1)
        std::cout << "Yes, it2 == it1 now" << std::endl;
    std::cout << "is it2 >= it1?" << std::endl;
    if(it2 >= it1)
        std::cout << "YES" << std::endl;
    if (it2 != it1)
        std::cout << "it1 != it2" << std::endl;
    std::cout << "*it1 = 999. *it-> " << *it1 << " and *it2" << *it2 << std::endl;
    it1 = 5 + it1;
    std::cout << "it1 = 5 + it1. *it1->" << *it1 << std::endl;
    std::cout << "Resetting it1 to 0 + it2 to it1 + 2..." << std::endl;;
    it1 = start;
    it2 = it1 + 2;
    std::cout << "it2 - it1 is: " << (it2 - it1) << std::endl;
    std:: cout << "it1 += 2: " << *(it1 += 2) << std::endl;
    std:: cout << "it1 -= 2: " << *(it1 -= 2) << std::endl;
    std::cout << "it1[5] is: " << it1[5] << std::endl;
}

void iteratorTests(void)
{
    std::cout << "standard iterator tests" << std::endl;
    opt::vector<int> vec1;
    vec1 = getSeqVec(10, 0);
    opt::vector<int>::iterator it1 = vec1.begin();
    opt::vector<int>::iterator it2 = vec1.begin();
    iteratorMaths(it1, it2, vec1.begin(), vec1.end());
    std::cout << "const iterator tests" << std::endl;
    opt::vector<int> vec2;
    vec2 = getSeqVec(10, 0);
    opt::vector<int>::const_iterator it3 = vec2.begin();
    opt::vector<int>::const_iterator it4 = vec2.begin();
    opt::vector<int>::const_iterator start = vec2.begin();
    opt::vector<int>::const_iterator end = vec2.end();
    iteratorMaths(it3, it4, start, end);
    std::cout << "comparing const and non-const iterators" << std::endl;
    if (it1 <= it3)
        std::cout << "it1 <= it3" << std::endl;;
    if (it4 != it2)
        std::cout << "it4 != it2" << std::endl;
}

void reverseIteratorTests(void)
{
    std::cout << "reverse iterator tests" << std::endl;
    opt::vector<int> vec1;
    vec1 = getSeqVec(10, 0);
    opt::vector<int>::reverse_iterator it1 = vec1.rbegin();
    opt::vector<int>::reverse_iterator it2 = vec1.rbegin();
    iteratorMaths(it1, it2, vec1.rbegin(), vec1.rend());
    std::cout << "const reverse iterator tests" << std::endl;
    opt::vector<int> vec2;
    vec2 = getSeqVec(10, 0);
    opt::vector<int>::const_reverse_iterator it3 = vec2.rbegin();
    opt::vector<int>::const_reverse_iterator it4 = vec2.rbegin();
    opt::vector<int>::const_reverse_iterator start = vec2.rbegin();
    opt::vector<int>::const_reverse_iterator end = vec2.rend();
    iteratorMaths(it3, it4, start, end);
    std::cout << "base + values test" << std::endl;
    opt::vector<int> vec3;
    vec3 = getSeqVec(10, 0);
    opt::vector<int>::iterator it = vec3.begin() + 3;
    opt::reverse_iterator<opt::vector<int>::iterator> revIt(it);
    std::cout << "*it should be 3:  " << *it << '\n' << "*revIt should be 2: " << *revIt << '\n' 
    << "*revIt.base() should be 3 " << *revIt.base() << '\n'
    << "*(revIt.base()-1) should be 2" << *(revIt.base() - 1) << '\n';
    std::cout << "comparing const and non-const iterators" << std::endl;
    if (it1 <= it3)
        std::cout << "it1 > it3" << std::endl;
    if (it4 != it2)
        std::cout << "it4 == it2" << std::endl;
    
}

void capacityTests(void)
{
    std::cout << "building empty vector: " << std::endl;
    opt::vector<int> vec1;
    if (vec1.empty())
        std::cout << "Vector is empty" << std::endl;
    std::cout << "Filling container: " << std::endl;
    vec1 = getSeqVec(10, 0);
     if (!vec1.empty())
        std::cout << "Vector is no longer empty" << std::endl;
    std::cout << "vec1 size is: " << vec1.size() << std::endl;
    opt::vector<int> vec2;
    std::cout << "empty vec size is: " << vec2.size() << std::endl;
    std::cout << "Max size is: " << vec2.max_size() << std::endl;
    std::cout << "Empty vector capacity is: " << vec2.capacity() << std::endl;
    std::cout << "Vec1 capacity is: " << vec1.capacity() << std::endl;
    std::cout << "changing vec 1 capacity to 50 using reserve..." << std::endl;
    vec1.reserve(50);
    std::cout << "Vec1 capacity is: " << vec1.capacity() << std::endl;
    std::cout << "changing vec 1 capacity to 1 using reserve..." << std::endl;
    vec1.reserve(1);
    try
    {
       std::cout << "Vec1 capacity is: " << vec1.capacity() << std::endl;
        std::cout << "changing vec 1 capacity to -1 using reserve..." << std::endl;
        vec1.reserve(-1);
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error caught: " << e.what() << '\n';
        std::cout << "Vec1 capacity is: " << vec1.capacity() << std::endl;
    }
    try
    {
       std::cout << "Vec1 capacity is: " << vec1.capacity() << std::endl;
        std::cout << "changing vec 1 capacity to max_size + 1 using reserve..." << std::endl;
        vec1.reserve(vec1.max_size() + 1);
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error caught: " << e.what() << '\n';
        std::cout << "Vec1 capacity is: " << vec1.capacity() << std::endl;

    }
}

void accessTests(void)
{
    opt::vector<int> vec1;
    vec1 = getSeqVec(10, 0);
    std::cout << "My vector is: ";
    vectorPrinterInt(vec1);
    vec1.front() = 111;
    std::cout << "vec1.front() = 111" << vec1.front() << std::endl;
    vec1.at(1) = 222;
    std::cout << "vec1.at(1) = 222" << vec1.at(1) << std::endl;
    vec1.back() = 999;
    std::cout << "vec1.back() = 999" << vec1.back() << std::endl;
    vec1[2] = 333;
    std::cout << "vec1[2] = 333" << vec1[2] << std::endl;
    std::cout << "My vector is: "; 
    vectorPrinterInt(vec1);
    try {
        std::cout << "vec1.at(100) = 666" << std::endl;
        vec1.at(100) = 666;
    }
    catch (std::out_of_range const& exc) {
        std::cout << "Caught error: " << exc.what() << std::endl;
    }
    try {
        std::cout << "vec1[100] = 666" << std::endl;
        vec1[100] = 666;
    }
    catch (std::out_of_range const& exc) {
        std::cout << "Caught error: " << exc.what() << std::endl;
    }
}

void modifierTests(void)
{
    /*pop_back*/
    std::cout << "Testing pop_back" << std::endl;
    opt::vector<int> popVec;
    popVec = getSeqVec(3, 0);
    std::cout << "popVec: ";
    vectorPrinterInt(popVec);
    popVec.pop_back();
    std::cout << "pop_back(): ";
    vectorPrinterInt(popVec);
    popVec.pop_back();
    std::cout << "pop_back(): ";
    vectorPrinterInt(popVec);
    popVec.pop_back();
    std::cout << "pop_back(): ";
    vectorPrinterInt(popVec);

    /*ERASE TESTS*/
    std::cout << "Testing erase" << std::endl;
    opt::vector<int> vec1;
    vec1 = getSeqVec(10, 0);
    std::cout << "Vec1: ";
    vectorPrinterInt(vec1);
    std::cout << "Result of erase element 5: " << *(vec1.erase(vec1.begin() + 5)) << std::endl;
    std::cout << "Vec1: ";
    vectorPrinterInt(vec1);
    std::cout << "Result of erase element 5 - 8: " << *(vec1.erase(vec1.begin() + 5, vec1.begin() + 8)) << std::endl;
    std::cout << "Vec1: ";
    vectorPrinterInt(vec1);

    /*swap*/
    std::cout << "Testing swap" << std::endl;
    opt::vector<int> vec2;
    vec2 = getSeqVec(10, 0);
    vec2[5] = 999;
    std::cout << "Vec1: ";
    vectorPrinterInt(vec1);
    std::cout << "Vec2: ";
    vectorPrinterInt(vec2);
    vec1.swap(vec2);
     std::cout << "Vec1: ";
    vectorPrinterInt(vec1);
    std::cout << std::endl << "Vec2: ";
    vectorPrinterInt(vec2);
    std::cout << std::endl;
    void *V1pre = &vec1;
    void *V2pre = &vec2;
    void *V1front = &(vec1.front());
    void *V2front = &(vec2.front());
    std::cout << "TESTING SWAP with an empty array, swapping vec2 with empty vector" << std::endl;
    if (&vec1 == V1pre && V1front == &(vec1.front()))
        std::cout << "address of vec1 has not changed" << std::endl;
    else
        std::cout << "address was " << V1pre << " and is now: " << &vec1 << std::endl;
    if (&vec2 == V2pre  && V2front == &(vec2.front()))
        std::cout << "address of vec2 has not changed" << std::endl;
     else
        std::cout << "address was " << V2pre << " and is now: " << &vec2 << std::endl;
    opt::vector<int> vec3;
    void *V3pre = &vec3;
    vec2.swap(vec3);
    std::cout << "Vec2: ";
    vectorPrinterInt(vec2);
    std::cout << std::endl << "Vec3: ";
    vectorPrinterInt(vec3);
    std::cout << std::endl;
    if (&vec2 == V2pre)
        std::cout << "address of vec2 has not changed" << std::endl;
    else
        std::cout << "address was " << V2pre << " and is now: " << &vec2 << std::endl;
    if (&vec3 == V3pre)
        std::cout << "address of vec3 has not changed" << std::endl;
    else
        std::cout << "address was " << V3pre << " and is now: " << &vec3 << std::endl;
    
    
    /*resize*/
    std::cout << "Vec1: ";
    vectorPrinterInt(vec1);
    std::cout << "resizing vec1 of size: " << vec1.size() << " to size(30)" << std::endl;
    vec1.resize(30);
    vectorPrinterInt(vec1);
    std::cout << "resizing vec1 of size: " << vec1.size() << " to size(0)" << std::endl;
    vec1.resize(0);
    vectorPrinterInt(vec1);
    std::cout << "resizing vec1 of size: " << vec1.size() << " to size(max_size + 1)" << std::endl;
    try {
        vec1.resize(vec1.max_size() + 1);
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error caught: " << e.what() << '\n';
    }
    vectorPrinterInt(vec1);
    std::cout << "resizing vec1 of size: " << vec1.size() << " to size(-99)" << std::endl;
    try {
        vec1.resize(-99);
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error caught: " << e.what() << '\n';
    }
    vectorPrinterInt(vec1);

    /*clear*/
    std::cout << "Clearing vec2 of size: " << vec2.size() << std::endl;
    vec1.clear();
    std::cout << "size is now: " << vec2.size() << std::endl;
    std::cout << "clearing vec3 of size: " << vec3.size() << std::endl;
    vec3.clear();
    std::cout << "size is now: " << vec3.size() << std::endl;
    
    /*INSERT TESTS*/
}

void insertTest(void)
{
    /*single element tests*/
    opt::vector<int> vec1;
    vec1 = getSeqVec(10, 0);
    std::cout << "Vec1: ";
    vectorPrinterInt(vec1);
    std::cout << "return val of .insert( begin + 5, 99): " << *(vec1.insert ( vec1.begin() + 5, 99)) << std::endl;
    std::cout << "size of vec is now: " << vec1.size() << std::endl;
    std::cout << "Vec1: ";
    vectorPrinterInt(vec1);
    opt::vector<int> vec2;
    std::cout << "Vec2: ";
    vectorPrinterInt(vec2);
    std::cout << "return val of .insert(begin, 99): " << *(vec2.insert ( vec2.begin(), 99)) << std::endl;
    std::cout << "size of vec is now: " << vec2.size() << std::endl;
    std::cout << "Vec2: ";
    vectorPrinterInt(vec2);

    /*fill tests*/
    std::cout << "Vec1: ";
    vectorPrinterInt(vec1);
    std::cout << "insert( begin + 5, 666, 5): " << std::endl;
    vec1.insert( vec1.begin() + 5, 666, 5);
    std::cout << "size of vec is now: " << vec1.size() << std::endl;
    std::cout << "Vec1: ";
    vectorPrinterInt(vec1);
    opt::vector<int> vec3;
    std::cout << "Vec3: ";
    vectorPrinterInt(vec3);
    std::cout << "insert(begin, 666, 7): " << std::endl;
    vec3.insert( vec3.begin(), 666, 7);
    std::cout << "size of vec is now: " << vec3.size() << std::endl;
    std::cout << "Vec3: ";
    vectorPrinterInt(vec3);
    std::cout << "insert(begin, 666, 7): " << std::endl;
    vec3.insert( vec3.begin(), 666, 7);
    std::cout << "size of vec is now: " << vec3.size() << std::endl;
    std::cout << "Vec3: ";
    vectorPrinterInt(vec3);
    std::cout << "insert(begin, 666, 0): " << std::endl;
    vec3.insert ( vec3.begin(), 666, 0);
    std::cout << "size of vec is now: " << vec3.size() << std::endl;
    std::cout << "Vec3: ";
    vectorPrinterInt(vec3);


    /*range tests*/
    opt::vector<int> vec4;
    std::cout << "Vec1: ";
    vectorPrinterInt(vec1);
    std::cout << "Vec4: ";
    vectorPrinterInt(vec4);
    std::cout << "rinsert( vec1.begin + 5, vec4.begin(), vec4.end()): " << std::endl;
    vec1.insert( vec1.begin() + 5,  vec4.begin(), vec4.end());
    std::cout << "size of vec is now: " << vec1.size() << std::endl;
    std::cout << "Vec1: ";
    vectorPrinterInt(vec1);
    std::cout << "Vec4: ";
    vectorPrinterInt(vec4);
    vectorPrinterInt(vec4);
    std::cout << "insert( vec4.begin, vec1.begin(), vec1.end()): " << std::endl;
    vec4.insert( vec4.begin(),  vec1.begin(), vec1.end());
    std::cout << "size of vec is now: " << vec1.size() << std::endl;
    std::cout << "Vec1: ";
    vectorPrinterInt(vec1);
    std::cout << "Vec4: ";
    vectorPrinterInt(vec4);
}

void nonMemberTests(void)
{
    opt::vector<int> vec1;
    vec1 = getSeqVec(10, 0);
    opt::vector<int> vec2;
    vec2 = getSeqVec(10, 0);
    vec2[5] = 999;
    std::cout << "Vec1: ";
    vectorPrinterInt(vec1);
    std::cout << std::endl << "Vec2: ";
    vectorPrinterInt(vec2);
    std::cout << std::endl;
    if (vec1 == vec2)
        std::cout << "vec1 == vec2" << std::endl;
    else 
        std::cout << "NOT TRUE: vec1 == vec2" << std::endl;
    if (vec1 != vec2)
        std::cout << "vec1 != vec2" << std::endl;
    else 
        std::cout << "NOT TRUE: vec1 != vec2" << std::endl;
    if (vec1 < vec2)
        std::cout << "vec1 < vec2" << std::endl;
    else 
        std::cout << "NOT TRUE: vec1 <= vec2" << std::endl;
    if (vec1 <= vec2)
        std::cout << "vec1 <= vec2" << std::endl;
    else 
        std::cout << "NOT TRUE: vec1 ,= vec2" << std::endl;
    if (vec1 > vec2)
        std::cout << "vec1 > vec2" << std::endl;
    else 
        std::cout << "NOT TRUE: vec1 > vec2" << std::endl;
     if (vec1 >= vec2)
        std::cout << "vec1 >= vec2" << std::endl;
    else 
        std::cout << "NOT TRUE: vec1 >= vec2" << std::endl;
    vec2[5] = 5;
    std::cout << "Vec1: ";
    vectorPrinterInt(vec1);
    std::cout << std::endl << "Vec2: ";
    vectorPrinterInt(vec2);
    std::cout << std::endl;
    if (vec1 == vec2)
        std::cout << "vec1 == vec2" << std::endl;
    else 
        std::cout << "NOT TRUE: vec1 == vec2" << std::endl;
    if (vec1 != vec2)
        std::cout << "vec1 != vec2" << std::endl;
    else 
        std::cout << "NOT TRUE: vec1 != vec2" << std::endl;
    if (vec1 < vec2)
        std::cout << "vec1 < vec2" << std::endl;
    else 
        std::cout << "NOT TRUE: vec1 <= vec2" << std::endl;
    if (vec1 <= vec2)
        std::cout << "vec1 <= vec2" << std::endl;
    else 
        std::cout << "NOT TRUE: vec1 ,= vec2" << std::endl;
    if (vec1 > vec2)
        std::cout << "vec1 > vec2" << std::endl;
    else 
        std::cout << "NOT TRUE: vec1 > vec2" << std::endl;
     if (vec1 >= vec2)
        std::cout << "vec1 >= vec2" << std::endl;
    else 
        std::cout << "NOT TRUE: vec1 >= vec2" << std::endl;
    vec1.pop_back();
    std::cout << "Vec1: ";
    vectorPrinterInt(vec1);
    std::cout << std::endl << "Vec2: ";
    vectorPrinterInt(vec2);
    std::cout << std::endl;
    if (vec1 == vec2)
        std::cout << "vec1 == vec2" << std::endl;
    else 
        std::cout << "NOT TRUE: vec1 == vec2" << std::endl;
    if (vec1 != vec2)
        std::cout << "vec1 != vec2" << std::endl;
    else 
        std::cout << "NOT TRUE: vec1 != vec2" << std::endl;
    if (vec1 < vec2)
        std::cout << "vec1 < vec2" << std::endl;
    else 
        std::cout << "NOT TRUE: vec1 <= vec2" << std::endl;
    if (vec1 <= vec2)
        std::cout << "vec1 <= vec2" << std::endl;
    else 
        std::cout << "NOT TRUE: vec1 ,= vec2" << std::endl;
    if (vec1 > vec2)
        std::cout << "vec1 > vec2" << std::endl;
    else 
        std::cout << "NOT TRUE: vec1 > vec2" << std::endl;
     if (vec1 >= vec2)
        std::cout << "vec1 >= vec2" << std::endl;
    else 
        std::cout << "NOT TRUE: vec1 >= vec2" << std::endl;
    std::cout << "TESTING SWAP" << std::endl;
    vec1.swap(vec2);
     std::cout << "Vec1: ";
    vectorPrinterInt(vec1);
    std::cout << std::endl << "Vec2: ";
    vectorPrinterInt(vec2);
    std::cout << std::endl;
    void *V1pre = &vec1;
    void *V2pre = &vec2;
    void *V1front = &(vec1.front());
    void *V2front = &(vec2.front());
    std::cout << "TESTING SWAP with an empty array, swapping vec2 with empty vector" << std::endl;
    if (&vec1 == V1pre && V1front == &(vec1.front()))
        std::cout << "address of vec1 has not changed" << std::endl;
    else
        std::cout << "address was " << V1pre << " and is now: " << &vec1 << std::endl;
    if (&vec2 == V2pre  && V2front == &(vec2.front()))
        std::cout << "address of vec2 has not changed" << std::endl;
     else
        std::cout << "address was " << V2pre << " and is now: " << &vec2 << std::endl;
    opt::vector<int> vec3;
    void *V3pre = &vec3;
    vec2.swap(vec3);
    std::cout << "Vec2: ";
    vectorPrinterInt(vec2);
    std::cout << std::endl << "Vec3: ";
    vectorPrinterInt(vec3);
    std::cout << std::endl;
    if (&vec2 == V2pre)
        std::cout << "address of vec2 has not changed" << std::endl;
    else
        std::cout << "address was " << V2pre << " and is now: " << &vec2 << std::endl;
    if (&vec3 == V3pre)
        std::cout << "address of vec3 has not changed" << std::endl;
    else
        std::cout << "address was " << V3pre << " and is now: " << &vec3 << std::endl;
}