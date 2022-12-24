#include "database.h"

namespace db{
    database::database(){}
    database::database(std::string name) : db_name(name){}

    table database::operator[](int x){
        return t[x];
    }

    std::string database::name(){
        return db_name;
    }

    void database::set_name(std::string name){
        db_name = name;
    }

    std::vector<table> database::tables(){
        return t;
    }

    bool database::is_public(){
        return ispub;
    }

    void database::make_public(){
        ispub = true;
    }

    void database::make_private(){
        ispub = false;
    }

    bool database::create_table(std::string name, std::vector<std::string> cn, std::vector<std::string> ct){
        for (int i = 0; i < (int)t.size(); i++){
            if (name == t[i].table_name()){
                return false;
            }
        }

        t.push_back(table(name, cn, ct));
        return true;
    }

    bool database::drop_table(std::string name){
        for (int i = 0; i < (int)t.size(); i++){
            if (name == t[i].table_name()){
                t.erase(t.begin() + i);
                return true;
            }
        }

        return false;
    }

}
