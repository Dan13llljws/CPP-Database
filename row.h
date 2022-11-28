#pragma once

#include <variant>
#include <vector>
#include <string>

namespace db{
    typedef std::variant<int, std::string, bool, double> rowtypes;
    class row {
    public:
        std::vector<rowtypes> r;
    
        row(int n);
        int size();
        rowtypes operator[](int x);
    };
}