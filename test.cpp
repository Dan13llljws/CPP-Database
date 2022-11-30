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
        cout << "#  " << dbs[i].name();
        for (int j = 0; j < db_name_max_len - (int)dbs[i].name().size(); j++) cout << " ";
        cout << "  #" << endl;
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

void use_db(string name){
    for (auto db : dbs){
        if (db.name() == name){
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

    ofstream ofs("db_list.txt");
    ofs << (int)dbs.size() << endl;
    
    for (auto db : dbs){
        ofs << db.name() + ".txt" << endl;
    }
    
    cout << "Database list created successfully!" << endl;

    for (auto db : dbs){
        string f = db.name();
        cout << "Saving " << f << " ..." << endl;
        f += ".txt";
        
        ofstream db_file(f);
        db_file << (int)db.tables().size() << endl;
        
        for (auto t : db.tables()){
            db_file << t.table_name() << '\n';
            t.print_table(db_file);
        }
    }
    cout << "Databases saved!" << endl;
}

void load(){
    cout << "Loading databases..." << endl;
    
    ifstream list_fs("db_list.txt");
    int db_cnt = 0;
    list_fs >> db_cnt;

    for (int i = 0; i < db_cnt; i++){
        string db_name;
        for (int j = 0; j < 4; j++) db_name.pop_back();
        list_fs >> db_name;
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

int main(){
    system("cls");
    load();
    menu();
    save();
    cout << "Goodbye!" << endl;
}
