#include "account.h"
#include <sqlite3.h>

int number_of_accounts;
static int number_callback(void *data, int argc, char **argv, 
                           char **azColName) {
    ++number_of_accounts;
    return 0;
}

Account::Account() { }

void Account::deposit_money(sqlite3* db, int id, int money) { }

void Account::withdraw_money(sqlite3* db, int id, int money) { }

void Account::transfer_money(sqlite3* db, int id, int destination_id, 
                             int money) { }

void Account::add_account(sqlite3* db, int user_id, int bank_id) { }

Debit::Debit() : Account() {}

void Debit::deposit_money(sqlite3* db, int id, int money) {
     std::string update = "UPDATE ACCOUNTS set MONEY=MONEY+" +
                         std::__cxx11::to_string(money) + 
                         " WHERE ID = " +
                         std::__cxx11::to_string(id);
    int rc = sqlite3_exec(db, update.c_str(), NULL, NULL, NULL);
}

void Debit::withdraw_money(sqlite3* db, int id, int money) {
    std::string update = "update accounts set money=money-" +
                         std::__cxx11::to_string(money) + 
                         " where id = " +
                         std::__cxx11::to_string(id);
    int rc = sqlite3_exec(db, update.c_str(), NULL, NULL, NULL);
}

void Debit::transfer_money(sqlite3* db, int id, int destination_id, int money) {
    std::string update = "UPDATE ACCOUNTS set MONEY=MONEY-" +
                         std::__cxx11::to_string(money) + 
                         " WHERE ID = " +
                         std::__cxx11::to_string(id);
    int rc = sqlite3_exec(db, update.c_str(), NULL, NULL, NULL);
    update = "UPDATE ACCOUNTS set MONEY=MONEY+" +
                         std::__cxx11::to_string(money) + 
                         " WHERE ID = " +
                         std::__cxx11::to_string(destination_id);
    rc = sqlite3_exec(db, update.c_str(), NULL, NULL, NULL);
}

void Debit::add_account(sqlite3* db, int id_user, int id_bank) {
    number_of_accounts = 0;
    std::string update = "SELECT * FROM ACCOUNTS";
    int rc = sqlite3_exec(db, update.c_str(), number_callback, NULL, NULL);
    update = "INSERT INTO ACCOUNTS VALUES (" + 
             std::__cxx11::to_string(number_of_accounts + 1) +
             ", Debit, " + 
             std::__cxx11::to_string(id_user) + ", " +
             std::__cxx11::to_string(id_bank) + ", 0)";
    rc = sqlite3_exec(db, update.c_str(), NULL, NULL, NULL);
}

Credit::Credit() : Account() { }

void Credit::deposit_money(sqlite3* db, int id, int money) {
    std::string update = "UPDATE ACCOUNTS set MONEY=MONEY+" +
                         std::__cxx11::to_string(money) + 
                         " WHERE ID = " +
                         std::__cxx11::to_string(id);
    int rc = sqlite3_exec(db, update.c_str(), NULL, NULL, NULL);
}

void Credit::withdraw_money(sqlite3* db, int id, int money) {
    std::string update = "update accounts set money=money-" +
                         std::__cxx11::to_string(money) + 
                         " where id = " +
                         std::__cxx11::to_string(id);
    int rc = sqlite3_exec(db, update.c_str(), NULL, NULL, NULL);
}

void Credit::transfer_money(sqlite3* db, int id, int destination_id, 
                            int money) {
    std::string update = "UPDATE ACCOUNTS set MONEY=MONEY-" +
                         std::__cxx11::to_string(money) + 
                         " WHERE ID = " +
                         std::__cxx11::to_string(id);
    int rc = sqlite3_exec(db, update.c_str(), NULL, NULL, NULL);
    update = "UPDATE ACCOUNTS set MONEY=MONEY+" +
                         std::__cxx11::to_string(money) + 
                         " WHERE ID = " +
                         std::__cxx11::to_string(destination_id);
    rc = sqlite3_exec(db, update.c_str(), NULL, NULL, NULL);
}

void Credit::add_account(sqlite3* db, int id_user, int id_bank) {
    number_of_accounts = 0;
    std::string update = "SELECT * FROM ACCOUNTS";
    int rc = sqlite3_exec(db, update.c_str(), number_callback, NULL, NULL);
    update = "INSERT INTO ACCOUNTS VALUES (" + 
             std::__cxx11::to_string(number_of_accounts + 1) +
             ", Debit, " + 
             std::__cxx11::to_string(id_user) + ", " +
             std::__cxx11::to_string(id_bank) + ", 0)";
    rc = sqlite3_exec(db, update.c_str(), NULL, NULL, NULL);
}

Deposit::Deposit() : Account() { }

void Deposit::deposit_money(sqlite3* db, int id, int money) {
    std::string update = "UPDATE ACCOUNTS set MONEY=MONEY+" +
                         std::__cxx11::to_string(money) + 
                         " WHERE ID = " +
                         std::__cxx11::to_string(id);
    int rc = sqlite3_exec(db, update.c_str(), NULL, NULL, NULL);
}

void Deposit::withdraw_money(sqlite3* db, int id, int money) {
    std::string update = "update accounts set money=money-" +
                         std::__cxx11::to_string(money) + 
                         " where id = " +
                         std::__cxx11::to_string(id);
    int rc = sqlite3_exec(db, update.c_str(), NULL, NULL, NULL);
}

void Deposit::transfer_money(sqlite3* db, int id, int destination_id, 
                            int money) {
    std::string update = "UPDATE ACCOUNTS set MONEY=MONEY-" +
                         std::__cxx11::to_string(money) + 
                         " WHERE ID = " +
                         std::__cxx11::to_string(id);
    int rc = sqlite3_exec(db, update.c_str(), NULL, NULL, NULL);
    update = "UPDATE ACCOUNTS set MONEY=MONEY+" +
                         std::__cxx11::to_string(money) + 
                         " WHERE ID = " +
                         std::__cxx11::to_string(destination_id);
    rc = sqlite3_exec(db, update.c_str(), NULL, NULL, NULL);
}

void Deposit::add_account(sqlite3* db, int id_user, int id_bank) {
    number_of_accounts = 0;
    std::string update = "SELECT * FROM ACCOUNTS";
    int rc = sqlite3_exec(db, update.c_str(), number_callback, NULL, NULL);
    update = "INSERT INTO ACCOUNTS VALUES (" + 
             std::__cxx11::to_string(number_of_accounts + 1) +
             ", Debit, " + 
             std::__cxx11::to_string(id_user) + ", " +
             std::__cxx11::to_string(id_bank) + ", 0)";
    rc = sqlite3_exec(db, update.c_str(), NULL, NULL, NULL);
}

