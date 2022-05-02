#pragma once
#include <iostream>

class Account {
public:
    explicit Account();
    virtual void DepositMoney(int id, int money);
    virtual void WithdrawMoney(int id, int money);
    virtual void TransferMoney(int id, int destination_id, int money);
};

class Debit: public Account {
public:
    explicit Debit();
    void DepositMoney(int id, int money) final;
    void WithdrawMoney(int id, int money) final;
    void TransferMoney(int id, int destination_id, int money) final;
};

class Credit: public Account {
public:
    explicit Credit();
    void DepositMoney(int id, int money) final;
    void WithdrawMoney(int id, int money) final;
    void TransferMoney(int id, int destination_id, int money) final;
};

class Deposit: public Account {
public:
    explicit Deposit();
    void DepositMoney(int id, int money) final;
    void WithdrawMoney(int id, int money) final;
    void TransferMoney(int id, int destination, int money) final;
};

