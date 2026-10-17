#include <sqlite3.h>
#include <iostream>

int main(){
    sqlite3* db;
    if(sqlite3_open("Test.db", &db) == SQLITE_OK){
        std::cout << "SQLite C API is working" << std::endl;
    }
    sqlite3_close(db);
}