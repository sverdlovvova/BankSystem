#include "customer.h"
#include <string>
#include <sqlite3.h>
#include <iostream>

static int callback(void *data, int argc, char **argv, char **azColName) {
    for (int i = 0; i < argc; ++i) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

Customer::Customer() {
    /*sqlite3* db;
    int rc = sqlite3_open("database.db", &db);
    std::cout << "ok\n";
    const char sql[] = "CREATE TABLE words("
                      "ID INT PRIMARY       KEY    NOT NULL,"
                      "CURRENT_WORD         TEXT   NOT NULL,"
                      "OCCERANCES           INT    NOT NULL);";
    rc = sqlite3_exec(db, sql, NULL, NULL, NULL);
    const char* ins = "INSERT INTO words VALUES (1, 'a', 1)";
    rc = sqlite3_exec(db, ins, NULL, NULL, NULL);
    const char* select = "SELECT * FROM words";
    rc = sqlite3_exec(db, select, callback, NULL, NULL);*/
}

void Customer::set_name(int id, const std::string& name) { }

void Customer::set_surname(int id, const std::string& surname) { }

void Customer::set_address(int id, const std::string& address) { }

void Customer::set_passport(int id, int passport) { }

void Customer::update_limit(int id) { }

bool Customer::has_limit(int id) { return false; }
