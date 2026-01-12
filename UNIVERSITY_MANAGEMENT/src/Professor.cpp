#include <algorithm>
#include <cctype>
#include <string>
#include <iomanip>
#include "Professor.h"
#include "Course.h"
#include "Utilities/InputValidator.h"
#include "Managers/AssesmentManager.h"
#include "Managers/AttendanceManager.h"
#include "Managers/StudentManager.h"
#include "Managers/CourseManager.h"
#include "Managers/ProfessorManager.h"

using std::cout;
using std::endl;
using std::string;


Professor::Professor(string name, string gender,
     int age, string role, std::string employee_email_id, string employee_id, string password):
     IPerson(name,gender,age), //member initializer list
     IAccount(employee_id, password), employee_ID_ (employee_id), role_(role), employee_email_id_(employee_email_id) {}

void Professor::AddCourse(Course* course) {
    courses_teaching_.push_back(course);
}

std::string Professor::professor_id() const {
return employee_ID_;
}

std::string Professor::professor_email_id() const {
return employee_email_id_;
}

std::string Professor::role() const {
    return role_;
}

PrivateInfo Professor::GetPrivateInfo() const {
    return professor_private_info_;
}

std::vector<Course*> Professor::getAllCourse() {
    return courses_teaching_;
}


Course* Professor::GetCourse(string course_code) {

    if(!IsCourseExist(course_code)) {
        cout <<"Error: Course " << course_code << " not found!" << endl;
        return nullptr;
    }
    for(auto& course: courses_teaching_) {
        if(course->course_code() == course_code) {
            return course;
        }
    }
    return nullptr;
}


void Professor::GradeStudent(AssesmentManager* assesment_manager) {
    cout << "-------------------------- Giving Students Marks --------------------------\n";
    string course_code, assesment_id;
    string choice;
    double obtainedMarks;
    while(true) {
    cout << "Enter course_code: ";
    getline(std::cin,course_code);
    if(!IsCourseExist(course_code)) {
        cout << "Cours Not found!" << endl;
        continue;
    }        
    cout << "Enter Assesment ID: ";
    getline(std::cin, assesment_id);
    if(!assesment_manager->IsAssesmentIdExist(course_code,assesment_id)) {
        cout <<"Invalid Assesment Id or assesment Id not exist!" << endl;
        bool IsCountinue;
        while(true){
        cout << "continue/exit [1/0]: ";
        getline(std::cin, choice);
        if (choice != "0" && choice != "1") {
            cout << "Invalid Choice!" << endl;
            continue;
        }
        if (choice == "1") {
            IsCountinue = true;
            break;
        } else {
            IsCountinue = false;
            break;
        }
        }
        if(!IsCountinue) {
            break;
        }
        continue;
    }
    break;
    }

    Course* course = GetCourse(course_code);
    for(auto& student_id: course->student_enrolled_ids()) {
        while(true){
        cout << "Student Roll Number: " << student_id <<endl;
        cout << "Enter obtained Makrs: ";
        std::cin >> obtainedMarks;
        if(std::cin.peek() == '\n')     std::cin.ignore();
        if(obtainedMarks < 0.0) {
            cout << "Please enter only positive marks!";
            continue;
        }
        if(obtainedMarks > assesment_manager->get_assesment(assesment_id,course_code)->total_marks_) {
            cout << "Obtained Marks can't be greater then total marks!" << endl;
            continue;
        }
            assesment_manager->MarkStudent(course_code,assesment_id,student_id,obtainedMarks);
            cout << "Marks has given successfully!" << endl;
            break;
        }

    }
    cout << "Grading Completed successfully!" << endl;

}
//Assesment* CreateAssesment(string course_code, string assesment_name, string assesment_ID,string assesment_type, double total_marks);

bool Professor::IsCourseExist(string course_code) {
  //  cout << "IsCourse Exist!" << endl;
   if (courses_teaching_.empty())   return false;
    for(auto course: courses_teaching_) {
        if(course->course_code() == course_code) {
            
            return true;
        }
    }
    return false;
}

void Professor::ProfessorCreateAssesment(AssesmentManager* assesment_manager) {
    
    string course_code, assesment_name, assesment_id, assesment_type;
            double total_marks;
            bool should_continue = true;
              while (true) {
                cout << "Enter course_code: ";
                getline(std::cin,course_code);
                
                if(!IsCourseExist(course_code)) {

                    cout <<"Course not found!" << endl;
                    if (InputValidator::IsCountinue()) {
                        continue;;
                    }
                    should_continue = false;
                    break;
                }
                break;
            }
                            //cout << "HI in createAssesment in professor!"<< endl;

            if (should_continue) {
            cout << "Enter assesment Name: " ;
            getline(std::cin,assesment_name);
            while (true) {
                cout << "Enter Unique Assesment ID: ";
                getline(std::cin,assesment_id);
                if(assesment_manager->IsAssesmentIdExist(course_code,assesment_id)) {
                    cout << "Assesment ID "<< assesment_id << " Already exist! for course " << course_code << endl;
                    continue;
                }
                break;
            }
            cout << "Enter assesment type: ";
            getline(std::cin,assesment_type);
            total_marks = InputValidator::GetValidInput<double>("Enter total Marks: ");
            if (std::cin.peek() == '\n')     std::cin.ignore();
            assesment_manager->CreateAssesment(course_code,assesment_name,assesment_id,assesment_type,total_marks);
            cout << "Assesment Created!" << endl;
        }
    
}

void Professor::ConductClassAttendance(AttendanceManager* attendance_manager) {
    string course_code;
            string date;
            while (true) {
                cout << "Enter course_code: ";
                getline(std::cin,course_code); 
                //cout << "Conduct Attendance right!" << endl;
                if(!IsCourseExist(course_code)) {
                    cout <<"Course not found!" << endl;
                    if(InputValidator::IsCountinue()) {
                        continue;
                    }
                    break;
                }
                //cout << "In else block!" << endl;
                date = InputValidator::InputDate();
                break;
            }
           // cout << "Still rigt!" << endl;
            Course* target_course_for_attendance = GetCourse(course_code);
            //cout << "Still right!" << endl;
            if (target_course_for_attendance != nullptr) {
                cout << "\n============================================================\n";
                cout << "   MARKING ATTENDANCE: " << course_code << " | DATE: " << date << "\n";
                cout << "============================================================\n";
                cout << "Instructions: Enter 'P' for Present, 'A' for Absent.\n\n";
                for (auto& student: target_course_for_attendance->student_enrolled_ids()) {
                    while (true) {
                        string attendance_status;
                        cout << "Roll Number: " << student << endl;
                        cout << "Mark attendance [A/P]: ";
                        getline(std::cin,attendance_status);
                        if (attendance_status != "A" && attendance_status != "a" && attendance_status != "p" && attendance_status != "P" ) {
                            cout <<"Invalid input enter only A or P!" << endl;
                            continue;
                        } else if (attendance_status == "p" || attendance_status == "P" ) {
                            attendance_manager->MarkAttendance(course_code,student,date, "P");
                            break;
                        } else if(attendance_status == "a" || attendance_status == "A") {
                            attendance_manager->MarkAttendance(course_code,student,date, "A");
                            break;
                        }
                        
                    }
                }
            } else {
                cout << "Error: Course " << course_code << " not found!" << endl;
            }
            cout << "Attendance Marked Successfully!" << endl;
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
    if(courses_teaching_.empty()) {
        cout << "No courses assigned yet!" << endl;
        return;
    }
    cout <<" "<< string(100,'=') <<" "<< endl;
    cout <<"|       \t\t\t\tCourse Details\t\t\t\t                     |"<<endl;
    cout <<" "<< string(100,'=') <<" "<< endl;
    cout << std::left << std::setw(15) << "Course Code"
    << std::setw(25) << "Course Title"
    << std::setw(15) << "Credit Hourse" 
    << std::setw(20) << "Enrolled Students"
    << std::setw(15) <<"Assigned Room"
    << std::setw(15) <<"Instructor" 
    << endl
    << string(100,'=') << endl;

    for(auto course: courses_teaching_) {
     course->PrintCourse(false);
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


std::ostream& operator<<(std::ostream& out, const Professor& other) {
    other.ViewProfile();
    return out;
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
    cout << "Personal Email: " << professor_private_info_.personal_email_ << endl;
    
}

bool Professor::VerifyIdentity(std::string username, std::string password)
{
    cout << "Enter user_name: ";
    getline(std::cin,username);
    cout <<"Enter Password: ";
    getline(std::cin,password);
    return user_name_ == username && password_ == password;
} 


void Professor::AddPrivateInfo (
    std::string cnic,
    std::string address,
    std::string personal_email,
    std::string father_name,
    std::string date_of_birth
    ) {
        professor_private_info_.address_ = address;
        professor_private_info_.cnic_ = cnic;
        professor_private_info_.personal_email_ = personal_email;
        professor_private_info_.father_name_ = father_name;
        professor_private_info_.date_of_birth_ = date_of_birth;
    }


    
void Professor::RunProfessorPanel(AttendanceManager* attendane_manager, AssesmentManager* assesment_manager, CourseManager* course_manager, StudentManager* student_manager, ProfessorManager* professor_manager) {
 while(true) {
        string choice;
        cout << "\n================ FACULTY DASHBOARD ================\n";
        cout << "1. View My Profile\n";
        cout << "2. Edit My Profile\n";
        cout << "3. View My Courses\n";
        cout << "4. Conduct Attendance (Mark Class)\n";
        cout << "5. View Class Attendance History\n";
        cout << "6. Create Assessment (Quiz/Assignment)\n";
        cout << "7. Grade Students\n";
        cout << "0. Logout\n";
        cout << "===================================================\n";
        cout << "Enter your choice: ";
        getline(std::cin,choice);
        
        if (choice == "1") {
            ViewProfile();
            cout << endl;
        } else if (choice == "2") {
            EditProfessorProfile();
            professor_manager->WriteOrUpdateProfessor();
        } 
        else if (choice == "3") {
            ViewCourses();
        } else if (choice == "4") {
            ConductClassAttendance(attendane_manager);
        } else if (choice == "5") {
            string course_code;
            bool IsView = true;
              while (true) {
                cout << "Enter course_code: ";
                getline(std::cin,course_code);
                if(!IsCourseExist(course_code)) {
                    cout <<"Course not found!" << endl;
                    if(InputValidator::IsCountinue()) {
                        continue;
                    }
                    IsView = false;
                    break;
                }
                break;
            }
            if(IsView) {
            attendane_manager->ViewAllStudentsAttendanceReport(course_code);
            }
        } else if (choice == "6") {
            ProfessorCreateAssesment(assesment_manager);
        } else if (choice == "7") {
            GradeStudent(assesment_manager);
        } else if (choice == "0") {
            cout << "Logging out......" << endl;
            cout <<"press any key to continue";
            std::cin.ignore();
            break;
        } else {
            cout << "Invalid Choice!" << endl;
            cout <<"press any key to continue";
            std::cin.ignore();
            
        }
 
    }
}



void Professor::EditProfessorProfile() {
      while(true) { 
    cout << "\n================ UPDATE PROFILE MENU ================\n";
        cout << "1.  Name          (" << name_ << ")\n";
        cout << "2.  Gender        (" << gender_ << ")\n";
        cout << "3.  Age           (" << age_ << ")\n";
        cout << "4.  CNIC          (" << professor_private_info_.cnic_ << ")\n";
        cout << "5.  Father Name   (" << professor_private_info_.father_name_ << ")\n";
        cout << "6.  Date of Birth (" << professor_private_info_.date_of_birth_ << ")\n";
        cout << "7.  Address       (" << professor_private_info_.address_ << ")\n";
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
        //if(std::cin.peek() == '\n')     std::cin.ignore();
        professor_private_info_.cnic_ = InputValidator::InputCNIC();
    } else if (choice == "5") {
       // if(std::cin.peek() == '\n')     std::cin.ignore();
        professor_private_info_.father_name_ = InputValidator::InputFatherName();

    } else if (choice == "6") {
        //if(std::cin.peek() == '\n')     std::cin.ignore();
        professor_private_info_.date_of_birth_ = InputValidator::InputDOB();
    } else if (choice == "7") {
        //if(std::cin.peek() == '\n')     std::cin.ignore();
        professor_private_info_.address_ = InputValidator::InputAddress();
    } else if (choice == "8") {
        //if(std::cin.peek() == '\n')     std::cin.ignore();
        cout << "Verify your Identity before changing password!"<<endl;
        if(!VerifyIdentity("","")) {
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
        professor_private_info_.personal_email_ = InputValidator::InputEmail();
    }
    else if (choice == "0") {
        cout << "Saving changes...";

        
        break;
    } else {
        cout << "Invalid Choice !" << endl;
    }
}
}