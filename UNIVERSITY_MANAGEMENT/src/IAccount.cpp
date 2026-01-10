#include "Interfaces/IAccount.h"

IAccount::IAccount(): user_name_("NULL"), password_("NULL") {}

IAccount::IAccount(std::string user_name, std::string password): user_name_(user_name), password_(password) {}

std::string IAccount::user_name() const {
    return user_name_;
}

std::string IAccount::password() const {
    return password_;
}

 IAccount::~IAccount() {

}
