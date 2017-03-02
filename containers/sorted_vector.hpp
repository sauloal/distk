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
#include <stdint.h> // C99 or C++0x or C++ TR1 will have this header. ToDo: Change to <cstdint> when C++0x broader support gets under way.

//#include "set_alloc.hpp"


template<typename T>
class sorted_vector {
private:
    typedef typename std::vector<T>       Cont;
    typedef typename Cont::iterator       iterator;
    Cont                                  elements;

public:
    typedef typename Cont::const_iterator const_iterator;
    typedef typename Cont::size_type      size_type;
    typedef T                             value_type;
    typedef T                             key_type;

    inline
    bool insert(const T & t) {
        //std::cout << "insert " << t;
        
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
    const_iterator begin() const {
        return elements.begin();
    }

    inline
    const_iterator end() const {
        return elements.end();
    }

    inline
    T & front() const {
        return elements.front();
    }

    inline
    T & back() const {
        return elements.back();
    }

    inline
    iterator lower_bound(const T & t) {
        return std::lower_bound(elements.begin(), elements.end(), t);
    }

    inline
    const_iterator lower_bound(const T & t) const {
        return std::lower_bound(elements.begin(), elements.end(), t);
    }

    inline
    const_iterator upper_bound(const T & t) const {
        return std::upper_bound(elements.begin(), elements.end(), t);
    }

    inline
    size_type size() const {
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
        std::cout << " reserving memory for " << t << " kmers" << std::endl;
        elements.reserve(t);
        std::cout << " reserved memory for  " << t << " kmers" << std::endl;
    }
    
    inline
    void resize(const size_t & t) {
        elements.resize(t);
    }
    
    inline
    auto get_allocator() {
        return elements.get_allocator();
    }
    
    inline
    auto& get_container() {
        return elements;
    }
    
    inline
    T& operator[](const size_t p){
        return elements[p];
    }
};

typedef sorted_vector< unsigned long > setuLongLess;

#endif
