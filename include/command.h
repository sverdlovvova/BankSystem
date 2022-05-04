#include "account.h"

class Command() {
public:
    virtual void execute() const = 0;
}

class TransferMoney(): public command {
public:
    void execute() const {

    }
};

class WithdrawMoney(): public command {
public:
    void execute() const {

    }
};

class DepositMoney(): public command {
public:
    void execute() const {

    }
};

