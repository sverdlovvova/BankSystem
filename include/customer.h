#pragma once
#include <string>
#include <sqlite3.h>

class Customer {
public:
    Customer();

    void add_customer(sqlite3* db, const std::string& name, 
                      const std::string& surname);
    void set_name(sqlite3* db, int id, const std::string& name);
    void set_surname(sqlite3* db, int id, const std::string& surname);
    void set_address(sqlite3* db, int id, const std::string& address);
    void set_passport(sqlite3* db, int id, int passport);
    bool has_limit(sqlite3* db, int id);
};
