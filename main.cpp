#include "account.h"
#include "customer.h"
#include "src/customer.cpp"

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
                          "MONEY     INT     NOT NULL);";

sqlite3* db;

void create_db_tables() {
    int rc = sqlite3_open("database.db", &db); 
    rc = sqlite3_exec(db, users, NULL, NULL, NULL); 
    rc = sqlite3_exec(db, banks, NULL, NULL, NULL); 
    rc = sqlite3_exec(db, accounts, NULL, NULL, NULL);
    std::cout << "ok\n";
}

static int print_callback(void *data, int argc, char **argv, char **azColName) {
    for (int i = 0; i < argc; ++i) {
        printf("%s=%s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

bool consist_flag;
static int consist_callback(void *data, int argc, char **argv, char **azColName) {
    consist_flag = true;
    return 0;
}

int main() {
    create_db_tables();
    int rc = sqlite3_open("database.db", &db);
    const char* print = "SELECT * FROM USERS";

    const char* consist = "SELECT * FROM USERS WHERE ID=1";
    rc = sqlite3_exec(db, consist, consist_callback, NULL, NULL);
    if (!consist_flag) {
        const char* insert = 
            "INSERT INTO USERS VALUES (1, 'Ivan', 'Ivanov', 'A', NULL)";
        rc = sqlite3_exec(db, insert, NULL, NULL, NULL);
    }

    Customer customer;
    customer.set_name(db, 1, "Vasya");
    //const char* update = "SELECT * FROM USERS WHERE NAME='Ivan'";
    //rc = sqlite3_exec(db, update, NULL, NULL, NULL);

    customer.add_customer(db, "Petya", "Ivanov");

    rc = sqlite3_exec(db, print, print_callback, NULL, NULL);
    return 0;
}
