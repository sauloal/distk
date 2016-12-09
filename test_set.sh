#/bin/bash
set -xeu

echo "heap vector"
CPP_OPTS=
g++ ${CPP_OPTS} -std=c++11 -o set set.cpp && time ./set

#echo "heap list"
#CPP_OPTS=-D_LIST_
#g++ ${CPP_OPTS} -std=c++11 -o set set.cpp && time ./set


echo "set"
CPP_OPTS=-D_SET_
g++ ${CPP_OPTS} -std=c++11 -o set set.cpp && time ./set


echo "heap vector"
CPP_OPTS="-D_MAX_VAL_=20 -D_DEBUG_=1"
g++ ${CPP_OPTS} -std=c++11 -o set set.cpp && time ./set

#echo "heap list"
#CPP_OPTS=-D_LIST_
#g++ ${CPP_OPTS} -std=c++11 -o set set.cpp && time ./set


echo "set"
CPP_OPTS="-D_SET_ -D_MAX_VAL_=20 -D_DEBUG_=1"
g++ ${CPP_OPTS} -std=c++11 -o set set.cpp && time ./set

