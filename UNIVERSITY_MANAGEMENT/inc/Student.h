#pragma once

#include "Interfaces/IPerson.h"
#include "Interfaces/IAccount.h"
#include "Interfaces/IPersistance.h"

class Student: public Person, public Account {
private:
std::string roll_number_;
std::string department_;
std::string program_;

};
