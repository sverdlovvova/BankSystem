#include <iostream>

class Account {
private:
    int id;
public:
    virtual void DepositMoney(const int AccountId) = 0;
    virtual void WithdrawMoney(const int AccountId) = 0;
    virtual void TransferMoney(const int AccountId) = 0;
};

class Debit: public Account {
public:
    void DepositMoney(const int AccountId) override;
};

class Credit: public Account {
public:
    void WithdrawMoney(const int AccountId) = 0;
};

class Deposit: public Account {
public:
    void WithdrawMoney(const int AccountId) = 0;
};
