#include "Interfaces/IPerson.h"

#include <iostream>

IPerson::IPerson(): name_("NULL"), gender_("NULL"), age_(0) {}

IPerson::IPerson(std::string name, std::string gender, int age): name_(name), gender_(gender), age_(age) {}


void IPerson::set_name(std::string name) {
    name_ = name;
}
void IPerson::set_gender(std::string gender) {
    gender_ = gender;
}
void IPerson::set_age(int age) {
    age_ = age;
}

std::string IPerson::name() const {
    return name_;
}
std::string IPerson::gender() const {
    return gender_;
}
int IPerson::age() const {
    return age_;
}

IPerson::~IPerson() {
    //
}
