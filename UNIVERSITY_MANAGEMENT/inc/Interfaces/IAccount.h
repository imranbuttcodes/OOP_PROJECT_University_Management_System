#pragma once
#include <iostream>
class Account {
protected:
std::string user_name_;
std::string password_;

public:
Account();
Account(std::string user_name, std::string password);

virtual bool VerifyIdentity(std::string user_name, std::string password) = 0;
std::string user_name() const {
    return user_name_;
}
virtual ~Account() {}
};
