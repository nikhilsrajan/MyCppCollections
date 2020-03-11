#pragma once

#include <iostream>
#include <sstream>

class Announcer {
public:
    template<class T>
    Announcer& operator << (const T& item) {
        ss << item;
        return *this;
    }

    void now() {
        std::cout << ss.str() << '\n' << std::flush;
        ss = std::stringstream();
    } 

private:
    std::stringstream ss;
};