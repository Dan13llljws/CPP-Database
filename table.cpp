#include "table.h"

namespace db{
    table::table(std::string name, 
                std::vector<std::string> cn, 
                std::vector<std::string> ct) : table_name(name), col_name(cn), col_type(ct){
        col_cnt = (int)cn.size();
    }

    void table::insert_row(row r){
        t.push_back(r);
    }

    void table::print_table(std::ostream& os = std::cout){
        for (auto s : col_name) std::cout << "\"" + s + "\"" << std::endl;
        for (auto s : col_type) std::cout << "\"" + s + "\"" << std::endl;
        for (auto r : t){
            for (int i = 0; i < (int)r.size(); i++){
                if (col_type[i] == "int"){
                    os << std::get<int>(r[i]) << ' ';
                } else if (col_type[i] == "string"){
                    os << "\"" + std::get<std::string>(r[i]) + "\"" << ' ';
                } else if (col_type[i] == "bool"){
                    os << std::get<bool>(r[i]) << ' ';
                } else if (col_type[i] == "double"){
                    os << std::get<double>(r[i]) << ' ';
                }
            }
            os << std::endl;
        }
        os << std::endl;
    }
}