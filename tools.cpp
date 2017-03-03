//https://stackoverflow.com/questions/874134/find-if-string-ends-with-another-string-in-c

#include "tools.hpp"

#include <iterator>
#include <sys/stat.h>

std::ostream& operator<< (std::ostream& out, const std::vector<string>& v) {
  if ( v.size() != 0 ) {
    out << '[';
    std::copy (std::begin(v), std::end(v), std::ostream_iterator<string>(out, ", "));
    out << "\b\b]";
  }
  return out;
}


#ifdef _DEBUG_
#define _PRINT_LINE_LENGTHS_

//http://stackoverflow.com/questions/10750057/how-to-print-out-the-contents-of-a-vector
template <typename T>
std::ostream& operator<< (std::ostream& out, const std::vector<T>& v) {
  if ( !v.empty() ) {
    out << '[';
    std::copy (v.begin(), v.end(), std::ostream_iterator<T>(out, ", "));
    out << "\b\b]";
  }
  return out;
}


//template <typename T>
std::ostream& operator<< (std::ostream& out, const std::valarray<char>& v) {
  if ( v.size() != 0 ) {
    out << '[';
    std::copy (std::begin(v), std::end(v), std::ostream_iterator<char>(out, ", "));
    out << "\b\b]";
  }
  return out;
}
std::ostream& operator<< (std::ostream& out, const std::valarray<int>& v) {
  if ( v.size() != 0 ) {
    out << '[';
    std::copy (std::begin(v), std::end(v), std::ostream_iterator<int>(out, ", "));
    out << "\b\b]";
  }
  return out;
}
std::ostream& operator<< (std::ostream& out, const std::valarray<uint>& v) {
  if ( v.size() != 0 ) {
    out << '[';
    std::copy (std::begin(v), std::end(v), std::ostream_iterator<uint>(out, ", "));
    out << "\b\b]";
  }
  return out;
}
std::ostream& operator<< (std::ostream& out, const std::valarray<ulong>& v) {
  if ( v.size() != 0 ) {
    out << '[';
    std::copy (std::begin(v), std::end(v), std::ostream_iterator<ulong>(out, ", "));
    out << "\b\b]";
  }
  return out;
}
std::ostream& operator<< (std::ostream& out, const std::valarray<bool>& v) {
  if ( v.size() != 0 ) {
    out << '[';
    //std::copy (std::begin(v), std::end(v), std::ostream_iterator<bool>(out, ", "));
    for (auto it=std::begin(v); it!=std::end(v); ++it) {
        out << (( it == std::begin(v) )? "" : ", ") << *it;
    }
    out << "]";
  }
  return out;
}
template <typename T>
std::vector<T> reversed(std::vector<T> v) {
    std::vector<T> w(v.begin(), v.end());
    std::reverse(w.begin(),w.end());
    return w;
}
#endif


//https://stackoverflow.com/questions/12774207/fastest-way-to-check-if-a-file-exist-using-standard-c-c11-c
inline bool file_exists (const string& name) {
  struct stat buffer;   
  return (stat (name.c_str(), &buffer) == 0); 
}

inline void remove_if_exists( const string& name ) {
    if ( file_exists( name ) ) {
        if ( remove( name.c_str() ) != 0 ) {
            perror((string("error deleting file: ") + name).c_str());
#ifdef __CHEERP__
            assert(false);
#else
            throw std::runtime_error("error deleting file: " + name);
#endif
        }
    }
}

inline void rename_and_check( const string& src, const string& dst ) {
    int r = rename(src.c_str(), dst.c_str() );
    if ( r != 0 ) {
        perror((string("error renaming file: ") + src + " to: " + dst).c_str());
#ifdef __CHEERP__
        assert(false);
#else
        throw std::runtime_error(string("error renaming file: ") + src + " to: " + dst);
#endif
    }
}


template<typename T1, typename T2>
size_t intersection_size(const T1& s1, const T2& s2)
{
    Counter c;
    set_intersection(s1.begin(), s1.end(), s2.begin(), s2.end(), std::back_inserter(c));
    return c.count;
}




bool hasEnding (string const &fullString, string const &ending) {
    if (fullString.length() >= ending.length()) {
        return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
    } else {
        return false;
    }
}
