//#include <cassert>
#include <iostream>
#include <functional>
#include <assert.h>
#include <algorithm>    // std::random_shuffle
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand
#include <vector>


/*

-D_DEBUG_

c++ set.cpp -Ofast -std=c++11 -o set_set_dflt       -D_SET_              && time ./set_set_dflt
c++ set.cpp -Ofast -std=c++11 -o set_set_alta       -D_SET_ -D_ALLOC_    && time ./set_set_alta
c++ set.cpp -Ofast -std=c++11 -o set_svec           -D_SVEC_             && time ./set_svec
c++ set.cpp -Ofast -std=c++11 -o set_queue_vec      -D_QUEUE_            && time ./set_queue_vec
//c++ set.cpp -Ofast -std=c++11 -o set_queue_vec_alta -D_QUEUE_ -D_ALLOC_  && time ./set_queue_vec_alta

//c++ set.cpp -Ofast -std=c++11 -o set_queue_lst -D_QUEUE_ -D_LIST_   && time ./set_queue_lst

*/

/*
saulo@SAULO-ASUS:~/dev/distk$ c++ set.cpp -Ofast -std=c++11 -o set_set_dflt  -D_SET_              && time ./set_set_dflt
Creating SET WITH DEFAULT ALLOCATOR
 MAX VAL 50000000
real    1m22.105s
user    1m18.938s
sys     0m3.156s

saulo@SAULO-ASUS:~/dev/distk$ c++ set.cpp -Ofast -std=c++11 -o set_set_alta  -D_SET_ -D_ALLOC_    && time ./set_set_alta
Creating SET WITH ALTERNATIVE ALLOCATOR
 MAX VAL 50000000
real    1m14.423s
user    1m13.031s
sys     0m1.391s

saulo@SAULO-ASUS:~/dev/distk$ c++ set.cpp -Ofast -std=c++11 -o set_svec      -D_SVEC_             && time ./set_svec
Creating SORTED VECTOR
 MAX VAL 50000000
real    7m51.379s
user    7m50.797s
sys     0m0.391s

saulo@SAULO-ASUS:~/dev/distk$ c++ set.cpp -Ofast -std=c++11 -o set_queue_vec -D_QUEUE_            && time ./set_queue_vec
Creating DEQUE WITH VECTOR BACKEND
 MAX VAL 50000000
real    0m38.604s
user    0m38.000s
sys     0m0.563s
*/

#ifndef _MAX_VAL_
#define _MAX_VAL_ 50000000
#endif


//https://stackoverflow.com/questions/6498098/are-there-any-sorted-collections-in-c
//https://stackoverflow.com/questions/2439283/how-can-i-create-min-stl-priority-queue

//typedef unsigned long long int uint;


#ifdef _SET_
    #include <set>
    #ifdef _ALLOC_
        #include "set_alloc.hpp"
        #define _DESC_ "SET WITH ALTERNATIVE ALLOCATOR"
        template<class T> using min_set = std::set< T, std::less<T>, bestAlloc<T> >;
    #else
        #define _DESC_ "SET WITH DEFAULT ALLOCATOR"
        #include <unordered_set>
        template<class T> using min_set = std::set< T, std::less<T> >;
        //template<class T> using min_set = std::unordered_set< T >;
        
    #endif
#else
    #ifdef _SVEC_
        #include "sorted_vector.hpp"
        #define _DESC_ "SORTED VECTOR"
        template<class T> using min_vec = sorted_vector< T >;
    #else
        #ifdef _QUEUE_
            #include <queue>
            #ifdef _LIST_
                #include <list>
                #define _DESC_ "DEQUE WITH LIST BACKEND"
                template<class T> using min_heap = std::priority_queue<T, std::list<T>  , std::less<T> >;
            #else
                #ifdef _ALLOC_
                    #include "set_alloc.hpp"
                    #include "sorted_vector.hpp"
                    #define _DESC_ "DEQUE WITH VECTOR BACKEND AND ALTERNATIVE ALLOCATOR"
                    template<class T> using min_heap = std::priority_queue<T, sorted_vector< T >, std::less<T> >;
                    //template<class T> using min_heap = std::priority_queue<T, std::vector<T, bestAlloc<T> >, std::less<T> >;
                #else
                    #define _DESC_ "DEQUE WITH VECTOR BACKEND"
                    //https://stackoverflow.com/questions/29235978/how-to-preallocatereserve-a-priority-queuevector
                    template<typename T>
                    class MyPQueue : public std::priority_queue<T, std::vector<T>, std::less<T> > {
                        public:
                            void reserve(size_t reserve_size) {
                                this->c.reserve(reserve_size);
                            }
                    };
                    template<class T> using min_heap = MyPQueue<T>;
                    //template<class T> using min_heap = std::priority_queue<T, std::vector<T>, std::less<T> >;
                #endif
            #endif
        #endif
    #endif
#endif

template <typename T>
class sorter {
    #ifdef _SET_
        min_set<T>  q;
    #endif
    #ifdef _SVEC_
        min_vec<T> q;
    #endif
    #ifdef _QUEUE_
        min_heap<T> q;
    #endif
    
    size_t curr;

    public:    
    sorter(): curr(0) {
        std::cout << "Creating " << _DESC_    << std::endl;
    }

    void add(T i) {
        #ifdef _SET_
        q.insert(i);
        #endif
        #ifdef _SVEC_
        q.push_back(i);
        #endif
        #ifdef _QUEUE_
        q.push(i);
        #endif
    }
    
    bool empty() {
        return q.empty();
    }
    
    T pop() {
        T v = 0;
        
        assert(!q.empty());
        
        #ifdef _SET_
        auto it=q.end();
        v += *it;
        it--;
        q.erase(it);
        #endif

        #ifdef _SVEC_
        auto it = q.end();
        v  += *it;
        it--;
        q.erase(it);
        #endif

        #ifdef _QUEUE_
        v += q.top();
        q.pop();
        #endif

        return v;
    }
    
    size_t size() {
        return q.size();
    }
    
    void reserve(size_t s) {
        #ifdef _SET_
        q.get_allocator().allocate(s);
        #else
        q.reserve(s);
        #endif
    }
};


int main() {
    //http://www.cplusplus.com/reference/algorithm/random_shuffle/
    std::srand ( unsigned ( std::time(0) ) );
    std::vector<uint> v;
    sorter <uint>     q;

    std::cout << " MAX VAL " << _MAX_VAL_ << std::endl;

    std::cout << "  Creating " << v.size() << std::endl;
    for ( uint i = 0; i < _MAX_VAL_; i++ ) {
        v.push_back(i);
    }
    
    std::cout << "  Shuffling " << v.size() << std::endl;
    std::random_shuffle ( v.begin(), v.end() );
    
    q.reserve(v.size());
    
    std::cout << "  Adding " << q.size() << std::endl;
    for ( uint i = 0; i < _MAX_VAL_; i++ ) {
        q.add(v[i]);
    }

    std::cout << "Start Size " << q.size() << std::endl;

    while (!q.empty()) {
        uint v = q.pop();
        #ifdef _DEBUG_
        std::cout << " V " << v << std::endl;
        #endif
    }
    
    std::cout << "End Size " << q.size() << std::endl;

    return 0;
}
