#include "bank.h"
#include <set>

class Administrator {
public:
    std::set<Bank> banks;
    
    void addBank(int id, int limitForDoubtful) {
        banks.insert(Bank(id, limitForDoubtful);
    }
    
    void deleteBank(int id) {
        for (auto bank : Banks) {
            if (bank.id == id) {
                Banks.erase(bank);
                break;
            }
        }
    }
};
