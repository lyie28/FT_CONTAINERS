#include <iostream>
#ifndef STD
#include "../includes/map.hpp"
namespace opt=ft;
#else
#include <map>
namespace opt=std;
#endif

template<typename T1, typename T2>
opt::map<T1, T2> getSeqMap(int stop, T1 keyval, T2 val)
{
    opt::map<T1, T2> map;
    for (int i = 0; i < stop; i++)
    {
        map[keyval] = val;
        keyval++;
        val++;
    }
    return map;
}

void mapConstructorsAcess(void)
{
    std::cout << "Void constructor + fill with []" << std::endl;
    opt::map<int, std::string> map1;

	map1[231] = "Laura";
    map1[354] = "Manon";
	map1[445] = "Samantha";
	map1[486] = "John";
    map1[229] = "Aurelie";
	map1[247] = "Margot";
	map1[536] = "Em";
	map1[285] = "Claire";
    map1[423] = "Emzie";
	map1[602] = "Bill";
    map1[903] = "Ben";
	map1[825] = "flowerpot";
	map1[756] = "men";
	map1[162] = "Theo";
	map1[317] = "Cecilia";
	map1[208] = "Theresa";
	map1[759] = "Isma";
    map1[201] = "Simon";
	map1[272] = "Samoa";
	map1[292] = "Samosa";
	map1[336] = "doggo";
	map1[387] = "cat";
	map1[189] = "meow";

    std::cout << "Creating copy map with copy constructor" << std::endl;
    opt::map<int, std::string> map2(map1);

    std::cout << "Creating copy map with =" << std::endl;
    opt::map<int, std::string> map3 = map1;

    opt::map<int, std::string>::iterator it = map1.begin();
     opt::map<int, std::string>::iterator end = map1.end();

    std::cout << "Creating map with same content using range constructor" << std::endl;
    opt::map<int, std::string> map4(it, end);

  
    opt::map<int, std::string>::iterator it2 = map2.begin();
    opt::map<int, std::string>::iterator it3 = map3.begin();
    opt::map<int, std::string>::iterator it4 = map4.begin();

    for (; it != end; it++ )
    {
        if (it2 == map2.end())
            std::cout << "Problem" << std::endl;
        if (it3 == map3.end())
            std::cout << "Problem" << std::endl;
        std::cout << "map 1 next values: " << (*it).first << " : " << (*it).second << std::endl;
        std::cout << "map 2 next values: " << (*it2).first << " : " << (*it2).second << std::endl;
        std::cout << "map 3 next values: " << (*it3).first << " : " << (*it3).second << std::endl;
        std::cout << "map 4 next values: " << (*it4).first << " : " << (*it4).second << std::endl;
        it2++;
        it4++;
        it3++;
    }
    if (map1.size() == map2.size() && map1.size() == map3.size() && map1.size() == map4.size())
        std::cout << "sizes are equal" << std::endl;
    if (map1.get_allocator() == map2.get_allocator() && map1.get_allocator() == map3.get_allocator())
        std::cout << "allocators of copies are the same" << std::endl;
    std::cout << "creating new range map with 6 values from map1" << std::endl;
    opt::map<int, std::string> map5(map1.find(285), map1.find(423));
    it = map5.begin();
    end = map5.end();
    for (; it != end; it++ )
    {
        std::cout << "map 5 next values: " << (*it).first << " : " << (*it).second << std::endl;
    }
    std::cout << "map5 size is: " << map5.size() << std::endl;
    std::cout << "changing values to 'sandwich' using [] operator" << std::endl;
    it = map5.begin();
    end = map5.end();
    for (; it != end; it++ )
    {
        map5[((*it).first)] = "sandwich";
        std::cout << "new map 5 values are: " << (*it).first << " : " << (*it).second << std::endl;
    }
    return;
}

void mapAllocator(void)
{
    std::cout << "Getting allocator from a int<>float map" << std::endl;
    opt::map<const int, float> map1;
    opt::pair<const int,float> *pair1;
    std::cout << "Building a pair with the allocator" << std::endl;
    pair1 = map1.get_allocator().allocate(1);
    map1.get_allocator().construct(pair1, opt::pair<int, float>(10, 9.99));
    std::cout << "My pair is: " << pair1->first << " : " << pair1->second << std::endl;
    std::cout << "Getting allocator from a std::string<>char map" << std::endl;
    opt::map<const std::string, char> map2;
    opt::pair<const std::string, char> *pair2;
    std::cout << "Building a pair with the allocator" << std::endl;
    pair2 = map2.get_allocator().allocate(1);
    map2.get_allocator().construct(pair2, opt::pair<std::string, char>("superman", 'S'));
    std::cout << "My pair is: " << pair2->first << " : " << pair2->second << std::endl;
    map1.get_allocator().destroy(pair1);
    map1.get_allocator().deallocate(pair1, 1);
    map2.get_allocator().destroy(pair2);
    map2.get_allocator().deallocate(pair2, 1);
}

template<typename T>
void mapIteratorMaths(T it, T start, T end, bool standard)
{
    (void)standard;
    std::cout << "Set iterator to point at start of map" << std::endl;
    std::cout << "creaing new iterators with copy constructor and = operator to it1" << std::endl;
    T it2(start);
    T it3 = it;
    for (; it != end; it++ )
    {
        std::cout << "it1 next values: " << (*it).first << " : " << it->second << std::endl;
        std::cout << "it2 next values: " << (*it2).first << " : " << it2->second << std::endl;
        std::cout << "it3 next values: " << (*it3).first << " : " << it3->second << std::endl;
        it2++;
        it3++;
    }
    it3--;
    std::cout << "it3-- performed. Value is now: " << (*it3).first << " : " << it3->second << std::endl;
    --it3;
    std::cout << "--it3 performed. Value is now: " << (*it3).first << " : " << it3->second << std::endl;
    std::cout << "Does it3 == it2?" << std::endl;
    if (it3 == it2)
        std::cout << "YES" << std::endl;
    else
        std::cout << "NO" << std::endl;
    std::cout << "Does it3 != it2?" << std::endl;
    if (it3 != it2)
        std::cout << "YES" << std::endl;
    else
        std::cout << "NO" << std::endl;
    std::cout << "Does it1 == it2?" << std::endl;
    if (it == it2)
        std::cout << "YES" << std::endl;
    else
        std::cout << "NO" << std::endl;
    std::cout << "Does it1 != it2?" << std::endl;
    if (it != it2)
        std::cout << "YES" << std::endl;
    else
        std::cout << "NO" << std::endl;
     std::cout << "Does it1 == map1.end()" << std::endl;
    if (it == end)
        std::cout << "YES" << std::endl;
    else
        std::cout << "NO" << std::endl;
    std::cout << "extra it3--" << std::endl;
    it3--;
    std::cout << "printing ++it3->first: " << it3++->first << ": and it3++->second: " << it3++->second << std::endl;
    std::cout << "it3 now: " << (*it3).first << " : " << it3->second << std::endl;
}

void mapBiIterator(void)
{
    opt::map<int, std::string> map1;
	map1[231] = "Laura";
    map1[354] = "Manon";
	map1[445] = "Samantha";
	map1[486] = "John";
    map1[229] = "Aurelie";
	map1[247] = "Margot";
	map1[536] = "Em";
	map1[285] = "Claire";
    map1[423] = "Emzie";
    opt::map<int, std::string>::iterator it1;
    it1 = map1.begin();
    mapIteratorMaths(it1, map1.begin(), map1.end(), true);
    std::cout << "-----------------------------------" << std::endl << std::endl;

    std::cout << "same test with const iterator" << std::endl;
    opt::map<int, std::string>::const_iterator cit1 = map1.begin();
    opt::map<int, std::string>::const_iterator cstart = map1.begin();
    opt::map<int, std::string>::const_iterator cend = map1.end();
    mapIteratorMaths(cit1, cstart, cend, true);
    std::cout << "-----------------------------------" << std::endl << std::endl;

    std::cout << "same test with rev iterators" << std::endl;
    opt::map<int, std::string>::reverse_iterator it2 = map1.rbegin();
    mapIteratorMaths(it2, map1.rbegin(), map1.rend(), false);
    std::cout << "-----------------------------------" << std::endl << std::endl;

    mapIteratorMaths(it2, map1.rbegin(), map1.rend(), false);
    std::cout << "same test with const rev iterator" << std::endl;
    opt::map<int, std::string>::const_reverse_iterator cit2 = map1.rbegin();
    opt::map<int, std::string>::const_reverse_iterator rcstart = map1.rbegin();
    opt::map<int, std::string>::const_reverse_iterator rcend = map1.rend();
    mapIteratorMaths(cit2, rcstart, rcend, false);
    std::cout << "-----------------------------------" << std::endl << std::endl;
}

template<typename T>
void maptorPrinter(T it, T end)
{
    for (; it != end; it++ )
    {
        std::cout << "it1 next values: " << (*it).first << " : " << it->second << std::endl;
    }
}

void mapErase(void)
{
    int numbers[20] = { 1, 8, 5, 69, 67, 2, 0, 10, 12, 99, 55, 71, 77, 60, 50, 13, 18, 22, 73, 64};
    std::cout << "TESTING ERASE STANDARD: 30 erases from a tree of 100 int-int" << std::endl;
    opt::map<int, int> m1 = getSeqMap(100, 0, 1);
    for (int i = 0; i < 20; i++)
    {
        m1.erase(numbers[i]);
        maptorPrinter(m1.begin(), m1.end());
        std::cout << "size is: " << m1.size() << std::endl;
    }
    std::cout << std::endl;
    std::cout << "TESTING ERASE IT: erases 5 elements from tree" << std::endl;
    opt::map<int, int> m2 = getSeqMap(100, 0, 1);
    opt::map<int, int>::iterator it = m2.find(59);
    m2.erase(it);
    it = m2.find(69);
    m2.erase(it);
    it = m2.find(31);
    m2.erase(it);
    it = m2.find(64);
    m2.erase(it);
    it = m2.find(33);
    m2.erase(it);
    it = m2.find(32);
    m2.erase(it);
    maptorPrinter(m2.begin(), m2.end());
    std::cout <<std::endl << "size is: " << m2.size() << std::endl;
    std::cout << "TESTING ERASE RANGE" << std::endl;
    opt::map<int, int> m3 = getSeqMap(100, 0, 1);
    std::cout << "erasing elements 5 to 10" << std::endl;
    m3.erase(m3.find(5), m3.find(10));
    maptorPrinter(m3.begin(), m3.end());
    std::cout << "size is: " << m3.size() << std::endl;
    std::cout << "erasing elements 90 to 99" << std::endl;
    m3.erase(m3.find(90), m3.find(99));
    maptorPrinter(m3.begin(), m3.end());
    std::cout << "size is: " << m3.size() << std::endl;
}

void mapInsert(void)
{
    std::cout << "MASSIVE INSERT FOR TIME TESTING" << std::endl;
    opt::map<int, int> t1;
    for (int i = 0; i < 10000; i++)
    {
        opt::pair<int, int> time1(i, i);
        t1.insert(time1);
    }
    maptorPrinter(t1.begin(), t1.end());
    std::cout << "Inserting 20 elements into map" << std::endl;
    int numbers[20] = { 1, 8, 5, 69, 67, 2, 0, 10, 12, 99, 55, 71, 77, 60, 50, 13, 18, 22, 73, 64};
    int numbers2[20] = { 46, 51, 97, 1, 63, 3, 48, 54, 78, 5, 85, 10, 12, 52, 36, 86, 4, 92, 57, 80};
    opt::map<int, int> m1;
    for (int i = 0; i < 20; i++)
    {
        opt::pair<int, int> p1(numbers[i], i);
        m1.insert(p1);
        maptorPrinter(m1.begin(), m1.end());
        std::cout << "size is: " << m1.size() << std::endl;
    }
    std::cout << "ensuring we have an element over 100 by inserting 1 now!" << std::endl;
    opt::pair<int, int> custom(101, 10);
    m1.insert(custom);
    std::cout << std::endl;
    std::cout << "TESTING INSERT RANGE: inserting all values from m1 up to 100" << std::endl;
    opt::map<int, int> m2;
    m2.insert(m1.begin(), m1.upper_bound(100));
    for (int i = 0; i < 20; i++)
    {
        opt::pair<int, int> p1(numbers2[i], i);
        m2.insert(p1);
        maptorPrinter(m2.begin(), m2.end());
        std::cout << "size is: " << m2.size() << std::endl;
    }
    std::cout << std::endl;
    if (m1.empty())
        std::cout << "Map1 is empty" << std::endl;
    std::cout << "clearing map1" << std::endl;
    m1.clear();
    if (m1.empty())
        std::cout << "Map1 is empty" << std::endl;
    std::cout << "TESTING INSERT HINT: inserting 20 vals with hint" << std::endl;
    opt::map<int, int> m3;
    for (int i = 0; i < 20; i++)
    {
        m3.insert(m3.begin(), opt::pair<int, int>(i, i));
        maptorPrinter(m3.begin(), m3.end());
        std::cout << "size is: " << m3.size() << std::endl;
    }
}

void mapWithDiffComp(void)
{
    std::cout << "creating standard map with default less than compare" << std::endl;
    opt::map<std::string, int> map1;
    std::cout << "creating custom map with std::greater function" << std::endl;
    opt::map<std::string, int, std::greater<std::string> > map2;
    std::cout << "map with less than function: " << std::endl;
    map1["Laura"] = 9;
    map1["Manon"] = 10;
	map1["Samantha"] = 11;
	map1["John"] = 5;
    map1["Aurelie"] = 4;
	map1["Margot"] = 1;
	map1["Em"] = 0;
	map1["Claire"] = -3;
    map1["Emzie"] = 99;
    opt::map<std::string, int>::iterator it;
    it = map1.begin();
     for (; it != map1.end(); it++ )
    {
        std::cout << "it1 next values: " << (*it).first << " : " << it->second << std::endl;
    }
    std::cout << "------------------------------------" << std::endl << std::endl;
    
    std::cout << "DEFAULT LESS THAN: is key Alpha <<less than>> Beta?" << std::endl;
    opt::map<std::string, int>::key_compare comp_func = map1.key_comp();
    if (comp_func("Alpha", "Beta"))
        std::cout << "YES IT IS" << std::endl;
    else
        std::cout << "Nope it is not" << std::endl;
    std::cout << "DEFAULT LESS THAN: is Alpha, 10 pair less than Beta, 0 pair?" << std::endl;
    opt::map<std::string, int>::value_compare comp_val = map1.value_comp();
    if (comp_val(opt::pair<std::string, int>("alpha", 10), opt::pair<std::string, int>("Beta", 0)))
        std::cout << "YES IT IS" << std::endl;
    else
       std::cout << "Nope it is not" << std::endl;
    std::cout << "------------------------------------" << std::endl << std::endl;
    
    std::cout << "map with greater than function: " << std::endl;
    std::cout << "map with less than function: " << std::endl;
    map2["Laura"] = 9;
    map2["Manon"] = 10;
	map2["Samantha"] = 11;
	map2["John"] = 5;
    map2["Aurelie"] = 4;
	map2["Margot"] = 1;
	map2["Em"] = 0;
	map2["Claire"] = -3;
    map2["Emzie"] = 99;
    opt::map<std::string, int>::iterator it2;
    it2 = map2.begin();
     for (; it2 != map2.end(); it2++ )
    {
        std::cout << "it2 next values: " << (*it2).first << " : " << it2->second << std::endl;
    }
    std::cout << "------------------------------------" << std::endl << std::endl;
    
    std::cout << "GREATER THAN: is key Alpha <<less than>> Beta?" << std::endl;
    opt::map<std::string, int, std::greater<std::string> >::key_compare comp_func2 = map2.key_comp();
    if (comp_func2("Alpha", "Beta"))
        std::cout << "YES IT IS" << std::endl;
    else
        std::cout << "Nope it is not" << std::endl;
    std::cout << "GREATER THAN: is Alpha, 10 pair less than Beta, 0 pair?" << std::endl;
    opt::map<std::string, int, std::greater<std::string> >::value_compare comp_val2 = map2.value_comp();
    if (comp_val2(opt::pair<std::string, int>("alpha", 10), opt::pair<std::string, int>("Beta", 0)))
        std::cout << "YES IT IS" << std::endl;
    else
      std::cout << "Nope it is not" << std::endl;
    std::cout << "------------------------------------" << std::endl << std::endl;
    opt::map<std::string, int >::iterator bound1;
    opt::map<std::string, int >::iterator bound2;
    bound1 = map1.lower_bound("Emzie");
    std::cout << "lower_bound(Emzie) is: " << bound1->first << " : " << bound1->second << std::endl;
    bound1 = map1.lower_bound("z");
    if (bound1 != map1.end())
       std::cout << "bound1(z) is valid" << std::endl;
    else
       std::cout << "bound1(z) is not valid" << std::endl;
    bound2 = map1.upper_bound("Manon");
    std::cout << "upper_bound(Manon) is: " << bound2->first << " : " << bound2->second << std::endl;
    opt::pair < opt::map<std::string, int >::iterator, opt::map<std::string, int >::iterator > pair1;
    pair1 = map1.equal_range("middle");
    std::cout << "equal_range(middle) is: " << std::endl;
    while (pair1.first != pair1.second)
    {
        std::cout << "element is: " << pair1.first->first << " : " << pair1.first->second << std::endl;
        pair1.first++;
    }
    pair1 = map2.equal_range("Laura");
    std::cout << "equal_range(Laura) is: " << std::endl;
    while (pair1.first != pair1.second)
    {
        std::cout << "element is: " << pair1.first->first << " : " << pair1.first->second << std::endl;
        pair1.first++;
    }
    std::cout << "------------------------------------" << std::endl << std::endl;

    opt::map<std::string, int, std::greater<std::string> >::iterator it1;
    opt::map<std::string, int, std::greater<std::string> >::iterator b2;
    it1 = map2.lower_bound("middle");
    std::cout << "lower_bound(middle) is: " << it1->first << " : " << it1->second << std::endl;
    b2 = map2.upper_bound("middle");
    b2 = map2.lower_bound("z");
    if (b2 != map2.end())
        std::cout << "there is something greater or equal than z" << std::endl;
    std::cout << "upper_bound(middle) is: " << b2->first << " : " << b2->second << std::endl;
    opt::pair < opt::map<std::string, int, std::greater<std::string> >::iterator, opt::map<std::string, int, std::greater<std::string> >::iterator > p1;
    p1 = map2.equal_range("middle");
    std::cout << "equal_range(middle) is: " << std::endl;
    while (p1.first != p1.second)
    {
        std::cout << "element is: " << p1.first->first << " : " << p1.first->second << std::endl;
        p1.first++;
    }
    p1 = map2.equal_range("Laura");
    std::cout << "equal_range(Laura) is: " << std::endl;
    while (p1.first != p1.second)
    {
        std::cout << "element is: " << p1.first->first << " : " << p1.first->second << std::endl;
        p1.first++;
    }
}

void findCount(void)
{
    int numbers2[20] = { 46, 51, 197, 1, 63, 3, 48, 254, 78, 5, 485, 10, 12, 52, 836, 86, 444, 92, 57, 80};
    opt::map<int, int> m1 = getSeqMap(100, 0, 100);
    opt::map<int, int>::iterator it;
    int i = 0;
    std::cout << "searching for values which may or may not be in map with find and count" << std::endl;
    while(i < 20)
    {
        it = m1.find(numbers2[i]);
        if (it != m1.end())
            std::cout << "found element";
        std::cout << "count ret: " << m1.count(numbers2[i]) << std::endl;
        i++;
    }

}
void mapSwap(void)
{
   opt::map<int, std::string> map1;
   opt::map<int, std::string> map2;
    map1[231] = "Laura";
    map1[354] = "Manon";
    map1[445] = "Samantha";
    map1[486] = "John";
    map1[229] = "Aurelie";
    map1[247] = "Margot";
    map1[536] = "Em";
    map1[285] = "Claire";
    map1[423] = "Emzie";

    std::cout << "Building map1 with values and map2 empty" << std::endl;
    std::cout << "map1: " << std::endl;
    opt::map<int, std::string>::iterator it2;
    it2 = map1.begin();
    for (; it2 != map1.end(); it2++ )
    {
        std::cout << "it2 next values: " << (*it2).first << " : " << it2->second << std::endl;
    }
    std::cout << "size is: " << map1.size() << std::endl;
    std::cout << "map2: " << std::endl;
    it2 = map2.begin();
    for (; it2 != map2.end(); it2++ )
    {
        std::cout << "it2 next values: " << (*it2).first << " : " << it2->second << std::endl;
    }
    std::cout << "size is: " << map2.size() << std::endl;
    std::cout << "PERFORMING SWAP" << std::endl;
    std::cout << "map1: " << std::endl;
    it2 = map1.begin();
    for (; it2 != map1.end(); it2++ )
    {
        std::cout << "it2 next values: " << (*it2).first << " : " << it2->second << std::endl;
    }
    std::cout << "size is: " << map1.size() << std::endl;
    std::cout << "map2: " << std::endl;
     it2 = map2.begin();
    for (; it2 != map2.end(); it2++ )
    {
        std::cout << "it2 next values: " << (*it2).first << " : " << it2->second << std::endl;
    }
    std::cout << "size is: " << map2.size() << std::endl;
}

void mapNonMember(void)
{
    opt::map<int, char> map1;
    map1 = getSeqMap<int, char>(10, 0, 'a');
    opt::map<int, char> map2;
    map2 = getSeqMap<int, char>(10, 0, 'a');
    map2[5] = 'z';
    std::cout << "map1: ";
    maptorPrinter(map1.begin(), map1.end());
    std::cout << std::endl << "map2: ";
    maptorPrinter(map2.begin(), map2.end());
    std::cout << std::endl;
    if (map1 == map2)
        std::cout << "map1 == map2" << std::endl;
    else 
        std::cout << "NOT TRUE: map1 == map2" << std::endl;
    if (map1 != map2)
        std::cout << "map1 != map2" << std::endl;
    else 
        std::cout << "NOT TRUE: map1 != map2" << std::endl;
    if (map1 < map2)
        std::cout << "map1 < map2" << std::endl;
    else 
        std::cout << "NOT TRUE: map1 <= map2" << std::endl;
    if (map1 <= map2)
        std::cout << "map1 <= map2" << std::endl;
    else 
        std::cout << "NOT TRUE: map1 ,= map2" << std::endl;
    if (map1 > map2)
        std::cout << "map1 > map2" << std::endl;
    else 
        std::cout << "NOT TRUE: map1 > map2" << std::endl;
     if (map1 >= map2)
        std::cout << "map1 >= map2" << std::endl;
    else 
        std::cout << "NOT TRUE: map1 >= map2" << std::endl;
    map1[5] = 'z';
    std::cout << "map1: ";
    maptorPrinter(map1.begin(), map1.end());
    std::cout << std::endl << "map2: ";
    maptorPrinter(map2.begin(), map2.end());
    std::cout << std::endl;
    if (map1 == map2)
        std::cout << "map1 == map2" << std::endl;
    else 
        std::cout << "NOT TRUE: map1 == map2" << std::endl;
    if (map1 != map2)
        std::cout << "map1 != map2" << std::endl;
    else 
        std::cout << "NOT TRUE: map1 != map2" << std::endl;
    if (map1 < map2)
        std::cout << "map1 < map2" << std::endl;
    else 
        std::cout << "NOT TRUE: map1 <= map2" << std::endl;
    if (map1 <= map2)
        std::cout << "map1 <= map2" << std::endl;
    else 
        std::cout << "NOT TRUE: map1 ,= map2" << std::endl;
    if (map1 > map2)
        std::cout << "map1 > map2" << std::endl;
    else 
        std::cout << "NOT TRUE: map1 > map2" << std::endl;
     if (map1 >= map2)
        std::cout << "map1 >= map2" << std::endl;
    else 
        std::cout << "NOT TRUE: map1 >= map2" << std::endl;
    std::cout << "TESTING SWAP" << std::endl;
    map1.swap(map2);
     std::cout << "map1: ";
    maptorPrinter(map1.begin(), map1.end());
    std::cout << std::endl << "map2: ";
    maptorPrinter(map2.begin(), map2.end());
    std::cout << std::endl;
    void *V1pre = &map1;
    void *V2pre = &map2;
    std::cout << "TESTING SWAP with an empty array, swapping map2 with empty maptor" << std::endl;
    if (&map1 == V1pre)
        std::cout << "address of map1 has not changed" << std::endl;
    else
        std::cout << "address was " << V1pre << " and is now: " << &map1 << std::endl;
    if (&map2 == V2pre)
        std::cout << "address of map2 has not changed" << std::endl;
    else
        std::cout << "address was " << V2pre << " and is now: " << &map2 << std::endl;
    opt::map<int, char> map3;
    void *V3pre = &map3;
    map2.swap(map3);
    std::cout << "map2: ";
    maptorPrinter(map2.begin(), map2.end());
    std::cout << std::endl << "map3: ";
    maptorPrinter(map3.begin(), map3.end());
    std::cout << std::endl;
    if (&map2 == V2pre)
        std::cout << "address of map2 has not changed" << std::endl;
    else
        std::cout << "address was " << V2pre << " and is now: " << &map2 << std::endl;
    if (&map3 == V3pre)
        std::cout << "address of map3 has not changed" << std::endl;
    else
        std::cout << "address was " << V3pre << " and is now: " << &map3 << std::endl;
}


