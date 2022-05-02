#pragma once
#include <string>
#include <sqlite3.h>

class Customer {
    //sqlite3 *db;

public:
    Customer();

    void set_name(int id, const std::string& name);
    void set_surname(int id, const std::string& surname);
    void set_address(int id, const std::string& address);
    void set_passport(int id, int passport);

    void update_limit(int id);

    /*
    std::string get_name(int id) const;
    std::string get_surname(int id) const;
    std::string get_address(int id) const;
    int get_passport(int id) const;
    */

    bool has_limit(int id);
};
