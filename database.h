#pragma once

#include "table.h"

namespace db{
    class database {
    private:
        std::vector<table> t;
        std::string db_name;
        bool ispub;
    public:
        database();
        database(std::string name);
        table operator[](int x);
        std::string name();
        void set_name(std::string name);
        std::vector<table> tables();
        bool is_public();
        void make_public();
        void make_private();

        bool create_table(std::string name, std::vector<std::string> cn, std::vector<std::string> ct);
        bool drop_table(std::string name);
    };

}