#include <vector>

class Bank {
public:
    int id;
    int limitForDoubtful;
    std::vector<int> customerIds;

    Bank(int newId, int newLimitForDoubtful) {
        id = newId;
        limitForDoubtful = newLimitForDoubtful;
    }
};
