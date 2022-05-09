#pragma once
#include "customer.h"

class Builder {
private:
    Customer* customer;
public:
    void reset();

    void addName(std::string newName);
    
    void addSurname(std::string newSurname);
    
    void addAddress(std::string newAddress);

    Customer* getResult();

    ~Builder();
};

class Director {
private:
    Builder* builder;
public:
    void setBuilder(Builder* builder);

    void BuildFullCustomer(std::string name,
                           std::string surname,
                           std::string address,
                           int passport);

    void BuildCustomerWithoutAddress(std::string name,
                                     std::string surname,
                                     int passport);
        
    void BuildCustomerWithoutPassport(std::string name,
                                      std::string surname,
                                      std::string address);
};
