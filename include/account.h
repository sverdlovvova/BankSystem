#pragma once
#include <iostream>
#include <sqlite3.h>
#include <ctime>
#include <vector>

class Account {
public:
    explicit Account();
    virtual bool deposit_money(sqlite3* db, int id, int money);
    virtual bool withdraw_money(sqlite3* db, int id, int money);
    virtual bool transfer_money(sqlite3* db, int id, int destination_id, int money);
    virtual void add_account(sqlite3* db, int id_user, int id_bank);
};

class Debit: public Account {
public:
    explicit Debit();
    bool deposit_money(sqlite3* db, int id, int money) final;
    bool withdraw_money(sqlite3* db, int id, int money) final;
    bool transfer_money(sqlite3* db, int id, int destination_id, int money) final;
    void add_account(sqlite3* db, int id_user, int id_bank) final;
};

class Credit: public Account {
private:
    time_t last_oper_time_;
public:
    explicit Credit();
    bool deposit_money(sqlite3* db, int id, int money) final;
    bool withdraw_money(sqlite3* db, int id, int money) final;
    bool transfer_money(sqlite3* db, int id, int destination_id, int money) final;
    void add_account(sqlite3* db, int id_user, int id_bank) final;
};

class Deposit: public Account {
public:
    explicit Deposit();
    bool deposit_money(sqlite3* db, int id, int money) final;
    bool withdraw_money(sqlite3* db, int id, int money) final;
    bool transfer_money(sqlite3* db, int id, int destination, int money) final;
    void add_account(sqlite3* db, int id_user, int id_bank) final;
};

std::string get_type(sqlite3* db, int id);

class Undo {
public:
    Undo();
    std::vector<std::pair<std::string, std::pair<sqlite3*, std::vector<int>>>> operations_stack_;
    void undo();
    void add_operation(const std::string& oper, sqlite3* db, int arg1, int arg2, int arg3 = 0);
};
