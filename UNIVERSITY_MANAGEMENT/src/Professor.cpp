#include <algorithm>
#include <string>
#include "inc/Professor.h"
#include "Course.h"
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
    
    string course_code,assesment_name, assesment_ID,assesment_type;
    double total_marks;
    while(true) {
        cout << "Enter Course-code: ";
        getline(std::cin,course_code);
        if(!IsCourseExist(course_code)) {
            cout <<"Course not found!" << endl;
            continue;
        }
        cout << "Enter assesment Name: ";
        getline(std::cin,assesment_name);
        cout << "Enter Assesment ID: ";
        getline(std::cin,assesment_ID);
        if (assesment_manager->IsAssesmentIdExist(course_code, assesment_ID)) {
            cout << "Assesment ID already exist create a new one!"<< endl;
            continue;
        }
        cout << "Enter assesment Type: " << endl;
        getline(std::cin, assesment_type);
        cout << "Enter Total Marks: ";
        std::cin >> total_marks; 
        if(total_marks < 0 ) {
            std::cout << "Please enter positice digits only" << endl; 
            continue;
        }
        break;
    }
    assesment_manager->CreateAssesment(course_code,assesment_name,assesment_ID,assesment_type,total_marks);
    cout << "Assesment Created Succesfully!" << endl;
    
    
}

void Professor::ConductClassAttendance(AttendanceManager* attendance_manager) {
    bool exit = false;
    string course_code, date;
    while(true){
        cout << "Enter course_code: " ;
        getline(std::cin, course_code);
            if(!IsCourseExist(course_code)) {
                cout <<"Error: Course " << course_code << " not found!" << endl;
                continue;
            }
            string choice;
            while(true) {
                cout << "continue/exit [1/0]: ";
                getline(std::cin,choice);
                if(choice != "0" && choice != "1") {
                    cout << "Invalid Choice!";
                    continue;
                }
                if (choice == "0") {
                    exit = true;
                    break;
                } else{
                    exit = false;
                    break;
                }
            }
            if(exit) {
                break;
            }
            cout << "Enter Date[dd-mm-yyyy]: ";
            getline(std::cin,date);
            break;
      }

 
    cout << "------------------ Mark Attendance ------------------\n\n";
    
    Course* course = GetCourse(course_code);
    if(course == nullptr) {
        cout << "Error: Course not exist or other issue!" << endl;
        return;
    }
    string attendance_status;
    for (auto& student_roll_number: course->student_enrolled_ids()) {
        while(true){
            cout << "Student Roll Number: " << student_roll_number << endl;
            cout << "Mark attendance [P/A]: ";
            getline(std::cin,attendance_status);
            if((attendance_status == "P" || attendance_status == "A")) {
                attendance_manager->MarkAttendance(course_code, student_roll_number, date, attendance_status);
                break;
            } else {
                cout << "Invalid Input Entered!"<< endl;
            }
        }
        
    }
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