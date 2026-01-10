#include <string>
#include "Student.h"
#include "Course.h"
using std::cout;
using std::endl;
Student::Student(std::string name, int age, std::string gender, std::string roll_number, std::string password, 
std::string department,
std::string program): IPerson(name,gender,age), IAccount(roll_number,password), roll_number_(roll_number), department_(department), program_(program) {}

void Student::set_student_private_info(std::string cnic,
    std::string address,
    std::string personal_email,
    std::string father_name,
    std::string date_of_birth) {
    if(address != "NULL") {
        student_private_info_.address_ = address;
    }
    if(cnic != "NULL") {
        student_private_info_.cnic_ = cnic;
    }
    if(personal_email != "NULL") {
        student_private_info_.personal_email_ = personal_email;
    }
    if(father_name != "NULL") {
        student_private_info_.father_name_ = father_name;
    }
    
    if(date_of_birth != "NULL") {
        student_private_info_.date_of_birth_= date_of_birth;
    }
}


std::string Student::roll_number() const {
    return roll_number_;
}

std::string Student::department() const {
    return department_;
}
std::string Student::program() const {
    return program_;
}

void Student::ViewProfile() const {
    cout << "-------------- Student Basic Info --------------\n\n";
    cout << "Name: " << name_ << endl;
    cout << "Roll Number: " << roll_number_ << endl;
    cout << "Program: " << program_ << endl;
    cout << "Department: " << department_ << endl;
    cout << "------------------------------------------------\n";

} 

void Student::ViewPrivateInfo() const {
    cout << "----------------- " << name_ << "'s private info -----------------"<<endl;
    cout << "Cnic: " << student_private_info_.cnic_ << endl;
    cout << "Address: " << student_private_info_.address_ << endl;
    cout << "Father Name: " << student_private_info_.father_name_ << endl;
    cout << "Personal Email: " << student_private_info_.personal_email_ << endl;
}


bool Student::VerifyIdentity(std::string username, std::string password)  {
    return (username == user_name_) && (password == password_ );
}

bool Student::IsCourseALreadyEnrolled(std::string course_code) const {
    for(auto& course_entry: enrolled_courses_id_) {
        if(course_entry == course_code) {
            return true;
        }
    }
    return false;
}
void Student::EnrollCourse(std::string course_code) {
if(IsCourseALreadyEnrolled(course_code)) {
    cout << "Error: Course Alredy Enrolled" << endl;
    return;
}
enrolled_courses_id_.push_back(course_code);
}

PrivateInfo& Student::GetPrivateInfo()  {
return student_private_info_;
}

void Student::AddPrivateInfo(
    std::string cnic,
    std::string address,
    std::string personal_email,
    std::string father_name,
    std::string date_of_birth
    ) 
    {
    student_private_info_.address_ = address;
    student_private_info_.cnic_ = cnic;
    student_private_info_.date_of_birth_ = date_of_birth;
    student_private_info_.father_name_ = father_name;
    student_private_info_.personal_email_ = personal_email;   
    }

void Student::CheckAttendance(IStudentPortalReadOnly* portal, std::string course_code) {
    portal->ViewStudentAttendance(course_code,roll_number_,true);
    cout << endl;
}

std::vector<std::string> Student::GetStudentEnrolledCourse() {
    return enrolled_courses_id_;
}