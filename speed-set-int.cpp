/*
* Copyright 2010 Tino Didriksen <tino@didriksen.cc>
* http://tinodidriksen.com/
* https://tinodidriksen.com/2010/04/cpp-set-performance/
* https://tinodidriksen.com/uploads/code/cpp/speed-set-int.cpp
* http://www.fftw.org/cycle.h
* https://www.codeproject.com/KB/cpp/stree/stree_src.zip
*/

#ifdef _MSC_VER
    #define _SECURE_SCL 0
    #define _CRT_SECURE_NO_DEPRECATE 1
    #define WIN32_LEAN_AND_MEAN
    #define VC_EXTRALEAN
    #define NOMINMAX
#endif

#include <cstdlib>
#include <cstdint>
#include <cmath>
#include <iostream>
#include <string>
#include <algorithm>
#include <limits>
#include <vector>
#include <iomanip>
#include <sstream>
#include <set>
#include <boost/unordered_set.hpp>
#include <unordered_set>
#include "sti/sset.h"
#include "sorted_vector.hpp"
#include "sorted_deque.hpp"
#include "cycle.h"

const size_t N = 1000000;
const size_t R = 7;
std::vector<uint32_t> numbers;

void PrintStats(std::vector<double> timings) {
    double fastest = std::numeric_limits<double>::max();

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "[";
    for (size_t i = 1 ; i<timings.size()-1 ; ++i) {
        fastest = std::min(fastest, timings[i]);
        std::cout << timings[i] << ",";
    }
    std::cout << timings.back();
    std::cout << "]";

    double sum = 0.0;
    for (size_t i = 1 ; i<timings.size() ; ++i) {
        sum += timings[i];
    }
    double avg = sum / double(timings.size()-1);

    sum = 0.0;
    for (size_t i = 1 ; i<timings.size() ; ++i) {
        timings[i] = pow(timings[i]-avg, 2);
        sum += timings[i];
    }
    double var = sum/(timings.size()-2);
    double sdv = sqrt(var);

    std::cout << " with fastest " << fastest << ", average " << avg << ", stddev " << sdv;
}

template<typename Cont>
void runTest() {
    std::vector< std::vector<double> > timings(4);

    for (size_t r=0 ; r<R ; ++r) {
        Cont Set;
        ticks start, end;
        double timed = 0.0;
        size_t res = 0;

        start = getticks();
        for (size_t i=0 ; i<N ; ++i) {
            Set.insert(numbers[i]);
        }
        end = getticks();
        timed = elapsed(end, start);
        timings[0].push_back(timed);

        res = 0;
        start = getticks();
        for (size_t i=0 ; i<N ; ++i) {
            typename Cont::const_iterator it = Set.find(numbers[i]);
            if (it != Set.end()) {
                res += *it;
            }
        }
        end = getticks();
        timed = elapsed(end, start);
        timings[1].push_back(timed);
        std::cerr << res << std::endl;

        res = 0;
        start = getticks();
        for (typename Cont::const_iterator it = Set.begin(); it != Set.end() ; ++it) {
            res += *it;
        }
        end = getticks();
        timed = elapsed(end, start);
        timings[2].push_back(timed);
        std::cerr << res << std::endl;

        start = getticks();
        for (size_t i=0 ; i<N ; ++i) {
            Set.erase(numbers[i]);
        }
        end = getticks();
        timed = elapsed(end, start);
        timings[3].push_back(timed);
    }

    std::cout << "Insertion: ";
    PrintStats(timings[0]);
    std::cout << std::endl;

    std::cout << "Lookup: ";
    PrintStats(timings[1]);
    std::cout << std::endl;

    std::cout << "Iterate: ";
    PrintStats(timings[2]);
    std::cout << std::endl;

    std::cout << "Erase: ";
    PrintStats(timings[3]);
    std::cout << std::endl;

    std::cout << std::endl;
}

int main() {
    srand(902200987);
    for (size_t i=0 ; i<N ; ++i) {
        numbers.push_back(rand() & 0x00003FFF);
    }

    std::cout << "std::set" << std::endl;
    runTest< std::set<uint32_t> >();

    std::cout << "std::unordered_set" << std::endl;
    runTest< std::unordered_set<uint32_t> >();

    std::cout << "boost::unordered_set" << std::endl;
    runTest< boost::unordered_set<uint32_t> >();

    std::cout << "sorted_vector" << std::endl;
    runTest< sorted_vector<uint32_t> >();

    std::cout << "sorted_deque" << std::endl;
    runTest< sorted_deque<uint32_t> >();

    std::cout << "sti::sset" << std::endl;
    runTest< sti::sset<uint32_t> >();
}
