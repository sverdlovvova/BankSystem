#include "account.h"
#include <sqlite3.h>
#include <ctime>

int number_of_accounts;
static int number_callback(void *data, int argc, char **argv, 
                           char **azColName) {
    ++number_of_accounts;
    return 0;
}

bool is_doubtful;
static int check_for_doubtful_callback(void *data, int argc, char **argv,
                              char **azColName) {
    is_doubtful = (argv[3] != NULL && argv[4] != NULL);
    return 0;
}

int limit_doubtful;
static int limit_doubtful_callback(void *data, int argc, char **argv,
                            char **azColName) {
    limit_doubtful = std::__cxx11::stoi(argv[0]);
    return 0;
}

int time_;
static int time_callback(void *data, int argc, char** argv, char **azColName) {
    time_ = std::__cxx11::stoi(argv[0]);
    return 0;
}

Account::Account() { }

bool Account::deposit_money(sqlite3* db, int id, int money) { return false; }

bool Account::withdraw_money(sqlite3* db, int id, int money) { return false; }

bool Account::transfer_money(sqlite3* db, int id, int destination_id, 
                             int money) { return false; }

void Account::add_account(sqlite3* db, int user_id, int bank_id) { }

Debit::Debit() : Account() {}

bool Debit::deposit_money(sqlite3* db, int id, int money) {
     std::string update = "UPDATE ACCOUNTS set MONEY=MONEY+" +
                         std::__cxx11::to_string(money) + 
                         " WHERE ID = " +
                         std::__cxx11::to_string(id);
    int rc = sqlite3_exec(db, update.c_str(), NULL, NULL, NULL);
    std::cout << "Deposited successfully\n";
    return true;
}

int amount_money = 0;
static int get_money_callback(void *data, int argc, char **argv, 
        char **azColName) {
    amount_money = std::__cxx11::stoi(argv[0]);
    return 0;
}

int bank_id = 0;
static int bank_id_callback(void *data, int argc, char **argv, 
        char **azColName) {
    bank_id = std::__cxx11::stoi(argv[0]);
    return 0;
}

bool check_for_doubtful(sqlite3* db, int id, int money) {
    std::string update = "SELECT * FROM USERS WHERE ID=" +
             std::__cxx11::to_string(id);
    int rc = sqlite3_exec(db, update.c_str(), check_for_doubtful_callback, 
            NULL, NULL);
    if (is_doubtful) {
        update = "SELECT BANK_ID FROM ACCOUTNS WHERE ID=" +
                 std::__cxx11::to_string(id);
        rc = sqlite3_exec(db, update.c_str(), bank_id_callback, NULL, NULL);
        update = "SELECT LIMIT_DOUBTFUL FROM BANKS WHERE ID=" +
                 std::__cxx11::to_string(bank_id);
        rc = sqlite3_exec(db, update.c_str(), limit_doubtful_callback,
                NULL, NULL);
        if (money > limit_doubtful) {
            std::cout << "You can't withdraw more than " << limit_doubtful << 
                " until you have correct address and passport\n";
            return true;
        }
    }
    return false;
}

bool Debit::withdraw_money(sqlite3* db, int id, int money) {
    std::string update = "SELECT MONEY FROM ACCOUNTS WHERE ID=" +
                         std::__cxx11::to_string(id);
    int rc = sqlite3_exec(db, update.c_str(), get_money_callback, NULL, NULL);
    if (amount_money < money) {
        std::cout << "Insufficient funds\n";
        return false;
    }
    if (check_for_doubtful(db, id, money)) {
        return false;
    }
    update = "UPDATE ACCOUNTS set MONEY=MONEY-" +
                         std::__cxx11::to_string(money) + 
                         " WHERE id = " +
                         std::__cxx11::to_string(id);
    rc = sqlite3_exec(db, update.c_str(), NULL, NULL, NULL);
    std::cout << "Withdrawed successfully\n";
    return true;
}

bool Debit::transfer_money(sqlite3* db, int id, int destination_id, int money) {
    std::string update = "SELECT MONEY FROM ACCOUNTS WHERE ID=" +
                         std::__cxx11::to_string(id);
    int rc = sqlite3_exec(db, update.c_str(), get_money_callback, NULL, NULL);
    if (amount_money < money) {
        std::cout << "Insufficient funds\n";
        return false;
    }

    if (check_for_doubtful(db, id, money)) {
        return false;
    }

    update = "UPDATE ACCOUNTS set MONEY=MONEY-" +
                         std::__cxx11::to_string(money) + 
                         " WHERE ID = " +
                         std::__cxx11::to_string(id);
    rc = sqlite3_exec(db, update.c_str(), NULL, NULL, NULL);
    update = "UPDATE ACCOUNTS set MONEY=MONEY+" +
                         std::__cxx11::to_string(money) + 
                         " WHERE ID = " +
                         std::__cxx11::to_string(destination_id);
    rc = sqlite3_exec(db, update.c_str(), NULL, NULL, NULL);
    std::cout << "Transfered successfully\n";
    return true;
}

void Debit::add_account(sqlite3* db, int id_user, int id_bank) {
    number_of_accounts = 0;
    std::string update = "SELECT * FROM ACCOUNTS";
    int rc = sqlite3_exec(db, update.c_str(), number_callback, NULL, NULL);
    update = "INSERT INTO ACCOUNTS VALUES (" + 
        std::__cxx11::to_string(number_of_accounts + 1) +
        ", 'Debit', " + 
             std::__cxx11::to_string(id_user) + ", " +
             std::__cxx11::to_string(id_bank) + ", 0, NULL)";
    rc = sqlite3_exec(db, update.c_str(), NULL, NULL, NULL);
    std::cout << "Added account with ID=" << 
                 std::__cxx11::to_string(number_of_accounts + 1) << '\n';
}

Credit::Credit() : Account() { }

int percent;
static int percent_callback(void *data, int argc, char **argv, 
        char **azColName) {
    percent = std::__cxx11::stoi(argv[0]);
    return 0;
}

bool Credit::deposit_money(sqlite3* db, int id, int money) {
    std::string update = "SELECT DATE FROM ACCOUNTS WHERE ID=" +
        std::__cxx11::to_string(id);
    int rc = sqlite3_exec(db, update.c_str(), time_callback, NULL, NULL);
    update = "SELECT MONEY FROM ACCOUNTS WHERE ID=" +
        std::__cxx11::to_string(id);
    rc = sqlite3_exec(db, update.c_str(), get_money_callback, NULL, NULL);
    if (amount_money < 0) {
        update = "SELECT BANK_ID FROM ACCOUNTS WHERE ID=" + 
            std::__cxx11::to_string(id);
        rc = sqlite3_exec(db, update.c_str(), bank_id_callback, NULL, NULL);
        update = "SELECT PERCENT_CREDIT FROM BANKS WHERE ID=" +
            std::__cxx11::to_string(bank_id);
        rc = sqlite3_exec(db, update.c_str(), percent_callback, NULL, NULL);
        int subtract = (time(0) - time_) / 2500000 * percent * 1.0 / 12 * 
            abs(amount_money);
        update = "UPDATE ACCOUNTS set MONEY=MONEY-" + 
            std::__cxx11::to_string(subtract) + 
            " WHERE ID=" + std::__cxx11::to_string(id);
        rc = sqlite3_exec(db, update.c_str(), NULL, NULL, NULL);
    }

    update = "UPDATE ACCOUNTS set MONEY=MONEY+" +
                         std::__cxx11::to_string(money) + 
                         " WHERE ID = " +
                         std::__cxx11::to_string(id);
    rc = sqlite3_exec(db, update.c_str(), NULL, NULL, NULL);
    std::cout << "Deposited successfully\n";
    update = "UPDATE ACCOUNTS set DATE=" + std::__cxx11::to_string(time(0)) +
        " WHERE ID=" + std::__cxx11::to_string(id);
    rc = sqlite3_exec(db, update.c_str(), NULL, NULL, NULL);
    return true;
}

int limit_credit;
static int limit_credit_callback(void *data, int argc, char **argv,
        char **azColName) {
    limit_credit = std::__cxx11::stoi(argv[0]);
    return 0;
}

bool Credit::withdraw_money(sqlite3* db, int id, int money) {
    std::string update = "SELECT DATE FROM ACCOUNTS WHERE ID=" +
        std::__cxx11::to_string(id);
    int rc = sqlite3_exec(db, update.c_str(), time_callback, NULL, NULL);
    update = "SELECT MONEY FROM ACCOUNTS WHERE ID=" +
        std::__cxx11::to_string(id);
    rc = sqlite3_exec(db, update.c_str(), get_money_callback, NULL, NULL);
    if (amount_money < 0) {
        update = "SELECT BANK_ID FROM ACCOUNTS WHERE ID=" + 
            std::__cxx11::to_string(id);
        rc = sqlite3_exec(db, update.c_str(), bank_id_callback, NULL, NULL);
        update = "SELECT PERCENT_CREDIT FROM BANKS WHERE ID=" +
            std::__cxx11::to_string(bank_id);
        rc = sqlite3_exec(db, update.c_str(), percent_callback, NULL, NULL);
        int subtract = (time(0) - time_) / 2500000 * percent * 1.0 / 12 * 
            abs(amount_money);
        update = "UPDATE ACCOUNTS set MONEY=MONEY-" + 
            std::__cxx11::to_string(subtract) + 
            " WHERE ID=" + std::__cxx11::to_string(id);
        rc = sqlite3_exec(db, update.c_str(), NULL, NULL, NULL);
    }


    update = "SELECT MONEY FROM ACCOUNTS WHERE ID=" +
                         std::__cxx11::to_string(id);
    rc = sqlite3_exec(db, update.c_str(), get_money_callback, NULL, NULL);
    update = "SELECT BANK_ID FROM ACCOUNTS WHERE ID="+
        std::__cxx11::to_string(id);
    rc = sqlite3_exec(db, update.c_str(), bank_id_callback, NULL, NULL);
    update = "SELECT LIMIT_CREDIT FROM BANKS WHERE ID="+
        std::__cxx11::to_string(bank_id);
    rc = sqlite3_exec(db, update.c_str(), limit_credit_callback, NULL, NULL);
    if (amount_money - money < limit_credit) {
        std::cout << "Insufficient funds\n";
        return false;
    }

    if (check_for_doubtful(db, id, money)) {
        return false;
    }


    update = "UPDATE ACCOUNTS set MONEY=MONEY-" +
                         std::__cxx11::to_string(money) + 
                         " WHERE id = " +
                         std::__cxx11::to_string(id);
    rc = sqlite3_exec(db, update.c_str(), NULL, NULL, NULL);
    std::cout << "Withdrawed successfully\n";
    update = "UPDATE ACCOUNTS set DATE=" + std::__cxx11::to_string(time(0)) +
        " WHERE ID=" + std::__cxx11::to_string(id);
    rc = sqlite3_exec(db, update.c_str(), NULL, NULL, NULL);
    return true;
}

bool Credit::transfer_money(sqlite3* db, int id, int destination_id, 
                            int money) {
    std::string update = "SELECT DATE FROM ACCOUNTS WHERE ID=" +
        std::__cxx11::to_string(id);
    int rc = sqlite3_exec(db, update.c_str(), time_callback, NULL, NULL);
    update = "SELECT MONEY FROM ACCOUNTS WHERE ID=" +
        std::__cxx11::to_string(id);
    rc = sqlite3_exec(db, update.c_str(), get_money_callback, NULL, NULL);
    if (amount_money < 0) {
        update = "SELECT BANK_ID FROM ACCOUNTS WHERE ID=" + 
            std::__cxx11::to_string(id);
        rc = sqlite3_exec(db, update.c_str(), bank_id_callback, NULL, NULL);
        update = "SELECT PERCENT_CREDIT FROM BANKS WHERE ID=" +
            std::__cxx11::to_string(bank_id);
        rc = sqlite3_exec(db, update.c_str(), percent_callback, NULL, NULL);
        int subtract = (time(0) - time_) / 2500000 * percent * 1.0 / 12 * 
            abs(amount_money);
        update = "UPDATE ACCOUNTS set MONEY=MONEY-" + 
            std::__cxx11::to_string(subtract) + 
            " WHERE ID=" + std::__cxx11::to_string(id);
        rc = sqlite3_exec(db, update.c_str(), NULL, NULL, NULL);
    }


    update = "SELECT MONEY FROM ACCOUNTS WHERE ID=" +
                         std::__cxx11::to_string(id);
    rc = sqlite3_exec(db, update.c_str(), get_money_callback, NULL, NULL);
    update = "SELECT BANK_ID FROM ACCOUNTS WHERE ID="+
        std::__cxx11::to_string(id);
    rc = sqlite3_exec(db, update.c_str(), bank_id_callback, NULL, NULL);
    update = "SELECT LIMIT_CREDIT FROM BANKS WHERE ID="+
        std::__cxx11::to_string(bank_id);
    rc = sqlite3_exec(db, update.c_str(), limit_credit_callback, NULL, NULL);
    if (amount_money - money < limit_credit) {
        std::cout << "Insufficient funds\n";
        return false;
    }

    if (check_for_doubtful(db, id, money)) {
        return false;
    }


    update = "UPDATE ACCOUNTS set MONEY=MONEY-" +
                         std::__cxx11::to_string(money) + 
                         " WHERE ID = " +
                         std::__cxx11::to_string(id);
    rc = sqlite3_exec(db, update.c_str(), NULL, NULL, NULL);
    update = "UPDATE ACCOUNTS set MONEY=MONEY+" +
                         std::__cxx11::to_string(money) + 
                         " WHERE ID = " +
                         std::__cxx11::to_string(destination_id);
    rc = sqlite3_exec(db, update.c_str(), NULL, NULL, NULL);
    std::cout << "Transfered successfully\n"; 
    update = "UPDATE ACCOUNTS set DATE=" + std::__cxx11::to_string(time(0)) +
        " WHERE ID=" + std::__cxx11::to_string(id);
    rc = sqlite3_exec(db, update.c_str(), NULL, NULL, NULL);
    return true;
}

void Credit::add_account(sqlite3* db, int id_user, int id_bank) {
    number_of_accounts = 0;
    std::string update = "SELECT * FROM ACCOUNTS";
    int rc = sqlite3_exec(db, update.c_str(), number_callback, NULL, NULL);
    update = "INSERT INTO ACCOUNTS VALUES (" + 
             std::__cxx11::to_string(number_of_accounts + 1) +
             ", 'Credit', " + 
             std::__cxx11::to_string(id_user) + ", " +
             std::__cxx11::to_string(id_bank) + ", 0, 0)";
    rc = sqlite3_exec(db, update.c_str(), NULL, NULL, NULL);
    std::cout << "Added account with ID=" << 
                 std::__cxx11::to_string(number_of_accounts + 1) << '\n';
}

Deposit::Deposit() : Account() { }

bool Deposit::deposit_money(sqlite3* db, int id, int money) {
    std::string update = "SELECT DATE FROM ACCOUNTS WHERE ID=" +
        std::__cxx11::to_string(id);
    int rc = sqlite3_exec(db, update.c_str(), time_callback, NULL, NULL);
    update = "SELECT MONEY FROM ACCOUNTS WHERE ID=" +
        std::__cxx11::to_string(id);
    
    if (time(0) < time_) {
        update = "SELECT BANK_ID FROM ACCOUNTS WHERE ID=" + 
                 std::__cxx11::to_string(id);
        rc = sqlite3_exec(db, update.c_str(), bank_id_callback, NULL, NULL);
        update = "SELECT PERCENT_DEPOSIT FROM BANKS WHERE ID=" +
                 std::__cxx11::to_string(bank_id);
        rc = sqlite3_exec(db, update.c_str(), percent_callback, NULL, NULL);
        int add = (time_ - time(0)) / 2500000 * percent * 1.0 / 12 * 
                  abs(money);
        update = "UPDATE ACCOUNTS set MONEY=MONEY+" + 
                 std::__cxx11::to_string(add) + 
                 " WHERE ID=" + std::__cxx11::to_string(id);
        rc = sqlite3_exec(db, update.c_str(), NULL, NULL, NULL);
    }

    update = "UPDATE ACCOUNTS set MONEY=MONEY+" +
                         std::__cxx11::to_string(money) + 
                         " WHERE ID = " +
                         std::__cxx11::to_string(id);
    rc = sqlite3_exec(db, update.c_str(), NULL, NULL, NULL);
    std::cout << "Deposited successfully\n";
    return true;
}

bool Deposit::withdraw_money(sqlite3* db, int id, int money) {
    std::string update = "SELECT DATE FROM ACCOUNTS WHERE ID=" +
        std::__cxx11::to_string(id);
    int rc = sqlite3_exec(db, update.c_str(), time_callback, NULL, NULL);
    if (time(0) < time_) {
        std::cout << "Deposit time is not over yet\n";
        return false;
    } 
    update = "SELECT MONEY FROM ACCOUNTS WHERE ID=" +
                         std::__cxx11::to_string(id);
    rc = sqlite3_exec(db, update.c_str(), get_money_callback, NULL, NULL);
    if (amount_money < money) {
        std::cout << "Insufficient funds\n";
        return false;
    }
    if (check_for_doubtful(db, id, money)) {
        return false;
    }

    update = "UPDATE ACCOUNTS set MONEY=MONEY-" +
                         std::__cxx11::to_string(money) + 
                         " WHERE ID = " +
                         std::__cxx11::to_string(id);
    rc = sqlite3_exec(db, update.c_str(), NULL, NULL, NULL);
    return true;
}

bool Deposit::transfer_money(sqlite3* db, int id, int destination_id, 
                            int money) {
    std::string update = "SELECT DATE FROM ACCOUNTS WHERE ID=" +
        std::__cxx11::to_string(id);
    int rc = sqlite3_exec(db, update.c_str(), time_callback, NULL, NULL);
    if (time(0) < time_) {
        std::cout << "Deposit time is not over yet\n";
        return false;
    }
    if (check_for_doubtful(db, id, money)) {
        return false;
    }

    update = "UPDATE ACCOUNTS set MONEY=MONEY-" +
                         std::__cxx11::to_string(money) + 
                         " WHERE ID = " +
                         std::__cxx11::to_string(id);
    rc = sqlite3_exec(db, update.c_str(), NULL, NULL, NULL);
    update = "UPDATE ACCOUNTS set MONEY=MONEY+" +
                         std::__cxx11::to_string(money) + 
                         " WHERE ID = " +
                         std::__cxx11::to_string(destination_id);
    rc = sqlite3_exec(db, update.c_str(), NULL, NULL, NULL);
    std::cout << "Transfered successfully\n";
    return true;
}

void Deposit::add_account(sqlite3* db, int id_user, int id_bank) {
    number_of_accounts = 0;
    std::string update = "SELECT * FROM ACCOUNTS";
    int rc = sqlite3_exec(db, update.c_str(), number_callback, NULL, NULL);
    update = "INSERT INTO ACCOUNTS VALUES (" + 
             std::__cxx11::to_string(number_of_accounts + 1) +
             ", 'Deposit', " + 
             std::__cxx11::to_string(id_user) + ", " +
             std::__cxx11::to_string(id_bank) + ", 0, " +
             std::__cxx11::to_string(time(0)) + ")";
    rc = sqlite3_exec(db, update.c_str(), NULL, NULL, NULL);
    std::cout << "Added account with ID=" << 
                 std::__cxx11::to_string(number_of_accounts + 1) << '\n';
}

std::string type;
static int type_callback(void *data, int argc, char **argv, char **azColName) {
    type = argv[0];
    return 0;
}

std::string get_type(sqlite3* db, int id) {
    std::string update = "SELECT TYPE FROM ACCOUNTS WHERE ID=" +
        std::__cxx11::to_string(id);
    int rc = sqlite3_exec(db, update.c_str(), type_callback, NULL, NULL);
    return type;
}

Undo::Undo() : operations_stack_({}) { }

void Undo::undo() {
    if (this->operations_stack_.empty()) {
        std::cout << "No operations to undo\n";
        return;
    }
    auto last = this->operations_stack_.back().first;
    auto db = this->operations_stack_.back().second.first;
    auto args = this->operations_stack_.back().second.second;
    this->operations_stack_.pop_back();
    Debit debit;
    Credit credit;
    Deposit deposit;
    if (last == "deposit") {
        std::string type = get_type(db, args[0]);
        if (type == "Debit") {
            debit.withdraw_money(db, args[0], args[1]);
        }
        if (type == "Credit") {
            credit.withdraw_money(db, args[0], args[1]);
        }
    }
    if (last == "withdraw") {
        std::string type = get_type(db, args[0]);
        if (type == "Debit") {
            debit.deposit_money(db, args[0], args[1]);
        }
        if (type == "Credit") {
            credit.deposit_money(db, args[0], args[1]);
        }
        if (type == "Deposit") {
            deposit.deposit_money(db, args[0], args[1]);
        }
    }
    if (last == "transfer") {
        std::string type = get_type(db, args[1]);
        if (type == "Debit") {
            debit.transfer_money(db, args[1], args[0], args[2]);
        }
        if (type == "Credit") {
            credit.transfer_money(db, args[1], args[0], args[2]);
        }
        if (type == "Deposit") {
            deposit.transfer_money(db, args[1], args[0], args[2]);
        }
    }
}

void Undo::add_operation(const std::string& oper, sqlite3* db, int arg1, int arg2, int arg3) {
    this->operations_stack_.push_back({oper, {db, {arg1, arg2, arg3}}});
}
