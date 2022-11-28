#include "database.h"

#include <iostream>

namespace db{
    
    bool database::create_table(std::string name, std::vector<std::string> cn, std::vector<std::string> ct){
        for (int i = 0; i < (int)database::tables.size(); i++){
            if (name == tables[i].table_name){
                return false;
            }
        }

        tables.push_back(table(name, cn, ct));
        return true;
    }

    bool database::drop_table(std::string name){
        for (int i = 0; i < (int)database::tables.size(); i++){
            if (name == tables[i].table_name){
                tables.erase(tables.begin() + i);
                return true;
            }
        }

        return false;
    }
}
