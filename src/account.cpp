#include "account.h"
#include <sqlite3.h>

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
    std::cout << "Deposited successfully\n";
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

void Debit::withdraw_money(sqlite3* db, int id, int money) {
    std::string update = "SELECT MONEY FROM ACCOUNTS WHERE ID=" +
                         std::__cxx11::to_string(id);
    int rc = sqlite3_exec(db, update.c_str(), get_money_callback, NULL, NULL);
    if (amount_money < money) {
        std::cout << "Insufficient funds\n";
        return;
    }
    if (check_for_doubtful(db, id, money)) {
        return;
    }
    update = "update accounts set money=money-" +
                         std::__cxx11::to_string(money) + 
                         " where id = " +
                         std::__cxx11::to_string(id);
    rc = sqlite3_exec(db, update.c_str(), NULL, NULL, NULL);
    std::cout << "Withdrawed successfully\n";
}

void Debit::transfer_money(sqlite3* db, int id, int destination_id, int money) {
    std::string update = "SELECT MONEY FROM ACCOUNTS WHERE ID=" +
                         std::__cxx11::to_string(id);
    int rc = sqlite3_exec(db, update.c_str(), get_money_callback, NULL, NULL);
    if (amount_money < money) {
        std::cout << "Insufficient funds\n";
        return;
    }

    if (check_for_doubtful(db, id, money)) {
        return;
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
    std::cout << "Added account with ID=" << 
                 std::__cxx11::to_string(number_of_accounts + 1) << '\n';
}

Credit::Credit() : Account() { }

void Credit::deposit_money(sqlite3* db, int id, int money) {
    std::string update = "UPDATE ACCOUNTS set MONEY=MONEY+" +
                         std::__cxx11::to_string(money) + 
                         " WHERE ID = " +
                         std::__cxx11::to_string(id);
    int rc = sqlite3_exec(db, update.c_str(), NULL, NULL, NULL);
    std::cout << "Deposited successfully\n";
}

int limit_credit;
static int limit_credit_callback(void *data, int argc, char **argv,
        char **azColName) {
    limit_credit = std::__cxx11::stoi(argv[0]);
    return 0;
}

void Credit::withdraw_money(sqlite3* db, int id, int money) {
    std::string update = "SELECT MONEY FROM ACCOUNTS WHERE ID=" +
                         std::__cxx11::to_string(id);
    int rc = sqlite3_exec(db, update.c_str(), get_money_callback, NULL, NULL);
    update = "SELECT BANK_ID FROM ACCOUNTS WHERE ID="+
        std::__cxx11::to_string(id);
    rc = sqlite3_exec(db, update.c_str(), bank_id_callback, NULL, NULL);
    update = "SELECT LIMIT_CREDIT FROM BANKS WHERE ID="+
        std::__cxx11::to_string(bank_id);
    rc = sqlite3_exec(db, update.c_str(), limit_credit_callback, NULL, NULL);
    if (amount_money - money < limit_credit) {
        std::cout << "Insufficient funds\n";
        return;
    }

    if (check_for_doubtful(db, id, money)) {
        return;
    }


    update = "update accounts set money=money-" +
                         std::__cxx11::to_string(money) + 
                         " where id = " +
                         std::__cxx11::to_string(id);
    rc = sqlite3_exec(db, update.c_str(), NULL, NULL, NULL);
}

void Credit::transfer_money(sqlite3* db, int id, int destination_id, 
                            int money) {
    std::string update = "SELECT MONEY FROM ACCOUNTS WHERE ID=" +
                         std::__cxx11::to_string(id);
    int rc = sqlite3_exec(db, update.c_str(), get_money_callback, NULL, NULL);
    update = "SELECT BANK_ID FROM ACCOUNTS WHERE ID="+
        std::__cxx11::to_string(id);
    rc = sqlite3_exec(db, update.c_str(), bank_id_callback, NULL, NULL);
    update = "SELECT LIMIT_CREDIT FROM BANKS WHERE ID="+
        std::__cxx11::to_string(bank_id);
    rc = sqlite3_exec(db, update.c_str(), limit_credit_callback, NULL, NULL);
    if (amount_money - money < limit_credit) {
        std::cout << "Insufficient funds\n";
        return;
    }

    if (check_for_doubtful(db, id, money)) {
        return;
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
}

void Credit::add_account(sqlite3* db, int id_user, int id_bank) {
    number_of_accounts = 0;
    std::string update = "SELECT * FROM ACCOUNTS";
    int rc = sqlite3_exec(db, update.c_str(), number_callback, NULL, NULL);
    update = "INSERT INTO ACCOUNTS VALUES (" + 
             std::__cxx11::to_string(number_of_accounts + 1) +
             ", Credit, " + 
             std::__cxx11::to_string(id_user) + ", " +
             std::__cxx11::to_string(id_bank) + ", 0)";
    rc = sqlite3_exec(db, update.c_str(), NULL, NULL, NULL);
    std::cout << "Added account with ID=" << 
                 std::__cxx11::to_string(number_of_accounts + 1) << '\n';
}

Deposit::Deposit() : Account() { }

void Deposit::deposit_money(sqlite3* db, int id, int money) {
    std::string update = "UPDATE ACCOUNTS set MONEY=MONEY+" +
                         std::__cxx11::to_string(money) + 
                         " WHERE ID = " +
                         std::__cxx11::to_string(id);
    int rc = sqlite3_exec(db, update.c_str(), NULL, NULL, NULL);
    std::cout << "Deposited successfully\n";
}

void Deposit::withdraw_money(sqlite3* db, int id, int money) {
    std::string update = "SELECT MONEY FROM ACCOUNTS WHERE ID=" +
                         std::__cxx11::to_string(id);
    int rc = sqlite3_exec(db, update.c_str(), get_money_callback, NULL, NULL);
    if (amount_money < money) {
        std::cout << "Insufficient funds\n";
        return;
    }
    if (check_for_doubtful(db, id, money)) {
        return;
    }

    update = "update accounts set money=money-" +
                         std::__cxx11::to_string(money) + 
                         " where id = " +
                         std::__cxx11::to_string(id);
    rc = sqlite3_exec(db, update.c_str(), NULL, NULL, NULL);
}

void Deposit::transfer_money(sqlite3* db, int id, int destination_id, 
                            int money) {

    if (check_for_doubtful(db, id, money)) {
        return;
    }

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
    std::cout << "Transfered successfully\n";
}

void Deposit::add_account(sqlite3* db, int id_user, int id_bank) {
    number_of_accounts = 0;
    std::string update = "SELECT * FROM ACCOUNTS";
    int rc = sqlite3_exec(db, update.c_str(), number_callback, NULL, NULL);
    update = "INSERT INTO ACCOUNTS VALUES (" + 
             std::__cxx11::to_string(number_of_accounts + 1) +
             ", Deposit, " + 
             std::__cxx11::to_string(id_user) + ", " +
             std::__cxx11::to_string(id_bank) + ", 0)";
    rc = sqlite3_exec(db, update.c_str(), NULL, NULL, NULL);
    std::cout << "Added account with ID=" << 
                 std::__cxx11::to_string(number_of_accounts + 1) << '\n';

}

std::string type;
static int type_callback(void *data, int arc, char **argv, char **azColName) {
    type = argv[0];
    return 0;
}

std::string get_type(sqlite3* db, int id) {
    std::string update = "SELECT TYPE FROM ACCOUNTS WHERE ID=" +
        std::__cxx11::to_string(id);
    int rc = sqlite3_exec(db, update.c_str(), type_callback, NULL, NULL);
    return type;
}

