#pragma once
#include <iostream>
class Person {
protected:
std::string name_;
std::string email_;
std::string phone_number_;
public:
Person();
Person(std::string name, std::string email, std::string phone_number);

void set_name(std::string name);
void set_phone_number(std::string phone_number);
void set_email(std::string email);

std::string name() const;
std::string email() const; 
std::string phone_number() const;

virtual void ViewProfile() const = 0;

virtual ~Person();
};