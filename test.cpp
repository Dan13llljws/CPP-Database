#include "database.h"
#include "user.h"
#include <variant>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
using namespace db;

vector<database> dbs;
database cur_db;
bool db_in_use;
int db_name_max_len = 9;

vector<user> users;
user cur_user;

void list_db(){
    for (int i = 0; i < db_name_max_len + 6; i++) cout << "=";
    cout << endl;
    cout << "#  DATABASES";
    for (int i = 0; i < (int)db_name_max_len - 9; i++) cout << " ";
    cout << "  #" << endl; 
    for (int i = 0; i < db_name_max_len + 6; i++) cout << "=";
    cout << endl;
    for (int i = 0; i < (int)dbs.size(); i++){
        if (cur_user.has_view_perm(dbs[i].name())){
            cout << "#  " << dbs[i].name();
            for (int j = 0; j < db_name_max_len - (int)dbs[i].name().size(); j++) cout << " ";
            cout << "  #" << endl;
        }
    }
    for (int i = 0; i < db_name_max_len + 6; i++) cout << "=";
    cout << endl;
}

bool db_search(string name){
    for (auto db : dbs){
        if (db.name() == name){
            return true;
        }
    }
    return false;
}

void create_db(){
    cout << "Enter name of the new database: ";
    string name;
    cin >> name;
    while(db_search(name)){
        cout << "ERROR! database already exist!" << endl;
        cout << "Enter another name: ";
        cin >> name;
    }

    database new_db(name);
    cout << name << " successfully created!" << endl;

    
    cout << "Do you want this database to be public? (y/n): ";
    string tmp;
    cin >> tmp; 
    if (tmp == "Y" || tmp == "y"){
        new_db.make_public();
        for (user &usr : users){
            usr.add_view_perm(name);
        }
        cur_user.add_edit_perm(name);
    } else {
        new_db.make_private();
        cur_user.add_view_perm(name);
        cur_user.add_edit_perm(name);
    }

    db_name_max_len = max(db_name_max_len, (int)name.size());
    dbs.push_back(new_db);
}

void use_db(){
    cout << "Enter name of database: ";
    string name;
    cin >> name;
    while(!db_search(name)){
        cout << "ERROR! database not found!" << endl;
        cout << "Enter another name: ";
        cin >> name;
    }

    for (auto db : dbs){
        if (db.name() == name){
            db_in_use = true;
            cur_db = db;
            break;
        }
    }

    cout << name << " is in use!" << endl;
}


void menu(){

    auto display_options = [&](){
        cout << "1. CREATE DATABASE" << endl;
        cout << "2. USE DATABASE" << endl;
        cout << "3. SEE A LIST OF DATABASES" << endl;
        cout << "4. EXIT" << endl;
        // 
    };

    display_options();
    int inp;
    cin >> inp;

    while(inp != 4){
        if (inp == 1){
            create_db();
        } else if (inp == 2){
            use_db();
        } else if (inp == 3){
            list_db();
        } 

        display_options();
        cin >> inp;
    }
}

void load(){
    cout << "Loading users..." << endl;
    
    ifstream ifs("users.txt");
    string buf;
    while(ifs >> buf){
        cout <<buf << endl;
        string username, password, p;

        username = buf;
        ifs >> password;
        ifs.ignore();


        user usr(username, password);

        getline(ifs, buf);
        istringstream iss(buf);
        while(iss >> p) usr.add_edit_perm(p);

        getline(ifs, buf);
        iss.str(buf);
        while(iss >> p) usr.add_view_perm(p);

        users.push_back(usr);
    }
    
    cout << "Loading databases..." << endl;
    
    ifstream list_fs("db_list.txt");
    int db_cnt = 0;
    list_fs >> db_cnt;

    for (int i = 0; i < db_cnt; i++){
        string db_name;
        list_fs >> db_name;
        db_name_max_len = max(db_name_max_len, (int)db_name.size());
        for (int j = 0; j < 4; j++) db_name.pop_back();
        dbs.push_back(database(db_name));
    }
    
    cout << "list loaded" << endl;

    for (int i = 0; i < db_cnt; i++){
        string f = dbs[i].name();
        f += ".txt";
        ifstream ifs(f);
        int t_cnt = 0;
        ifs >> t_cnt;

        for (int j = 0; j < t_cnt; j++){
            int r, c;
            ifs >> r >> c;
    
            vector<string> name(c), type(c);

            for (int k = 0; k < c; k++){
                ifs >> name[i];
            }
            for (int k = 0; k < c; k++){
                ifs >> type[i];
            }

            dbs[i].create_table(dbs[i].name(), name, type);

            for (int k = 0; k < r; k++){
                row rw(c);
                for (int k1 = 0; k1 < c; k1++){
                    if (type[k1] == "int"){
                        int x;
                        cin >> x;
                        rw[k1] = x;
                    } else if (type[k1] == "string"){
                        string x;
                        cin >> x;
                        rw[k1] = x;
                    } else if (type[k1] == "bool"){
                        bool x;
                        cin >> x;
                        rw[k1] = x;
                    } else if (type[k1] == "double"){
                        double x;
                        cin >> x;
                        rw[k1] = x;
                    }
                }
                dbs[i][j].insert_row(rw);
            }
        }
    }
    cout << "Databases loaded successfully!" << endl;
}


bool check_username(string username){
    for (user usr : users){
        if (username == usr.get_name()){
            cur_user = usr;
            return true;
        }
    }
    return false;
}

bool check_password(string password){
    return password == cur_user.get_pass();
}

bool valid_password(string password){
    if ((int)password.size() < 8) cout << "Password too short! ";
    if ((int)password.size() > 20) cout << "Password too long! ";
    for (char c : password){
        if (!isdigit(c) && !(c <= 'z' && c >= 'a') && !(c <= 'Z' && c >= 'A')){
            cout << "Password contains character \'" << c << "\'! ";
            return false;
        }
    }
    return true;
}

void sign_up(){
    string username;
    cout << "Enter the username: ";
    cin >> username;
    while(check_username(username)){
        cout << "User already exist! Please Enter another username: ";
        cin >> username;
    }
    string password;
    cout << "Enter the password (Password must contain 8-20 alphanumeric characters): ";
    cin >> password;
    while(!valid_password(password)){
        cout << "Enter a new password: ";
        cin >> password;
    }
    users.push_back(user(username, password));
    cur_user = users.back();
}

void login(){
    cout << "Enter Username: ";
    string username;
    cin >> username;
    while(true){
        while(!check_username(username)){
            cout << "User do not exist!" << endl;
            cout << "Enter 'c' to create new user: ";
            cin >> username;
            if (username == "c" || username == "C"){
                sign_up();
                return;
            }
        }
        cout << "Enter password: ";
        string password;
        cin >> password;
        while(!check_password(password)){
            cout << "Username and password mismatch!" << endl;
            cout << "Enter 'r' to re-enter username: ";
            cin >> password;
            if (password == "r" || password == "R") break;
        }
        if (check_password(password)){
            return;
        }
    }
}

void save(){
    cout << "Creating user list..." << endl;

    ofstream ofs("users.txt");
    for (user usr : users){
        ofs << usr.get_name() << endl;
        ofs << usr.get_pass() << endl;
        for (auto p : usr.get_edit_perm()) ofs << p << ' ';
        ofs << endl;
        for (auto p : usr.get_view_perm()) ofs << p << ' ';
        ofs << endl;
    }

    cout << "Creating database list..." << endl;

    ofs.open("db_list.txt");
    ofs << (int)dbs.size() << endl;
    
    for (auto db : dbs){
        ofs << db.name() + ".txt" << endl;
    }
    
    cout << "Database list created successfully!" << endl;

    for (auto db : dbs){
        string f = db.name();
        cout << "Saving " << f << " ..." << endl;
        f += ".txt";

        ofs.open(f); 
        ofs << (int)db.tables().size() << endl;
        
        for (auto t : db.tables()){
            ofs << t.table_name() << '\n';
            t.print_table(ofs);
        }
    }
    cout << "Databases saved!" << endl;
}

int main(){
    system("cls");
    load();
    login();
    cout << "Logged in Successfully!" << endl;
    menu();
    save();
    cout << "Goodbye!" << endl;
}
