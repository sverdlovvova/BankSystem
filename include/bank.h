#pragma once
#include <sqlite3.h>

class Bank {
public:
    Bank();
    void add_bank(sqlite3* db, int percent_credit, int percent_deposit, 
                  int limit_credit, int limit_doubtful);
    void update_percent_credit(sqlite3* db, int id, int percent_credit);
    void update_percent_deposit(sqlite3* db, int id, int percent_deposit);
    void update_limit_credit(sqlite3* db, int id, int limit_credit);
    void update_limit_doubtful(sqlite3* db, int id, int limit_doubtful);
};
