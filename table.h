#pragma once

#include "row.h"
#include <iostream>
#include <fstream>

namespace db{
    class table{
    private:
        std::vector<row> t; // table 
        std::vector<std::string> cn; // column name
        std::vector<std::string> ct; // column type
        int ccnt;
        std::string tn;
    public:
        table(std::string name, std::vector<std::string> cn, std::vector<std::string> ct);
        row& operator[](int x);
        std::string col_name(int x);
        std::string col_type(int x);
        std::string table_name();
        void set_table_name(std::string x);
        int col_cnt();
        void set_col_cnt(int x);
        void insert_row(row r);
        void print_table(std::ostream& os);
    };
}