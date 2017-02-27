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

template<typename T>
class sorted_vector {
private:
    typedef typename std::vector<T> Cont;
    typedef typename Cont::iterator iterator;
    Cont elements;

public:
    typedef typename Cont::const_iterator const_iterator;
    typedef typename Cont::size_type size_type;
    typedef T value_type;
    typedef T key_type;

    bool insert(T t) {
        if (elements.empty()) {
            elements.push_back(t);
            return true;
        }
        else if (elements.back() < t) {
            elements.push_back(t);
            return true;
        }
        else if (t < elements.front()) {
            elements.insert(elements.begin(), t);
            return true;
        }
        iterator it = std::lower_bound(elements.begin()+1, elements.end(), t);
        if (it == elements.end() || *it != t) {
            elements.insert(it, t);
            return true;
        }
        return false;
    }

    bool push_back(T t) {
        return insert(t);
    }

    bool erase(const_iterator t) {
        elements.erase(t);
    }

    bool erase(T t) {
        if (elements.empty()) {
            return false;
        }
        else if (elements.back() < t) {
            return false;
        }
        else if (t < elements.front()) {
            return false;
        }
        iterator it = lower_bound(t);
        if (it != elements.end() && *it == t) {
            elements.erase(it);
            return true;
        }
        return false;
    }

    const_iterator find(T t) const {
        if (elements.empty()) {
            return elements.end();
        }
        else if (elements.back() < t) {
            return elements.end();
        }
        else if (t < elements.front()) {
            return elements.end();
        }
        const_iterator it = lower_bound(t);
        if (it != elements.end() && *it != t) {
            return elements.end();
        }
        return it;
    }
    
    const_iterator begin() const {
        return elements.begin();
    }

    const_iterator end() const {
        return elements.end();
    }

    T front() const {
        return elements.front();
    }

    T back() const {
        return elements.back();
    }

    iterator lower_bound(T t) {
        return std::lower_bound(elements.begin(), elements.end(), t);
    }

    const_iterator lower_bound(T t) const {
        return std::lower_bound(elements.begin(), elements.end(), t);
    }

    const_iterator upper_bound(T t) const {
        return std::upper_bound(elements.begin(), elements.end(), t);
    }

    size_type size() const {
        return elements.size();
    }

    bool empty() const {
        return elements.empty();
    }

    void clear() {
        elements.clear();
    }
};

#endif
