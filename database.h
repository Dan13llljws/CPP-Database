#pragma once

#include "table.h"

namespace db{
    class database {
    public:
        std::vector<table> tables;
        std::string db_name;

        database(){};
        database(std::string name) : db_name(name){};
        bool create_table(std::string name, std::vector<std::string> cn, std::vector<std::string> ct);
        bool drop_table(std::string name);
    };

}