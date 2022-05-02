#pragma once

class Bank {
public:
    /*
    int percent_credit;
    int percent_deposit;
    int limit_credit;
    int limit_doubtful;
    */

    Bank();
    void update_percent_credit(int id, int percent_credit);
    void update_percent_deposit(int id, int percent_deposit);
    void update_limit_credit(int id, int limit_credit);
    void update_limit_doubtful(int id, int limit_doubtful);
};
