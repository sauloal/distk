//#include <cassert>
#include <iostream>
#include <functional>

#ifndef _MAX_VAL_
#define _MAX_VAL_ 10000000
#endif

#ifdef _LIST_
#include <list>
#else
#include <vector>
#endif

#ifndef _SET_
#include <queue>
#else
#include <set>
#endif

//https://stackoverflow.com/questions/6498098/are-there-any-sorted-collections-in-c
//https://stackoverflow.com/questions/2439283/how-can-i-create-min-stl-priority-queue

//typedef unsigned long long int uint;

#ifndef _SET_
#ifdef _LIST_
template<class T> using min_heap = std::priority_queue<T, std::list<T>  , std::greater<T> >;
#else
template<class T> using min_heap = std::priority_queue<T, std::vector<T>, std::greater<T> >;
#endif
#else
template<class T> using min_set  = std::set<           T,                 std::greater<T> >;
#endif


int main() {
#ifndef _SET_
    min_heap<uint> q;
#else
    min_set<uint>  q;
#endif

    std::cout << "Creating";
#ifndef _SET_
    std::cout << " HEAP WITH";
#ifdef _LIST_
    std::cout << " LIST";
#else
    std::cout << " VECTOR";
#endif
    std::cout << " BACKEND";
#else
    std::cout << " SET";
#endif
    std::cout << std::endl;


    for ( uint i = 0; i < _MAX_VAL_; i++ ) {
#ifndef _SET_
        q.push(i);
#else
        q.insert(i);
#endif
    }

    std::cout << "Start Size " << q.size() << std::endl;

#ifndef _SET_
    while ( ! q.empty() ) {
#ifdef _DEBUG_
        std::cout << q.top() << std::endl;
#endif
        q.pop();
    }
#else
    for (std::set<uint>::iterator it=q.begin(); it!=q.end(); ++it) {
#ifdef _DEBUG_
      std::cout << ' ' << *it;
      std::cout << '\n';
#endif
    }
#endif

    std::cout << "End Size " << q.size() << std::endl;

    return 0;
}
