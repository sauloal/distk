/*
* Copyright 2010 Tino Didriksen <tino@didriksen.cc>
* http://tinodidriksen.com/
* No rights reserved. Use as you see fit.
* https://tinodidriksen.com/2010/04/cpp-set-performance/
* https://tinodidriksen.com/uploads/code/cpp/sorted_vector.hpp
*/

#pragma once
#ifndef _SORTED_VECTOR_HPP
#define _SORTED_VECTOR_HPP
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <stdint.h> // C99 or C++0x or C++ TR1 will have this header. ToDo: Change to <cstdint> when C++0x broader support gets under way.

#ifndef COMMIT_EVERY
#define COMMIT_EVERY 10000000
#endif


//#include "set_alloc.hpp"


template<typename T>
class sorted_vector;


template<typename T>
class sorted_vector {
private:
    typedef typename std::vector<T>       Cont;
    typedef typename Cont::iterator       iterator;
    Cont                                  elements;
    //Cont                                  buffer;

public:
    typedef typename Cont::const_iterator const_iterator;
    typedef typename Cont::size_type      size_type;
    typedef T                             value_type;
    typedef T                             key_type;

private:
    size_t   last_sort;
    size_t   buffer_size;
    size_t   buffer_pos;
    iterator it;
/*
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
    
    void sort_half () {
        //v.reserve(v.size() + distance(v_prime.begin(),v_prime.end()));
        //v.insert(v.end(),v_prime.begin(),v_prime.end());
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
*/

    inline
    void sort_full () {
        if ( last_sort != elements.size() ) {
            printf("sort_full :: last_sort: %12lu elements size: %12lu", last_sort, elements.size());
            
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
            printf("sort_half :: last_sort: %12lu elements size: %12lu", last_sort, elements.size());
            
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

    sorted_vector(): last_sort(0), buffer_size(COMMIT_EVERY), buffer_pos(0) {
        //buffer.resize( buffer_size );
    }
    
    inline
    bool insert(const T & t) {
        //std::cout << "insert " << t;
        //buffer[buffer_pos++] = t;
        //std::sort (elements.begin(), elements.end());
        
        elements.push_back(t);
        buffer_pos++;

        //if ((elements.size()>0) && ( elements.size() % buffer_size == 0 )) {
        if ( buffer_pos == buffer_size ) {
            buffer_pos = 0;
            
            /*
            std::merge()

            std::sort(buffer.begin(), buffer.end());
            
            std::merge(v1.begin(), v1.end(), v2.begin(), v2.end(), std::back_inserter(dst))
            */
            
            /*
            std::sort(  elements.begin(), elements.begin());
            it = std::unique(elements.begin(), elements.end());
            elements.resize( std::distance(elements.begin(),it) );
            */
            
            if ( last_sort == 0 ) {
                sort_full();
            } else {
                sort_half();
            }
            
            /*
            std::partial_sort(elements.begin(), elements.begin()+(elements.size()/2), elements.end());
            it = std::unique(elements.begin(), elements.end());
            elements.resize( std::distance(elements.begin(),it) );
            */
            
            /*
            std::sort(  elements.begin(), elements.begin());
            it = std::unique(elements.begin(), elements.end());
            last_sort=elements.size();
            */
            
            /*
            std::set<T> input(elements.begin(), elements.end());
            elements.clear();
            std::copy(input.begin(), input.end(), std::back_inserter(elements));
            */
        }
        return true;
    }
    /*
    inline
    bool insert(const T & t) {
        if (elements.empty()) {
            elements.push_back(t);
            //std::cout << " empty" << std::endl;
            return true;

        } else {
            T b = elements.back();

            if (b <= t) {
                if (b < t) {
                    elements.push_back(t);
                    //std::cout << "insert " << t;
                    //std::cout << " push back" << std::endl;
                    return true;
                } else {
                    //std::cout << " is back" << std::endl;
                    return false;
                }
            } else {
                T f = elements.front();

                if (f >= t) {
                    if (f > t) {
                        elements.insert(elements.begin(), t);
                        //std::cout << " insert front" << std::endl;
                        return true;
                    } else {
                        //std::cout << " is front" << std::endl;
                        return false;
                    }
                } else {
                    iterator it = std::lower_bound(elements.begin()+1, elements.end(), t);
                    
                    if (it == elements.end() || *it != t) {
                        elements.insert(it, t);
                        //std::cout << " insert middle" << std::endl;
                        return true;
                    } else {
                        //std::cout << " repeated" << std::endl;
                        return false;
                    } //if (it == elements.end() || *it != t) {
                }//if (f >= t) {
            } //if (b <= t) {
        } //if (elements.empty()) {
    }
    */

    inline
    bool push_back(const T & t) {
        //std::cout << " push_back " << t << std::endl;
        return insert(t);
    }

    inline
    bool erase(const_iterator & t) {
        elements.erase(t);
    }

    inline
    bool erase(const T & t) {
        if (elements.empty()) {
            return false;
        }
        else if (elements.back() < t) {
            return false;
        }
        else if (t < elements.front()) {
            return false;
        } else {
            iterator it = lower_bound(t);
            
            if (it != elements.end() && *it == t) {
                elements.erase(it);
                return true;
            }
            
            return false;
        }
    }

    inline
    const_iterator find(const T & t) const {
        if (elements.empty()) {
            return elements.end();
        }
        else if (elements.back() < t) {
            return elements.end();
        }
        else if (t < elements.front()) {
            return elements.end();
        } else {
            const_iterator it = lower_bound(t);
            
            if (it != elements.end() && *it != t) {
                return elements.end();
            }
            
            return it;
        }
    }
    
    inline
    const_iterator begin() {
        sort_half();
        return elements.begin();
    }

    inline
    const_iterator end() {
        sort_half();
        return elements.end();
    }

    inline
    T & front() {
        sort_half();
        return elements.front();
    }

    inline
    T & back() {
        sort_half();
        return elements.back();
    }

    inline
    iterator lower_bound(const T & t) {
        sort_half();
        return std::lower_bound(elements.begin(), elements.end(), t);
    }

    inline
    const_iterator lower_bound(const T & t) const {
        sort_half();
        return std::lower_bound(elements.begin(), elements.end(), t);
    }

    inline
    const_iterator upper_bound(const T & t) {
        sort_half();
        return std::upper_bound(elements.begin(), elements.end(), t);
    }

    inline
    size_type size() {
        sort_half();
        return elements.size();
    }

    inline
    bool empty() const {
        return elements.empty();
    }

    inline
    void clear() {
        elements.clear();
    }
    
    inline
    void reserve(const size_t & t) {
        printf( " reserving memory for %12lu kmers", t );
        elements.reserve(t);
        std::cout << " reserved" << std::endl;
    }
    
    inline
    void resize(const size_t & t) {
        elements.resize(t);
    }
    
    inline
    auto get_allocator() {
        sort_half();
        return elements.get_allocator();
    }
    
    inline
    auto& get_container() {
        sort_half();
        return elements;
    }
    
    inline
    T& operator[](const size_t p){
        return elements[p];
    }

    inline
    bool operator==(sorted_vector<T> &c2) {
        if ( size() != c2.size() ) {
            return false;
        } else {
            for ( size_t n=0; n < size(); ++n ) {
                if( elements[n] != c2[n] ) {
                    return false;
                }
            }
            return true;
        }
    }
};

typedef sorted_vector< unsigned long > setuLongLess;

#endif
