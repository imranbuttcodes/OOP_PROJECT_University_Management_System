#pragma once
#include "Interfaces/IPerson.h"
#include "Interfaces/IAccount.h"
#include "Interfaces/IPersistance.h"

class Admin: public IPerson, public IAccount {
private:


public:

void ViewProfile() const override;

void AddPrivateInfo(
    std::string cnic,
    std::string address,
    std::string personal_email,
    std::string father_name,
    std::string date_of_birth
    ) override;

};