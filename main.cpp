#include "account.h"
#include "customer.h"
#include "bank.h"
#include <ctime>

const char users[] = "CREATE TABLE USERS("
                         "ID        KEY     NOT NULL,"
                         "NAME      TEXT    NOT NULL,"
                         "SURNAME   TEXT    NOT NULL,"
                         "ADDRESS   TEXT,"
                         "PASSPORT  INT);";

const char banks[] = "CREATE TABLE BANKS("
                         "ID               KEY     NOT NULL,"
                         "PERCENT_CREDIT   INT     NOT NULL,"
                         "PERCENT_DEPOSIT  INT     NOT NULL,"
                         "LIMIT_CREDIT     int     NOT NULL,"
                         "LIMIT_DOUBTFUL   int     NOT NULL);";

const char accounts[] = "CREATE TABLE ACCOUNTS("
                          "ID        KEY     NOT NULL,"
                          "TYPE      TEXT    NOT NULL,"
                          "USER_ID   INT     NOT NULL,"
                          "BANK_ID   INT     NOT NULL,"
                          "MONEY     INT     NOT NULL,"
                          "DATE      INT);";/*Last operation time for Credit
                                              and finish time for Deposit*/

sqlite3* db;

void create_db() {
    int rc = sqlite3_open("database.db", &db); 
    rc = sqlite3_exec(db, users, NULL, NULL, NULL);
    rc = sqlite3_exec(db, banks, NULL, NULL, NULL);
    rc = sqlite3_exec(db, accounts, NULL, NULL, NULL);
}

int main() {
    create_db();
    Bank banks;
    Customer customers;
    Debit debit;
    Credit credit;
    Deposit deposit;
    Undo undo;
    while (true) {
        std::string operation;
        getline(std::cin, operation);
        if (operation == "stop") {
            break;
        }
        if (operation == "create bank") {
            int percent_credit;
            int percent_deposit;
            int limit_credit;
            int limit_doubtful;
            std::cout << "Percent for credit:\n";
            std::cin >> percent_credit;
            std::cout << "Percent for deposit:\n";
            std::cin >> percent_deposit;
            std::cout << "Limit for credit:\n";
            std::cin >> limit_credit;
            std::cout << "Limit for doubtful:\n";
            std::cin >> limit_doubtful;
            banks.add_bank(db, percent_credit, percent_deposit, limit_credit,
                    limit_doubtful);
            continue;
        }
        if (operation == "create user") {
            std::string name;
            std::string surname;
            std::cout << "User name:\n";
            std::cin >> name;
            std::cout << "User surname:\n";
            std::cin >> surname;
            customers.add_customer(db, name, surname);
        }
        if (operation == "create account") {
            std::string type;
            int user_id;
            int bank_id;
            std::cout << "User ID:\n";
            std::cin >> user_id;
            std::cout << "Bank ID:\n";
            std::cin >> bank_id;
            std::cout << "Type:\n";
            std::cin >> type;
            if (type == "Debit") {
                debit.add_account(db, user_id, bank_id);
            }
            if (type == "Credit") {
                credit.add_account(db, user_id, bank_id);
            }
            if (type == "Deposit") {
                deposit.add_account(db, user_id, bank_id);
            }
        }
        if (operation == "change user name") {
            std::string new_name;
            int user_id;
            std::cout << "User ID:\n";
            std::cin >> user_id;
            std::cout << "New name:\n";
            std::cin >> new_name;
            customers.set_name(db, user_id, new_name);
        }
        if (operation == "change user surname") {
            std::string new_surname;
            int user_id;
            std::cout << "User ID:\n";
            std::cin >> user_id;
            std::cout << "New surname:\n";
            std::cin >> new_surname;
            customers.set_surname(db, user_id, new_surname);
        }
        if (operation == "change user address") {
            std::string new_address;
            int user_id;
            std::cout << "User ID:\n";
            std::cin >> user_id;
            std::cout << "New address:\n";
            std::cin >> new_address;
            customers.set_address(db, user_id, new_address);
        }
        if (operation == "change user passport") {
            int new_passport;
            int user_id;
            std::cout << "User ID:\n";
            std::cin >> user_id;
            std::cout << "New passport:\n";
            std::cin >> new_passport;
            customers.set_passport(db, user_id, new_passport);
        }
        if (operation == "deposit") {
            int account_id;
            int money;
            std::cout << "Account ID:\n";
            std::cin >> account_id;
            std::cout << "Money to deposit:\n";
            std::cin >> money;
            std::string type = get_type(db, account_id);
            std::cout << type << '\n';
            if (type == "Debit") {
                if (debit.deposit_money(db, account_id, money)) {
                    undo.add_operation("deposit", db, account_id, money);
                }
            }
            if (type == "Credit") {
                if (credit.deposit_money(db, account_id, money)) {
                    undo.add_operation("deposit", db, account_id, money);
                }
            }
            if (type == "Deposit") {
                if (deposit.deposit_money(db, account_id, money)) {
                    undo.add_operation("deposit", db, account_id, money);
                }
            }
        }
        if (operation == "withdraw") {
            int account_id;
            int money;
            std::cout << "Account ID:\n";
            std::cin >> account_id;
            std::cout << "Money to withdraw:\n";
            std::cin >> money;
            std::string type = get_type(db, account_id);
            if (type == "Debit") {
                if (debit.withdraw_money(db, account_id, money)) {
                    undo.add_operation("withdraw", db, account_id, money);
                }
            }
            if (type == "Credit") {
                if (credit.withdraw_money(db, account_id, money)) {
                    undo.add_operation("withdraw", db, account_id, money);
                }
            }
            if (type == "Deposit") {
                if (deposit.withdraw_money(db, account_id, money)) {
                    undo.add_operation("withdraw", db, account_id, money);
                }
            }
        }
        if (operation == "transfer") {
            int account_id;
            int destination_id;
            int money;
            std::cout << "Account ID:\n";
            std::cin >> account_id;
            std::cout << "Destination account ID:\n";
            std::cin >> destination_id;
            std::cout << "Money to transfer:\n";
            std::cin >> money;
            std::string type = get_type(db, account_id);
            if (type == "Debit") {
                if (debit.transfer_money(db, account_id, destination_id, money)) {
                    undo.add_operation("transfer", db, account_id, destination_id,  money);
                }
            }
            if (type == "Credit") {
                if (credit.transfer_money(db, account_id, destination_id, money)) {
                    undo.add_operation("transfer", db, account_id, destination_id, money);
                }
            }
            if (type == "Deposit") {
                if (deposit.transfer_money(db, account_id, destination_id, money)) {
                    undo.add_operation("transfer", db, account_id, destination_id, money);
                }
            }
        }
        if (operation == "undo") {
            undo.undo();
        }
    }
}
