#include "user.h"

namespace db{
    user::user(){}
    user::user(std::string n, std::string p): name(n), pass(p){}

    std::string user::get_name(){
        return name;
    }

    std::string user::get_pass(){
        return pass;
    }
    
    std::vector<std::string> user::get_edit_perm(){
        return edit_perm;
    }

    std::vector<std::string> user::get_view_perm(){
        return view_perm;
    }

    bool user::add_edit_perm(std::string db){
        for (std::string perm : edit_perm){
            if (db == perm){
                return false;
            } 
        }        
        edit_perm.push_back(db);
        return true;
    }

    bool user::add_view_perm(std::string db){
        for (std::string perm : view_perm){
            if (db == perm){
                return false;
            } 
        }        
        view_perm.push_back(db);
        return true;
    }

    bool user::rem_edit_perm(std::string db){
        for (int i = 0; i < (int)edit_perm.size(); i++){
            if (db == edit_perm[i]){
                edit_perm.erase(edit_perm.begin() + i);
                return true;
            }
        }
        return false;
    }

    bool user::rem_view_perm(std::string db){
        for (int i = 0; i < (int)view_perm.size(); i++){
            if (db == view_perm[i]){
                view_perm.erase(view_perm.begin() + i);
                return true;
            }
        }
        return false;
    }

    bool user::has_edit_perm(std::string db){
        for (std::string perm : view_perm){
            if (db == perm){
                return false;
            } 
        }        
        return true;
    }

    bool user::has_view_perm(std::string db){
        for (std::string perm : view_perm){
            if (db == perm){
                return false;
            } 
        }        
        return true;
    }
}