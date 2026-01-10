#pragma once
#include <iostream>
class  IAccount {
protected:
const std::string user_name_;
std::string password_;

public:
IAccount();
IAccount(std::string user_name, std::string password);
std::string password() const;
virtual bool VerifyIdentity(std::string username = "NULL", std::string password = "NULL") = 0;
std::string user_name() const;

virtual ~IAccount() {}
};
