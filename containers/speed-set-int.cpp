/*
* Copyright 2010 Tino Didriksen <tino@didriksen.cc>
* http://tinodidriksen.com/
* https://tinodidriksen.com/2010/04/cpp-set-performance/
* https://tinodidriksen.com/uploads/code/cpp/speed-set-int.cpp
* http://www.fftw.org/cycle.h
* https://www.codeproject.com/KB/cpp/stree/stree_src.zip
*
* g++ speed-set-int.cpp -std=c++14 -I. -Ofast -o speed-set-int
* g++ speed-set-int.cpp -std=c++1y -I. -Ofast -o speed-set-int
*/

/*

$ g++ speed-set-int.cpp -std=c++14 -I. -Ofast -o speed-set-int
$ ./speed-set-int
size 5,000,000 repetitions 7

std::set
Insertion: with fastest 1499963630.00, average 1517198666.17, stddev  21460804.22
Lookup   : with fastest 1357251676.00, average 1396224206.33, stddev  64947959.61
Iterate  : with fastest     645556.00, average     662238.67, stddev     23550.11
Erase    : with fastest   35894098.00, average   36207673.50, stddev    443245.09

std::unordered_set
Insertion: with fastest  141139898.00, average  141892159.17, stddev   1579563.47
Lookup   : with fastest  122507977.00, average  123807317.83, stddev   1085570.73
Iterate  : with fastest     140176.00, average     142000.67, stddev      3068.70
Erase    : with fastest  118077164.00, average  118588385.50, stddev    504817.28

boost::unordered_set
Insertion: with fastest  150982849.00, average  160027352.50, stddev  17746230.12
Lookup   : with fastest  142045244.00, average  145719418.00, stddev   6664099.64
Iterate  : with fastest     132436.00, average     137459.67, stddev      2807.93
Erase    : with fastest   12458742.00, average   12558941.67, stddev    110865.46

sorted_vector
Insertion: with fastest 1044564924.00, average 1049718686.83, stddev   6059916.20
Lookup   : with fastest  975083810.00, average  979559240.17, stddev   4302784.85
Iterate  : with fastest         14.00, average        239.67, stddev       350.56
Erase    : with fastest   63636541.00, average   64232690.17, stddev   1311240.30

sorted_deque
Insertion: with fastest 1365159863.00, average 1380353665.33, stddev  16758222.26
Lookup   : with fastest 1242655099.00, average 1254174762.83, stddev   7850745.32
Iterate  : with fastest      28166.00, average      28208.33, stddev        32.80
Erase    : with fastest  148508712.00, average  152071069.83, stddev   3862542.95

sti::sset
Insertion: with fastest 1041412056.00, average 1049197225.83, stddev   6351049.83
Lookup   : with fastest  859844758.00, average  870034433.00, stddev  16025085.54
Iterate  : with fastest      12802.00, average      16056.33, stddev      1857.26
Erase    : with fastest  104068522.00, average  107367076.67, stddev   5921034.82


set_dflt
Insertion: with fastest 1502312200.00, average 1518153587.17, stddev  14746004.75
Lookup   : with fastest 1356133292.00, average 1403312112.67, stddev  45767241.54
Iterate  : with fastest     645012.00, average     673726.67, stddev     34926.77
Erase    : with fastest   35851424.00, average   36242553.17, stddev    354898.73

set_alta
Insertion: with fastest 1456606655.00, average 1475307849.67, stddev  12716940.55
Lookup   : with fastest 1345110993.00, average 1361770902.67, stddev  22705917.61
Iterate  : with fastest     625768.00, average     662855.67, stddev     32129.38
Erase    : with fastest   34945298.00, average   35376642.00, stddev    360088.26

prq_vec
Insertion: with fastest  334040800.00, average  342697391.00, stddev   9092771.71
Lookup   : with fastest          0.00, average          0.00, stddev         0.00
Iterate  : with fastest 4588189179.00, average 4662832254.50, stddev 110452373.81
Erase    : with fastest          0.00, average          0.00, stddev         0.00

MySortedVector
Insertion: with fastest 1669001550.00, average 1696618208.33, stddev 32972691.39
Lookup   : with fastest          0.00, average        108.00, stddev      121.57
Iterate  : with fastest          0.00, average         13.67, stddev        0.82
Erase    : with fastest          0.00, average         23.33, stddev       15.27


            std::set                      std::unordered_set           boost::unordered_set         sorted_vector                 sorted_deque                  sti::sset                     set_dflt                      set_alta                      prq_vec
Insertion:  1517198666.17 +- 21460804.22  141892159.17 +-  1579563.47  160027352.50 +- 17746230.12  1049718686.83 +-  6059916.20  1380353665.33 +- 16758222.26  1049197225.83 +-  6351049.83  1518153587.17 +- 14746004.75  1475307849.67 +- 12716940.55   342697391.00 +-   9092771.71
Lookup   :  1396224206.33 +- 64947959.61  123807317.83 +-  1085570.73  145719418.00 +-  6664099.64   979559240.17 +-  4302784.85  1254174762.83 +-  7850745.32   870034433.00 +- 16025085.54  1403312112.67 +- 45767241.54  1361770902.67 +- 22705917.61           0.00 +-         0.00
Iterate  :      662238.67 +-    23550.11     142000.67 +-     3068.70     137459.67 +-     2807.93         239.67 +-      350.56       28208.33 +-       32.80       16056.33 +-     1857.26      673726.67 +-    34926.77      662855.67 +-    32129.38  4662832254.50 +- 110452373.81
Erase    :    36207673.50 +-   443245.09  118588385.50 +-   504817.28   12558941.67 +-   110865.46    64232690.17 +-  1311240.30   152071069.83 +-  3862542.95   107367076.67 +-  5921034.82    36242553.17 +-   354898.73    35376642.00 +-   360088.26           0.00 +-         0.00










            std::set                           std::unordered_set               boost::unordered_set             sorted_vector                      sorted_deque                       sti::sset                          set_dflt                           set_alta                           prq_vec
Insertion:  1,517,198,666.17 +- 21,460,804.22  141,892,159.17 +-  1,579,563.47  160,027,352.50 +- 17,746,230.12  1,049,718,686.83 +-  6,059,916.20  1,380,353,665.33 +- 16,758,222.26  1,049,197,225.83 +-  6,351,049.83  1,518,153,587.17 +- 14,746,004.75  1,475,307,849.67 +- 12,716,940.55    342,697,391.00 +-   9,092,771.71
Lookup   :  1,396,224,206.33 +- 64,947,959.61  123,807,317.83 +-  1,085,570.73  145,719,418.00 +-  6,664,099.64    979,559,240.17 +-  4,302,784.85  1,254,174,762.83 +-  7,850,745.32    870,034,433.00 +- 16,025,085.54  1,403,312,112.67 +- 45,767,241.54  1,361,770,902.67 +- 22,705,917.61              0.00 +-           0.00
Iterate  :        662,238.67 +-     23,550.11      142,000.67 +-      3,068.70      137,459.67 +-      2,807.93            239.67 +-        350.56         28,208.33 +-         32.80         16,056.33 +-      1,857.26        673,726.67 +-     34,926.77        662,855.67 +-     32,129.38  4,662,832,254.50 +- 110,452,373.81
Erase    :     36,207,673.50 +-    443,245.09  118,588,385.50 +-    504,817.28   12,558,941.67 +-    110,865.46     64,232,690.17 +-  1,311,240.30    152,071,069.83 +-  3,862,542.95    107,367,076.67 +-  5,921,034.82     36,242,553.17 +-    354,898.73     35,376,642.00 +-    360,088.26              0.00 +-           0.00


           std::set      std::unordered_set  boost::unordered_set  sorted_vector  sorted_deque  sti::sset     set_dflt      set_alta      prq_vec       MySortedVector
Insertion: 1.5E9+-2.1E7  1.4E8+-1.6E6        1.6E8+-1.8E7          1.0E9+-6.1E6   1.4E9+-1.7E7  1.0E9+-6.4E6  1.5E9+-1.5E7  1.5E9+-1.3E7  3.4E8+-9.1E6  1.7e9+-3.3e7
Lookup   : 1.4E9+-6.5E7  1.2E8+-1.1E6        1.5E8+-6.7E6          9.8E8+-4.3E6   1.3E9+-7.9E6  8.7E8+-1.6E7  1.4E9+-4.6E7  1.4E9+-2.3E7  0.0E0+-0.0E0  0.0E0+-0.0E0
Iterate  : 6.6E5+-2.4E4  1.4E5+-3.1E3        1.4E5+-2.8E3          2.4E2+-3.5E2   2.8E4+-3.3E1  1.6E4+-1.9E3  6.7E5+-3.5E4  6.6E5+-3.2E4  4.7E9+-1.1E8  0.0E0+-0.0E0
Erase    : 3.6E7+-4.4E5  1.2E8+-5.0E5        1.3E7+-1.1E5          6.4E7+-1.3E6   1.5E8+-3.9E6  1.1E8+-5.9E6  3.6E7+-3.5E5  3.5E7+-3.6E5  0.0E0+-0.0E0  0.0E0+-0.0E0


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

#include <queue>
#include <list>

#include "sti/sset.h"
#include "sorted_vector.hpp"
#include "sorted_deque.hpp"
#include "cycle.h"

#include "set_alloc.hpp"

const size_t N = 5000000;
const size_t R = 5;

typedef uint64_t measurement_int;

std::vector<measurement_int> numbers;


template<class T> using set_dflt = std::set< T, std::less<T> >;
template<class T> using set_alta = std::set< T, std::less<T>, bestAlloc<T> >;

template<typename T>
class MyPQueueLst : public std::priority_queue<T, std::list<T>, std::less<T> > {
    public:
        void reserve(size_t reserve_size) {
            this->c.reserve(reserve_size);
        }
        void insert(T v) {
            this.push(v);
        }
};

template<typename T>
class MyPQueueVec : public std::priority_queue<T, std::vector<T>, std::less<T> > {
    public:
        void reserve(size_t reserve_size) {
            this->c.reserve(reserve_size);
        }
        void insert(T v) {
            this.push(v);
        }
        std::vector<T>& getContainer() {
            return this->c;
        }
};

template<typename T>
class MyPQueueSVec: public std::priority_queue<T, sorted_vector<T>, std::less<T> > {
    public:
        void reserve(size_t reserve_size) {
            this->c.reserve(reserve_size);
        }
        void insert(T v) {
            this.push(v);
        }
};

template<class T> using prq_list = MyPQueueLst<T>;
template<class T> using prq_vec  = MyPQueueVec<T>;
//template<class T> using prq_svec = MyPQueueSVec<T>;



template<typename T>
class MySortedVector: public std::vector<T> {
    public:
        void insert(T v) {
            this->push_back(v);
        }
        void sort() {
            set_alta<T> s( this->begin(), this->end() );
            this->assign( s.begin(), s.end() );
        }
        auto find(T v) {
            return this->begin();
        }
        void erase(T v) {
            
        }
};



template<typename T>
class MySortedVectorAlt: public std::vector<T, bestAlloc<T> > {
    public:
        void insert(T v) {
            this->push_back(v);
        }
        void sort() {
            set_alta<T> s( this->begin(), this->end() );
            this->assign( s.begin(), s.end() );
        }
        auto find(T v) {
            return this->begin();
        }
        void erase(T v) {
            
        }
};



void PrintStats(std::vector<double> timings) {
    double fastest = std::numeric_limits<double>::max();
    double sum     = 0.0;
    double avg     = 0.0;
    double var     = 0.0;
    double sdv     = 0.0;

    if (timings.size() > 0) {
        std::cout << std::fixed << std::setprecision(2);
        #ifdef _DEBUG_
        std::cout << "[";
        #endif
        for (size_t i = 1 ; i<timings.size()-1 ; ++i) {
            fastest = std::min(fastest, timings[i]);
            #ifdef _DEBUG_
            std::cout << timings[i] << ",";
            #endif
        }
        #ifdef _DEBUG_
        std::cout << timings.back();
        std::cout << "]";
        #endif
        
        sum = 0.0;
        for (size_t i = 1 ; i<timings.size() ; ++i) {
            sum += timings[i];
        }
        avg = sum / double(timings.size()-1);
    
        sum = 0.0;
        for (size_t i = 1 ; i<timings.size() ; ++i) {
            timings[i] = pow(timings[i]-avg, 2);
            sum += timings[i];
        }
        var = sum/(timings.size()-2);
        sdv = sqrt(var);
    } else {
        fastest = 0;
    }
    std::cout << " with fastest " << fastest << ", average " << avg << ", stddev " << sdv;
}



template<typename Cont>
void runTest() {
    std::vector< std::vector<double> > timings(4);

    for (size_t r=0 ; r<R ; ++r) {
        Cont Set;

        Set.reserve(N/4);

        ticks start, end;
        double timed = 0.0;

        //INSERT
        size_t res = 0;
        start = getticks();
        for (size_t i=0 ; i<N ; ++i) {
            Set.insert(numbers[i]);
        }
        end = getticks();
        timed = elapsed(end, start);
        timings[0].push_back(timed);

        if ( r == 0 ) {
            std::cout << "Size: " << Set.size() << std::endl;
        }
        
        //LOOKUP
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
        #ifdef _DEBUG_
        std::cerr << res << std::endl;
        #endif

        //ITERATE
        res = 0;
        start = getticks();
        for (typename Cont::const_iterator it = Set.begin(); it != Set.end() ; ++it) {
            res += *it;
        }
        end = getticks();
        timed = elapsed(end, start);
        timings[2].push_back(timed);
        #ifdef _DEBUG_
        std::cerr << res << std::endl;
        #endif

        //ERASE
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

    std::cout << "Lookup   : ";
    PrintStats(timings[1]);
    std::cout << std::endl;

    std::cout << "Iterate  : ";
    PrintStats(timings[2]);
    std::cout << std::endl;

    std::cout << "Erase    : ";
    PrintStats(timings[3]);
    std::cout << std::endl;

    std::cout << std::endl;
}



template<typename Cont>
void runTestVec() {
    std::vector< std::vector<double> > timings(4);

    for (size_t r=0 ; r<R ; ++r) {
        //std::cout << "Creating" << std::endl;
        Cont Set;

        Set.reserve(N/4);

        ticks start, end;
        double timed = 0.0;

        //std::cout << "Inserting" << std::endl;
        //INSERT
        size_t res = 0;
        start = getticks();
        for (size_t i=0 ; i<N ; ++i) {
            Set.insert(numbers[i]);
        }
        Set.sort();
        end = getticks();
        timed = elapsed(end, start);
        timings[0].push_back(timed);


        
        if ( r == 0 ) {
            std::cout << "Size: " << Set.size() << std::endl;
        }

        
        //LOOKUP
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
        #ifdef _DEBUG_
        std::cerr << res << std::endl;
        #endif

        //ITERATE
        res = 0;
        start = getticks();
        for (typename Cont::const_iterator it = Set.begin(); it != Set.end() ; ++it) {
            res += *it;
        }
        end = getticks();
        timed = elapsed(end, start);
        timings[2].push_back(timed);
        #ifdef _DEBUG_
        std::cerr << res << std::endl;
        #endif

        //ERASE
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

    std::cout << "Lookup   : ";
    PrintStats(timings[1]);
    std::cout << std::endl;

    std::cout << "Iterate  : ";
    PrintStats(timings[2]);
    std::cout << std::endl;

    std::cout << "Erase    : ";
    PrintStats(timings[3]);
    std::cout << std::endl;

    std::cout << std::endl;
}



template<typename Cont>
void runTestQueue() {
    std::vector< std::vector<double> > timings(4);

    for (size_t r=0 ; r<R ; ++r) {
        Cont Set;
        ticks start, end;
        double timed = 0.0;

        //INSERT
        size_t res = 0;
        start = getticks();
        for (size_t i=0 ; i<N ; ++i) {
            Set.push(numbers[i]);
        }
        end = getticks();
        timed = elapsed(end, start);
        timings[0].push_back(timed);

        if ( r == 0 ) {
            std::cout << "Size: " << Set.size() << std::endl;
        }
        
        //LOOKUP
        /*
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
        #ifdef _DEBUG_
        std::cerr << res << std::endl;
        #endif
        */

        /*
        auto c = Set.getContainer();
        for ( auto d = c.begin(); d < c.end(); d++ ) {
            std::cout << *d << "\n";            
        }
        */
        
        //ITERATE
        res = 0;
        start = getticks();
        while (!Set.empty()) {
            #ifdef _DEBUG_
            auto v  = Set.top();
            res    += v;
            std::cout << v << "\n";
            #else
            //res    += Set.top();
            #endif
            Set.pop();
        }
        end = getticks();
        timed = elapsed(end, start);
        timings[2].push_back(timed);
        #ifdef _DEBUG_
        std::cerr << res << std::endl;
        #endif

        //ERASE
        /*
        start = getticks();
        for (size_t i=0 ; i<N ; ++i) {
            Set.erase(numbers[i]);
        }
        end = getticks();
        timed = elapsed(end, start);
        timings[3].push_back(timed);
        */
    }

    std::cout << "Insertion: ";
    PrintStats(timings[0]);
    std::cout << std::endl;

    std::cout << "Lookup   : ";
    PrintStats(timings[1]);
    std::cout << std::endl;

    std::cout << "Iterate  : ";
    PrintStats(timings[2]);
    std::cout << std::endl;

    std::cout << "Erase    : ";
    PrintStats(timings[3]);
    std::cout << std::endl;

    std::cout << std::endl;
}



int main() {
    std::cout << "size " << N << " repetitions " << R << std::endl;

    srand(902200987);
    
    std::cout << "resizing" << std::endl;
    numbers.resize(N);
    
    std::cout << "adding " << numbers.size() << " capacity " << numbers.capacity() << std::endl;
    for (size_t i=0 ; i<N ; ++i) {
        numbers[i] = rand() & 0x00003FFF;
    }
    std::cout << "testing" << std::endl;

    /*
    std::cout << "std::set" << std::endl;
    runTest< std::set<measurement_int> >();

    std::cout << "std::unordered_set" << std::endl;
    runTest< std::unordered_set<measurement_int> >();

    std::cout << "boost::unordered_set" << std::endl;
    runTest< boost::unordered_set<measurement_int> >();

    */
    
    std::cout << "sorted_vector" << std::endl;
    runTest< sorted_vector<measurement_int> >();
    
    /*
    std::cout << "sorted_deque" << std::endl;
    runTest< sorted_deque<measurement_int> >();

    std::cout << "sti::sset" << std::endl;
    runTest< sti::sset<measurement_int> >();


    */

    /*
    std::cout << "set_dflt" << std::endl;
    runTest< set_dflt<measurement_int> >();

    std::cout << "set_alta" << std::endl;
    runTest< set_alta<measurement_int> >();
    */

    //std::cout << "prq_list" << std::endl;
    //runTestQueue< prq_list<measurement_int> >();

    /*
    std::cout << "prq_vec" << std::endl;
    runTestQueue< prq_vec<measurement_int> >();
    */
    
    //std::cout << "prq_svec" << std::endl;
    //runTestQueue< prq_svec<measurement_int> >();
    
    std::cout << "MySortedVector" << std::endl;
    runTestVec< MySortedVector<measurement_int> >();
    
    //std::cout << "MySortedVectorAlt" << std::endl;
    //runTestVec< MySortedVectorAlt<measurement_int> >();
}
