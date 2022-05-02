#include "account.h"
#include "customer.h"
#include "src/customer.cpp"

void create_db_tables() {
    sqlite3* db;
    int rc = sqlite3_open("database.db", &db);
    const char users[] = "CREATE TABLE USERS("
                         "ID        KEY     NOT NULL,"
                         "NAME      TEXT    NOT NULL,"
                         "SURNAME   TEXT    NOT NULL,"
                         "ADDRESS   TEXT    NOT NULL,"
                         "PASSPORT  INT     NOT NULL);";
    rc = sqlite3_exec(db, users, NULL, NULL, NULL);
    const char banks[] = "CREATE TABLE BANKS("
                         "ID               KEY     NOT NULL,"
                         "CREDIT_LIMIT     INT     NOT NULL,"
                         "CREDIR_PERCENT   INT     NOT NULL,"
                         "DEPOSIT_PERCENT  INT     NOT NULL);";
    rc = sqlite3_exec(db, banks, NULL, NULL, NULL);
    const char accounts[] = "CREATE TABLE ACCOUNTS("
                          "ID        KEY     NOT NULL,"
                          "TYPE      TEXT    NOT NULL,"
                          "USER_ID   INT     NOT NULL,"
                          "BANK_ID   INT     NOT NULL);";
    rc = sqlite3_exec(db, accounts, NULL, NULL, NULL);
}

int main() {
    create_db_tables();
    return 0;
}
