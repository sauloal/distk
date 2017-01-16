/*
* Copyright 2010 Tino Didriksen <tino@didriksen.cc>
* http://tinodidriksen.com/
* https://tinodidriksen.com/2010/04/cpp-set-performance/
* https://tinodidriksen.com/uploads/code/cpp/sorted_deque.hpp
*/

#pragma once
#ifndef __SORTED_DEQUE_HPP
#define __SORTED_DEQUE_HPP
#include <deque>
#include <algorithm>

template<typename T>
class sorted_deque {
private:
    typedef typename std::deque<T> Cont;
    typedef typename Cont::iterator iterator;
    Cont elements;

public:
    typedef typename Cont::const_iterator const_iterator;
    typedef typename Cont::size_type size_type;
    typedef T value_type;
    typedef T key_type;

    bool insert(T t) {
        iterator it = std::lower_bound(elements.begin(), elements.end(), t);
        if (it == elements.end() || *it != t) {
            elements.insert(it, t);
            return true;
        }
        return false;
    }

    bool erase(T t) {
        iterator it = std::lower_bound(elements.begin(), elements.end(), t);
        if (it != elements.end() && *it == t) {
            elements.erase(it);
            return true;
        }
        return false;
    }

    const_iterator find(T t) const {
        const_iterator it = std::lower_bound(elements.begin(), elements.end(), t);
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
