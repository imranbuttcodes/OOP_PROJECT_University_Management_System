#include <string>
#include "Student.h"
#include "Course.h"
#include "Managers/CourseManager.h"
#include "Utilities/InputValidator.h"
#include "Managers/StudentManager.h"
#include "Managers/AssesmentManager.h"
#include "Managers/AttendanceManager.h"
#include "Interfaces/IStudentPortalReadOnly.h"

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

void Student::RunStudentPanel(IStudentPortalReadOnly* portal_viewer_assesment,IStudentPortalReadOnly* portal_viewer_attandance ,StudentManager* student_manager) {

while(true) {
        cout << "\n================ STUDENT DASHBOARD ================\n";
        cout << "1. View My Profile\n";
        cout << "2. View Enrolled Courses\n";
        cout << "3. Enroll Course\n";
        cout << "4. Edit Profile\n";
        cout << "5. Check Attendance\n";
        cout << "6. Check Grades / Results\n";
        cout << "0. Logout\n";
        cout << "===================================================\n";
        std::string choice = InputValidator::GetValidInput<std::string>("Enter your choice: ");
        if(std::cin.peek() == '\n') 
            std::cin.ignore();

        if (choice == "1") {
            while (1) {
            string ch;
            cout << "[1] View Basic Info? "<<endl;;
            cout << "[2] View Private Info? "<<endl;;
            cout << "[0] Exit"<<endl;
            cout << "Enter your Choice: ";
            getline(std::cin,ch);
            if (ch == "1") {
            cout << *this << endl;
            } else if (ch == "2") {
                ViewPrivateInfo();
            } else if (ch == "0") {
                cout << "Exiting...\n\n";
                break;
            } 
            else {
                cout << "Invlaid Input!"<<endl;
            }
            }
            
        } 
        else if (choice == "2") {
            cout << "\n--- Enrolled Courses ---\n";
            if(enrolled_courses_id_.empty()) cout << "No courses enrolled.\n";
            else {
                for(const auto& c : enrolled_courses_id_) {
                    cout << "- " << c << endl;
                }
            }
        } else if (choice == "3") {
            
            cout <<"----------------- Available courses -----------------\n\n";
            CourseManager course_manager;
            course_manager.LoadCourseDataFromFile();
            if(!course_manager.ViewAllCourses())    continue;
            std::string course_code;
            bool ShouldEnroll = true;
            while (true)
            {
                cout <<"Enter course-code to enroll in: ";
                getline(std::cin,course_code);
                
                if (IsCourseALreadyEnrolled(course_code)) {
                    cout << "Error: Already Enrolled!";
                    continue;
                }
                if(!course_manager.IsCourseExist(course_code)) {
                    cout << "Invalid Course code entered!" << endl;
                    if(InputValidator::IsCountinue()){   continue;}
                    else {
                        ShouldEnroll = false;
                        break;
                    }
                } 
                
                break;
            }
            if(ShouldEnroll) { 
                EnrollCourse(course_code);
                Course* temp_course = course_manager.GetCourse(course_code);
                temp_course->EnrollStudent(roll_number_);
                course_manager.WriteOrUpdateCourse();
                cout << "Course Added successfully!" << endl; 
                student_manager->WriteOrUpdateStudents();
            }
        }
        else if (choice == "4") {
            EditStudentProfile();
            student_manager->WriteOrUpdateStudents();
        } 
        else if (choice == "5") {
            std::string course_code;
            std::cout << "Enter Course Code: ";
            getline(std::cin, course_code);
            if(!IsCourseALreadyEnrolled(course_code)) {
                cout << "Course not exist!" << endl;
                continue;
            }
            portal_viewer_attandance->ViewStudentAttendance(course_code, roll_number_,true,true);
        } else if (choice == "6") {
            std::string course_code, assesment_id;
            cout << "Enter course-code: ";
            getline(std::cin,course_code);
            cout << "Enter Assesment-ID: ";
            getline(std::cin,assesment_id);
            if(!portal_viewer_assesment->ViewStudentAssesment(course_code,roll_number_,assesment_id)) {
                cout << "Invalid Assesment ID or Course Code or assesment haven't conducted yet!" << endl;
            }
        }
        else if (choice == "0") {
            break;
        } 
        else {
            cout << "Invalid Option.\n";
        }
    }

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
course_count++;
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
    portal->ViewStudentAttendance(course_code,roll_number_,true,true);
    cout << endl;
}

std::vector<std::string> Student::GetStudentEnrolledCourse() {
    return enrolled_courses_id_;
}


void Student::EditStudentProfile() {

     while(true) { 
    cout << "\n================ UPDATE PROFILE MENU ================\n";
        cout << "1.  Name          (" << name_ << ")\n";
        cout << "2.  Gender        (" << gender_ << ")\n";
        cout << "3.  Age           (" << age_ << ")\n";
        cout << "4.  CNIC          (" << student_private_info_.cnic_ << ")\n";
        cout << "5.  Father Name   (" << student_private_info_.father_name_ << ")\n";
        cout << "6.  Date of Birth (" << student_private_info_.date_of_birth_ << ")\n";
        cout << "7.  Address       (" << student_private_info_.address_ << ")\n";
        cout << "8.  Change Password\n";
        cout << "9.  Change Email\n";
        cout << "0.  Back\n";
        cout << "=====================================================\n";
        std::string choice = InputValidator::GetValidInput<std::string>("Select Field to Edit: ");
        if(std::cin.peek() == '\n')     std::cin.ignore();
        if (choice == "0")  break;
        if (choice == "1") {
            name_ = InputValidator::InputName();
                    //if(std::cin.peek() == '\n')     std::cin.ignore();

            cout << "Name changed Successfully!"<<endl;
        } else if (choice == "2") {
        gender_ = InputValidator::InputGender();
                if(std::cin.peek() == '\n')     std::cin.ignore();

    } else if (choice == "3") {
        int age = InputValidator::GetValidInput<int>("Enter your age");
        if (age < 0 || age > 130)    {
            cout <<"Invalid Age!";
            continue;
        } age_ = age;
    } else if (choice == "4") {
        if(std::cin.peek() == '\n')     std::cin.ignore();
        student_private_info_.cnic_ = InputValidator::InputCNIC();
    } else if (choice == "5") {
       // if(std::cin.peek() == '\n')     std::cin.ignore();
        student_private_info_.father_name_ = InputValidator::InputFatherName();

    } else if (choice == "6") {
        //if(std::cin.peek() == '\n')     std::cin.ignore();
        student_private_info_.date_of_birth_ = InputValidator::InputDOB();
    } else if (choice == "7") {
        //if(std::cin.peek() == '\n')     std::cin.ignore();
        student_private_info_.address_ = InputValidator::InputAddress();
    } else if (choice == "8") {
        if(std::cin.peek() == '\n')     std::cin.ignore();
        cout << "Verify your Identity before changing password!"<<endl;
        std::string temp_user_name,temp_password;
        cout << "Enter user_name";
        getline(std::cin,temp_user_name);
        cout << "Enter Password";
        getline(std::cin,temp_password);
        if(!VerifyIdentity(user_name_,password_)) {
            cout << "Invalid username or password!" << endl;
            continue;
        }
        while (true) {
            cout <<"Enter new passowrd!" << endl;
            std::string password = InputValidator::InputPassword();
            if(password == password_) {
                cout << "New password can't be old password!"<<endl;
                continue;
            } 
            password_ = password;
            cout << "Password changed!" << endl;
            break;
        }
        
    } else if (choice == "9") {
        student_private_info_.personal_email_ = InputValidator::InputEmail();
    }
    else if (choice == "0") {
        cout << "Saving changes...";
        
        break;
    } else {
        cout << "Invalid Choice !" << endl;
    }
}

}


std::ostream& operator<<(std::ostream& os, const Student& s) {
s.ViewProfile();
return os;
}

bool Student::operator==(const Student& other) const {
    return roll_number_ == other.roll_number_;
}


Student::Student(const Student& other): roll_number_(other.roll_number_), department_(other.department_) {
    this->student_private_info_ = other.student_private_info_;
    this->enrolled_courses_id_ = other.enrolled_courses_id_;
}

int Student::course_count = 0;