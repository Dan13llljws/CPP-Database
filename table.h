#pragma once

#include "row.h"
#include <iostream>
#include <fstream>

namespace db{
    class table{
    public:
        std::vector<row> t; // table 
        std::vector<std::string> col_name; // column name
        std::vector<std::string> col_type; // column type

        int col_cnt;
        std::string table_name;
        // std::map<std::string, int> col_map; //

        table(std::string name, std::vector<std::string> cn, std::vector<std::string> ct);
        void insert_row(row r);
        void print_table(std::ostream& os);
    };
}