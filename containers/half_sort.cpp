#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdint.h> // C99 or C++0x or C++ TR1 will have this header. ToDo: Change to <cstdint> when C++0x broader support gets under way.

//g++ half_sort.cpp -std=c++11 -o half_sort

#define RAND 902200987
#define N 1000
#define MASK 0x000000FF


typedef uint64_t measurement_int;

std::vector<measurement_int> numbers;

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
                std::cout << "sort_full :: last_sort: " << last_sort << " elements size: " << elements.size() << std::endl;
                std::sort(elements.begin(), elements.end());
                it        = std::unique(elements.begin(), elements.end());
                elements.resize( std::distance(elements.begin(),it) );
                last_sort = elements.size();
                std::cout << " new size: " << last_sort << std::endl;
            }
        }
        
        inline
        void sort_half() {
            if ( last_sort != elements.size() ) {
                std::cout << "sort_half :: last_sort: " << last_sort << " elements size: " << elements.size() << std::endl;
                std::sort(                           elements.begin()+last_sort, elements.end());
                std::inplace_merge(elements.begin(), elements.begin()+last_sort, elements.end());
                it        = std::unique(  elements.begin(), elements.end());
                elements.resize( std::distance(elements.begin(),it) );
                last_sort = elements.size();
                std::cout << " new size: " << last_sort << std::endl;
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
                
                print();
            }
            return true;
        }
        
        void print() {
            size_t c = 0;
            std::cout << "elements size " << elements.size() << std::endl;
            for (auto i = elements.begin(); i < elements.end(); i++) {
                ++c;
                printf( "elements %03lu %03lu", c, *i );
                std::cout << std::endl;
            }
        }
        
        void close() {
            sort_half();
            print();
        }
};


int main() {
    srand(RAND);
    
    std::cout << "resizing" << std::endl;
    
    half_sort<measurement_int> hs;
    
    std::cout << "adding   " << N << std::endl;
    for (size_t i=0 ; i<N ; ++i) {

        measurement_int v = rand() & MASK;
        printf( "adding   %03lu %03lu", (i+1), v );
        std::cout << std::endl;
        hs.insert(v);
    }
    std::cout << "testing" << std::endl;

    hs.close();
        
}