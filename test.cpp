#include "database.h"
#include <variant>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;
using namespace db;

vector<database> dbs;
database cur_db;
bool db_in_use;
int db_name_max_len = 9;
void list_db(){
    for (int i = 0; i < db_name_max_len + 6; i++) cout << "=";
    cout << endl;
    cout << "#  DATABASES";
    for (int i = 0; i < (int)db_name_max_len - 9; i++) cout << " ";
    cout << "  #" << endl; 
    for (int i = 0; i < db_name_max_len + 6; i++) cout << "=";
    cout << endl;
    for (int i = 0; i < (int)dbs.size(); i++){
        cout << "#  " << dbs[i].db_name;
        for (int j = 0; j < db_name_max_len - (int)dbs[i].db_name.size(); j++) cout << " ";
        cout << "  #" << endl;
    }
    for (int i = 0; i < db_name_max_len + 6; i++) cout << "=";
    cout << endl;
}

bool db_search(string name){
    for (auto db : dbs){
        if (db.db_name == name){
            return true;
        }
    }
    return false;
}

void use_db(string name){
    for (auto db : dbs){
        if (db.db_name == name){
            db_in_use = true;
            cur_db = db;
        }
    }
}

void create_db(string name){
    db_name_max_len = max(db_name_max_len, (int)name.size());
    dbs.push_back(database(name));
}

void menu(){
    // system("cls");
    cout << "1. CREATE DATABASE" << endl;
    cout << "2. USE DATABASE" << endl;
    cout << "3. SEE A LIST OF DATABASES" << endl;
    cout << "4. EXIT" << endl;

    int inp;
    cin >> inp;
    if (inp == 1){
        cout << "Enter name of the new database: ";
        string tmp;
        cin >> tmp;
        if (db_search(tmp)){
            cout << "ERROR! database already exist!" << endl;
        } else {
            create_db(tmp);
            cout << tmp << " successfully created!" << endl;
        }
    } else if (inp == 2){
        cout << "Enter name of database: ";
        string tmp;
        cin >> tmp;
        if (!db_search(tmp)){
            cout << "ERROR! database not found!" << endl;
        } else {
            use_db(tmp);
            cout << tmp << " is in use!" << endl;
        }
    } else if (inp == 3){
        list_db();
    } else return;
    
    menu(); 
}
void save(){
    cout << "Creating database list..." << endl;
    ofstream ofs("db_list.txt", iostream::out);
    for (auto db : dbs){
        ofs << db.db_name + ".txt" << endl;
    }
    cout << "Database list created successfully!" << endl;

    for (auto db : dbs){
        string f = db.db_name;
        cout << "Saving " << f << " ..." << endl;
        f += ".txt";
        ofstream db_file(f, iostream::out);
        ofs << (int)db.tables.size() << endl;
        for (auto t : db.tables){
            ofs << t.table_name << '\n';
            t.print_table(ofs);
        }
    }
    cout << "Databases saved!" << endl;
}
int main(){
    system("cls");
    cout << "Loading databases..." << endl;
    // load db
    cout << "Databases loaded successfully!" << endl;

    menu();
    save();
    cout << "Goodbye!" << endl;
}
