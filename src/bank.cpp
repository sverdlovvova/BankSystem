#include "bank.h"
#include <sqlite3.h>
#include <string>
#include <iostream>

Bank::Bank() {}

int number_of_banks;

static int number_callback(void* data, int argc, char **argv, 
                           char **azColName) {
    ++number_of_banks;
    return 0;
}

void Bank::add_bank(sqlite3* db, int percent_credit, int percent_deposit, 
                    int limit_credit, int limit_doubtful) {
    std::string update = "SELECT * FROM BANKS";
    number_of_banks = 0;
    int rc = sqlite3_exec(db, update.c_str(), number_callback, NULL, NULL);
    
    update = "INSERT INTO BANKS VALUES (" + 
             std::__cxx11::to_string(number_of_banks + 1) + ", " + 
             std::__cxx11::to_string(percent_credit) + ", " +
             std::__cxx11::to_string(percent_deposit) + ", " +
             std::__cxx11::to_string(limit_credit) + ", " +
             std::__cxx11::to_string(limit_doubtful) + ")";
    rc = sqlite3_exec(db, update.c_str(), NULL, NULL, NULL);
    std::cout << "Added bank with ID=" << number_of_banks + 1 << '\n';
}

void Bank::update_percent_credit(sqlite3* db, int id, int percent_credit) {
    std::string update = "UPDATE BANKS set percent_credit = " + 
                         std::__cxx11::to_string(percent_credit) + 
                         "WHERE ID = " + std::__cxx11::to_string(id);
    int rc = sqlite3_exec(db, update.c_str(), NULL, NULL, NULL);
}
void Bank::update_percent_deposit(sqlite3* db, int id, int percent_deposit) { 
    std::string update = "UPDATE BANKS set percent_deposit = " + 
                         std::__cxx11::to_string(percent_deposit) + 
                         "WHERE ID = " + std::__cxx11::to_string(id);
    int rc = sqlite3_exec(db, update.c_str(), NULL, NULL, NULL);
}

void Bank::update_limit_credit(sqlite3* db, int id, int limit_credit) {
    std::string update = "UPDATE BANKS set limit_credit = " + 
                         std::__cxx11::to_string(limit_credit) + 
                         "WHERE ID = " + std::__cxx11::to_string(id);
    int rc = sqlite3_exec(db, update.c_str(), NULL, NULL, NULL);
}

void Bank::update_limit_doubtful(sqlite3* db, int id, int limit_doubtful) {
    std::string update = "UPDATE BANKS set limit_doubtful = " + 
                         std::__cxx11::to_string(limit_doubtful) + 
                         "WHERE ID = " + std::__cxx11::to_string(id);
    int rc = sqlite3_exec(db, update.c_str(), NULL, NULL, NULL);
}

