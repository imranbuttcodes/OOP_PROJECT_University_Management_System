#include "inc/Professor.h"
#include "Course.h"
using std::cout;
using std::endl;
using std::string;
#include <algorithm>

Professor::Professor(string name, string gender,
     int age, string role, std::string employee_email_id, string employee_id, string pasword):
     Person(name,gender,age), //member initializer list
     Account(employee_id, password_), employee_ID_ (employee_id), role_(role) {}

void Professor::AddCourse(Course* course) {
    courses_teaching_.push_back(course);
}


void Professor::RemoveCourse(string course_code) {
    
    for(int i = 0; i < courses_teaching_.size(); i++) {
        if(courses_teaching_[i]->course_code() == course_code) {
            courses_teaching_.erase(courses_teaching_.begin() + i);
            return;
        }
    }
}


void Professor::ViewCourses() const {
    cout << "Courses teaching...\n\n";
    for(auto course: courses_teaching_) {
        cout << "--------------------------------------------------------------\n\n";
        cout <<"Course Code: " << course->course_code() << endl;
        cout <<"Course Title: " << course->course_code() << endl;
        cout <<"Credit Course: " << course->course_credit_hours() << endl;
        cout <<"Total Students Enroll: " << course->course_credit_hours() << endl;
        cout << "--------------------------------------------------------------\n\n";
    }
}


Course* Professor::course(std::string course_code) {
    for(auto course: courses_teaching_) {
        if(course_code == course->course_code()) {
            return course;
        } 
    }
    return nullptr;
}


void Professor::AddPrivateInfo(
    std::string cnic,
    std::string address,
    std::string personal_email,
    std::string father_name) 
    {
        professor_private_info_.address_ = address;
        professor_private_info_.cnic_ = cnic;
        professor_private_info_.personal_email_ = personal_email;
        professor_private_info_.father_name_ = father_name;
    }


void Professor::ViewProfile() const  {
    cout << "------------------- Faculty Profile ----------------------\n\n";
    cout << "Name: " << name_ <<endl;
    cout << "Age: " << age_ <<endl;
    cout << "Gender: " << gender_ <<endl;
    cout << "Role: " << role_ <<endl;
    cout << "Employee_ID: " << employee_ID_ <<endl;
    cout << "Working E-Mail: " << employee_email_id_ <<endl;
    cout << "----------------------------------------------------------\n\n";
    cout << "-------------------- Personal Info -----------------------\n\n";
    cout << "CNIC: " << professor_private_info_.cnic_ << endl;
    cout << "Address: " << professor_private_info_.address_ << endl;
    cout << "Father Name: " << professor_private_info_.father_name_ << endl;
    cout << "Personal: " << professor_private_info_.personal_email_ << endl;
    
}

bool Professor::VerifyIdentity(std::string user_name, std::string password) {
    return user_name_ == user_name && password_ == password;
}


bool Professor::CreateAssesment(std::string course_code, Assesment& assesment) { //it will fill the assesment struct by asking the assesment things 
    for (auto course: courses_teaching_) {
        if(course->course_code() == course_code) {
            course->AddAssesment(&assesment);
            return true;
        }
    }
    return false;
}

Assesment* Professor::GetAssesmentToUpdate(std::string assesment_type, std::string course_code) {
    for (auto course: courses_teaching_) {
        if(course->course_code() == course_code && course->assesments(assesment_type)->assesment_type_ == assesment_type) {
         return course->assesments(assesment_type);
        }
    }
    return nullptr;
}


void Professor::AssesmentHandler() {
    string choice = 0;
    while (choice != "4") {
        std::cout << "\n--- ASSESSMENT MENU ---\n";
        std::cout << "1. Add New Assessment\n";
        std::cout << "2. Update Marks\n";
        std::cout << "3. Save & Exit\n";
        std::cout << "4. Go Back\n";
        std::cout << "Enter Choice: ";
        std::cin >> choice;
        if (choice == "1") {
            string name, id, type,course_code;
            std::cout << "Enter Assessment ID: "; std::cin >> id;
            
            // DELEGATE logic to the manager
            manager_->createAssessment(id, name, type); 
        }
        else if (choice == 2) {
             // You need to find the assessment first, then pass it to your update function
             // Note: You might need a getter in your manager like manager_->getAssessment(id)
             
             // manager_->UpdateMarksAndFile( ... );
        }
    }
}

