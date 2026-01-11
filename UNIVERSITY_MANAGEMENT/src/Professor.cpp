#include <algorithm>
#include <cctype>
#include <string>
#include "inc/Professor.h"
#include "Course.h"
#include "Utilities/InputValidator.h"
using std::cout;
using std::endl;
using std::string;


Professor::Professor(string name, string gender,
     int age, string role, std::string employee_email_id, string employee_id, string password):
     IPerson(name,gender,age), //member initializer list
     IAccount(employee_id, password), employee_ID_ (employee_id), role_(role) {}

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
        return;
    }
    for(auto& course: courses_teaching_) {
        if(course->course_code() == course_code) {
            return course;
        }
    }
    return nullptr;
}


void Professor::GradeStudent(AssesmentManager* assesment_manager) {
    string course_code, assesment_id;
    string choice;
    double obtainedMarks;
    while(true) {
    cout << "Enter course_code";
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
        cout << "Enter obtained Makrs";
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
              while (true) {
                cout << "Enter course_code";
                getline(std::cin,course_code);
                if(!IsCourseExist(course_code)) {
                    cout <<"Course not found!" << endl;
                    continue;
                }
                break;
            }
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

void Professor::ConductClassAttendance(AttendanceManager* attendance_manager) {
    string course_code;
            string date;
            while (true) {
                cout << "Enter course_code";
                getline(std::cin,course_code);
                if(!IsCourseExist(course_code)) {
                    cout <<"Course not found!" << endl;
                    continue;
                }
                date = InputValidator::InputDate();
                break;
            }

            Course* target_course_for_attendance = GetCourse(course_code);
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
                        } else if(attendance_status == "n" || attendance_status == "N") {
                            attendance_manager->MarkAttendance(course_code,student,date, "N");
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

bool Professor::VerifyIdentity(std::string username = "NULL", std::string password = "NULL")
{
    std::string user_name, password;
    cout << "Enter user_name: " << endl;
    getline(std::cin,user_name);
    cout <<"Enter Password: " << endl;
    getline(std::cin,password);
    return user_name_ == user_name && password_ == password;
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


    
void Professor::RunProfessorPanel(AttendanceManager* attendane_manager, AssesmentManager* assesment_manager, CourseManager* course_manager, StudentManager* student_manager) {
 while(true) {
        string choice;
        cout << "\n================ FACULTY DASHBOARD ================\n";
        cout << "1. View My Profile\n";
        cout << "2. View My Courses\n";
        cout << "3. Conduct Attendance (Mark Class)\n";
        cout << "4. View Class Attendance History\n";
        cout << "5. Create Assessment (Quiz/Assignment)\n";
        cout << "6. Grade Students\n";
        cout << "0. Logout\n";
        cout << "===================================================\n";
        cout << "Enter your choice: ";
        getline(std::cin,choice);
        
        if (choice == "1") {
            ViewProfile();
            cout << endl;
        } else if (choice == "2") {
            ViewCourses();
        } else if (choice == "3") {
            ConductClassAttendance(attendane_manager);
        } else if (choice == "4") {
            string course_code;
              while (true) {
                cout << "Enter course_code";
                getline(std::cin,course_code);
                if(!IsCourseExist(course_code)) {
                    cout <<"Course not found!" << endl;
                    continue;
                }
                break;
            }
            attendane_manager->ViewAllStudentsAttendanceReport(course_code);
        } else if (choice == "5") {
            ProfessorCreateAssesment(assesment_manager);
        } else if (choice == "6") {
            GradeStudent(assesment_manager);
        }
 
    }
}