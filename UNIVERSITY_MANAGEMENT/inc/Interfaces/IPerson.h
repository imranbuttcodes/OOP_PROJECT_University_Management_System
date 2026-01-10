#pragma once
#include <iostream>
class IPerson {
protected:
std::string name_;
std::string gender_;
int age_;
public:
IPerson();
IPerson(std::string name, std::string gender, int age);

void set_name(std::string name);
void set_gender(std::string gender);
void set_age(int age);

std::string name() const;
std::string gender() const; 
int age() const;

virtual void ViewProfile() const = 0;
virtual void AddPrivateInfo(
    std::string cnic,
    std::string address,
    std::string personal_email,
    std::string father_name,
    std::string date_of_birth
    ) = 0;
virtual ~IPerson();
};