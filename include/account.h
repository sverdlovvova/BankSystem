#pragma once
#include <iostream>
#include <sqlite3.h>

class Account {
public:
    explicit Account();
    virtual void deposit_money(sqlite3* db, int id, int money);
    virtual void withdraw_money(sqlite3* db, int id, int money);
    virtual void transfer_money(sqlite3* db, int id, int destination_id, int money);
    virtual void add_account(sqlite3* db, int id_user, int id_bank);
};

class Debit: public Account {
public:
    explicit Debit();
    void deposit_money(sqlite3* db, int id, int money) final;
    void withdraw_money(sqlite3* db, int id, int money) final;
    void transfer_money(sqlite3* db, int id, int destination_id, int money) final;
    void add_account(sqlite3* db, int id_user, int id_bank) final;
};

class Credit: public Account {
public:
    explicit Credit();
    void deposit_money(sqlite3* db, int id, int money) final;
    void withdraw_money(sqlite3* db, int id, int money) final;
    void transfer_money(sqlite3* db, int id, int destination_id, int money) final;
    void add_account(sqlite3* db, int id_user, int id_bank) final;
};

class Deposit: public Account {
public:
    explicit Deposit();
    void deposit_money(sqlite3* db, int id, int money) final;
    void withdraw_money(sqlite3* db, int id, int money) final;
    void transfer_money(sqlite3* db, int id, int destination, int money) final;
    void add_account(sqlite3* db, int id_user, int id_bank) final;
};

