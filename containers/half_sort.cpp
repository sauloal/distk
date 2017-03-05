#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <stdint.h> // C99 or C++0x or C++ TR1 will have this header. ToDo: Change to <cstdint> when C++0x broader support gets under way.

//g++ half_sort.cpp -std=c++11 -Ofast -o half_sort

#define RAND  902200987
#define N       1000000
#define MASK 0x000FFFFF

typedef std::string string;
typedef uint64_t    measurement_int;


template<typename T>
class half_sort {
private:
    typedef typename std::vector<T>       Cont;
    typedef typename Cont::iterator       iterator;

public:
    typedef typename Cont::const_iterator const_iterator;
    typedef typename Cont::size_type      size_type;
    typedef T                             value_type;
    typedef T                             key_type;

private:
    Cont                                  elements;
    //Cont                                  buffer;
    size_t   last_sort;
    size_t   buffer_size;
    size_t   buffer_pos;
    iterator it;

    inline
    void sort_full () {
        if ( last_sort != elements.size() ) {
            printf("sort_full :: last_sort: %12lu elements size: %12lu\n", last_sort, elements.size());
            
            std::sort(elements.begin(), elements.end());
            
            it        = std::unique(elements.begin(), elements.end());
            elements.resize( std::distance(elements.begin(),it) );
            
            last_sort = elements.size();
            
            printf(" new size: %12lu", last_sort);
            std::cout << std::endl;
        }
    }
    
    inline
    void sort_half() {
        if ( last_sort != elements.size() ) {
            printf("sort_half :: last_sort: %12lu elements size: %12lu\n", last_sort, elements.size());
            
            //print("before half sort");
            
            std::sort(                           elements.begin()+last_sort, elements.end());
            
            //print("before inplace merge");
            
            std::inplace_merge(elements.begin(), elements.begin()+last_sort, elements.end());
            it        = std::unique(  elements.begin(), elements.end());
            //print("mid unique");
            
            elements.resize( std::distance(elements.begin(),it) );
            //print("after unique");
            
            last_sort = elements.size();
            
            printf(" new size: %12lu", last_sort);
            std::cout << std::endl;
        }
    }
    
public:
    half_sort(): last_sort(0), buffer_size(N/3), buffer_pos(0) {}

    inline
    bool insert(const T & t) {
        elements.push_back(t);
        buffer_pos++;

        if ( buffer_pos == buffer_size ) {
            buffer_pos = 0;
            
            if ( last_sort == 0 ) {
                sort_full();
            } else {
                sort_half();
            }
            
            //print();
        }
        return true;
    }
    
    void print(const string s="") {
        size_t c = 0;
        printf( "%s elements size %12lu\n", s, elements.size() );
        for (auto i = elements.begin(); i < elements.end(); i++) {
            ++c;
            printf( "%s elements %12lu %12lu\n", s, c, *i );
        }
        std::cout << std::endl;
    }
    
    void close() {
        sort_half();
        //print();
    }
    
    T size() const {
        return elements.size();
    }
    
    inline
    T& operator[](const size_t p){
        return elements[p];
    }
};


typedef std::vector<measurement_int> Tvec;
typedef half_sort<measurement_int>   Thso;
typedef std::set<measurement_int>    Tset;

int main() {
    srand(RAND);
    
    std::cout << "resizing" << std::endl;
    
    Thso hs;
    Tset ns;
   
    std::cout << " adding   " << N << std::endl;
    for (size_t i=0 ; i<N ; ++i) {

        measurement_int v = rand() & MASK;
        //printf( " adding   %12lu %12lu", (i+1), v );
        //std::cout << std::endl;
        hs.insert(v);
        ns.insert(v);
    }
    
    std::cout << "testing" << std::endl;

    hs.close();
    
    Tvec nv(ns.begin(), ns.end());
    //std::vector<measurement_int> svec(nset.size());
    //std::copy(nset.begin(), nset.end(), svec.begin());
    
    printf("       vector %12lu set %12lu setvec %12lu\n", hs.size(), ns.size(), nv.size());
    
    bool r = true;
    for ( size_t l = 0; l < hs.size(); ++l ) {
        auto h = hs[l];
        auto s = nv[l];
        auto b = hs[l] == nv[l];
        r &= b;
        //printf("%12lu vector %12lu setvec %12lu :: %s\n", l, h, s, (b ? "true" : "false"));
    }

    printf("       vector %12lu set %12lu setvec %12lu\n", hs.size(), ns.size(), nv.size());
    std::cout << " res " << r << std::endl;
}
