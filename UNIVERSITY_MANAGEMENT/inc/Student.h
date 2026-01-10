#pragma once

#include "Interfaces/IPerson.h"
#include "Interfaces/IAccount.h"
//#include "Interfaces/IPersistance.h"
#include "Interfaces/IStudentPortalReadOnly.h"
#include "Utilities/InfoStructs.h"

class Course;

class Student: public IPerson, public IAccount {
private:
const std::string roll_number_;
const std::string department_;
const std::string program_;
PrivateInfo student_private_info_;
std::vector<std::string> enrolled_courses_id_;
//std::string request_status_;
//file format roll_number|password|student_name|age|gender|program|department|privateInfo(cnic,address,father_name,personal_email,date_of_birth)|enrolled_course_id1,enrolled_course_id1...
public:
void CheckAttendance(IStudentPortalReadOnly* portal, std::string course_code);
Student(std::string name, int age, std::string gender, std::string roll_number, std::string password, 
std::string department,
std::string program);



void set_student_private_info(std::string cnic = "NULL",
    std::string address = "NULL",
    std::string personal_email = "NULL",
    std::string father_name = "NULL",
    std::string date_of_birth = "NULL");

std::string roll_number() const;
std::string department() const;
std::string program() const;
PrivateInfo& GetPrivateInfo();
std::vector<std::string> GetStudentEnrolledCourse();
void ViewProfile() const override;
void ViewPrivateInfo() const;
bool VerifyIdentity(std::string username = "NULL", std::string password = "NULL") override;
void EnrollCourse(std::string course);
//void RequestCourseWithdraw() const;

bool IsCourseALreadyEnrolled(std::string course_code) const;

void AddPrivateInfo(
    std::string cnic,
    std::string address,
    std::string personal_email,
    std::string father_name,
    std::string date_of_birth
    ) override;
};