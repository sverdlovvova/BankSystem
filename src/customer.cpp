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

Customer::Customer() { }

int number_of_customers;

static int number_callback(void* data, int argc, char **argv, 
                           char **azColName) {
    ++number_of_customers;
    return 0;
}

void Customer::add_customer(sqlite3* db, const std::string& name,
                            const std::string& surname) {
    number_of_customers = 0;
    std::string update = "SELECT * FROM USERS";
    int rc = sqlite3_exec(db, update.c_str(), number_callback, NULL, NULL);

    update = "INSERT INTO USERS VALUES ("
             + std::__cxx11::to_string(number_of_customers + 1) + ", '" + name + 
             "', '" + surname + "', NULL, NULL)";
    rc = sqlite3_exec(db, update.c_str(), NULL, NULL, NULL);
    std::cout << "Added customer with ID=" << number_of_customers + 1 << '\n';
}

void Customer::set_name(sqlite3* db, int id, const std::string& name) {
    std::string update = "UPDATE USERS set NAME = '" + name + "' WHERE ID = " +
        std::__cxx11::to_string(id);
    int rc = sqlite3_exec(db, update.c_str(), NULL, NULL, NULL);
}

void Customer::set_surname(sqlite3* db, int id, const std::string& surname) {
    std::string update = "UPDATE USERS set SURNAME = '" + surname + 
        "' WHERE ID = " + std::__cxx11::to_string(id);
    int rc = sqlite3_exec(db, update.c_str(), NULL, NULL, NULL);
}

void Customer::set_address(sqlite3* db, int id, const std::string& address) { 
    std::string update = "UPDATE USERS set ADDRESS = '" + address + 
        "' WHERE ID = " + std::__cxx11::to_string(id);
    int rc = sqlite3_exec(db, update.c_str(), NULL, NULL, NULL);
}

void Customer::set_passport(sqlite3* db, int id, int passport) {
    std::string update = "UPDATE USERS set PASSPORT = '" +
        std::__cxx11::to_string(passport) +  "' WHERE ID = " + 
        std::__cxx11::to_string(id);
    int rc = sqlite3_exec(db, update.c_str(), NULL, NULL, NULL);
}

bool has_limit_flag;
static int has_limit_callback(sqlite3* db, void *data, int argc, char **argv,
                              char **azColName) {
    for (int i = 0; i < argc; ++i) {
        if (!argv[i]) {
            has_limit_flag = true;
            return 0;
        }
    }
    return 0;
}

bool Customer::has_limit(sqlite3* db, int id) {
    has_limit_flag = false;
    std::string func = "SELECT * FROM USERS WHERE ID = " + 
                       std::__cxx11::to_string(id);
    int rc = sqlite3_exec(db, func.c_str(), NULL, NULL, NULL);
    return has_limit_flag;
}
