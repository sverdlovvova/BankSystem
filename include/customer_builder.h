#include "customer.h"

class Builder {
private:
    Customer* customer;
public:
    void reset() {
        this->customer = new Customer()
    }

    void addName(std::string newName) {
        this->customer.name = newName;
    }
    
    void addSurname(std::string newSurname) {
        this->customer.surmane = newSurname;
    }
    
    void addAddress(std::string newAddress) {
        this->customer.address = newAddress;
    }

    Customer* getResult() {
        Customer* result = this->product;
        reset();
        return result;
    }

    ~Builder() {
        delete customer;
    }
};

class Director {
private:
    Builder* builder;
public:
    void setBuilder(Builder* builder) {
        this->builder = builder;   
    }

    void BuildFullCustomer(std::string name,
                           std::string surname,
                           std::string address,
                           int passport) {
        this->builder->addName(name);
        this->builder->addSurname(surname);
        this->builder->addAddress(address);
        this->builder->addPassport(pasport);
    }

    void BuildCustomerWithoutAddress(std::string name,
                                     std::string surname,
                                     int passport) {
        this->builder->addName(name);
        this->builder->addSurname(surname);
        this->builder->addPassport(pasport);
    }
        
    void BuildCustomerWithoutPassport(std::string name,
                                      std::string surname,
                                      std::string address) {
        this->builder->addName(name);
        this->builder->addSurname(surname);
        this->builder->addAddress(address);
    }
};
