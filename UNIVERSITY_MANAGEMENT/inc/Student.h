#pragma once

#include "Interfaces/IPerson.h"
#include "Interfaces/IAccount.h"
#include "Interfaces/IPersistance.h"
#include "Utilities/InfoStructs.h"

class Course;

class Student: public Person, public Account {
private:
const std::string roll_number_;
std::string department_;
std::string program_;
PrivateInfo student_private_info_;
Course* enrolled_courses_;
std::string request_status_;

public:

Student(std::string roll_number,
std::string department,
std::string program);

void set_roll_number(std::string roll_number);
void set_department(std::string department);
void set_pogram(std::string program);


void set_student_private_info(PrivateInfo privateInfo);

std::string roll_number() const;
std::string department() const;
std::string program() const;

void ViewProfile() const override;
bool VerifyIdentity() override;
void EnrollCourse(Course* course);
void RequestCourseWithdraw() const;

void AddPrivateInfo(
    std::string cnic,
    std::string address,
    std::string personal_email,
    std::string father_name,
    std::string date_of_birth
    ) override;
};