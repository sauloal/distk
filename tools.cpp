//https://stackoverflow.com/questions/874134/find-if-string-ends-with-another-string-in-c

#include "tools.hpp"

bool hasEnding (string const &fullString, string const &ending) {
    if (fullString.length() >= ending.length()) {
        return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
    } else {
        return false;
    }
}
