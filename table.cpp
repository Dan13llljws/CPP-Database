#include "table.h"

namespace db{
    table::table(std::string name, 
                std::vector<std::string> cn, 
                std::vector<std::string> ct): cn(cn), ct(ct), tn(name){
        ccnt = (int)cn.size();
    }

    row& table::operator[](int x){
        return t[x];
    }

    std::string table::col_name(int x){
        return cn[x];
    }

    std::string table::col_type(int x){
        return ct[x];
    }

    std::string table::table_name(){
        return tn;
    }

    void table::set_table_name(std::string name){
        tn = name;
    }

    int table::col_cnt(){
        return ccnt;
    }

    void table::set_col_cnt(int cn){
        ccnt = cn;
    }

    void table::insert_row(row r){
        t.push_back(r);
    }

    void table::print_table(std::ostream& os = std::cout){
        os << (int)t.size() << ' ' << ccnt << std::endl;
        for (auto s : cn) std::cout << s << std::endl;
        for (auto s : ct) std::cout << s << std::endl;
        for (auto r : t){
            for (int i = 0; i < (int)r.size(); i++){
                if (ct[i] == "int"){
                    os << std::get<int>(r[i]) << ' ';
                } else if (ct[i] == "string"){
                    os << std::get<std::string>(r[i]) << ' ';
                } else if (ct[i] == "bool"){
                    os << std::get<bool>(r[i]) << ' ';
                } else if (ct[i] == "double"){
                    os << std::get<double>(r[i]) << ' ';
                }
            }
            os << std::endl;
        }
        os << std::endl;
    }
}