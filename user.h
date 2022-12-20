#pragma once

#include <vector>
#include <string>

namespace db{
    class user{
    private:
        std::string name, pass;
        std::vector<std::string> edit_perm;
        std::vector<std::string> view_perm;
    public:
        user();
        user(std::string n, std::string p);
        std::string get_name();
        std::string get_pass();
        std::vector<std::string> get_edit_perm();
        std::vector<std::string> get_view_perm();
        bool add_edit_perm(std::string db);
        bool add_view_perm(std::string db);
        bool rem_edit_perm(std::string db);
        bool rem_view_perm(std::string db);
        bool has_edit_perm(std::string db);
        bool has_view_perm(std::string db);
    };
}