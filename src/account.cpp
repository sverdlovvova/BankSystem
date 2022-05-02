#include "account.h"

Account::Account() {}

void Account::DepositMoney(int id, int money) { }

void Account::WithdrawMoney(int id, int money) { }

void Account::TransferMoney(int id, int destination_id, int money) { }

Debit::Debit() : Account() { }

void Debit::DepositMoney(int id, int money) { }

void Debit::WithdrawMoney(int id, int money) { }

void Debit::TransferMoney(int id, int destination_id, int money) { }

Credit::Credit() : Account() { }

void Credit::DepositMoney(int id, int money) { }

void Credit::WithdrawMoney(int id, int money) { }

void Credit::TransferMoney(int id, int destination_id, int money) { }

Deposit::Deposit() : Account() { }

void Deposit::DepositMoney(int id, int money) { }

void Deposit::WithdrawMoney(int id, int money) { }

void Deposit::TransferMoney(int id, int destination_id, int money) { }

