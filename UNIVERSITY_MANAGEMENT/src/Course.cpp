#include <iomanip>
#include "Course.h"
//#include "Professor.h"
using std::cout;
using std::endl;
using std::string;

Course::Course(std::string course_code, std::string course_title, std::string room, float course_credit_hours) {
    course_code_ = course_code;
    course_title_ = course_title;
    course_credit_hours_ = course_credit_hours;
    professor_id_ = "NULL";
    assigned_room_id_ = room;
}

void Course::set_course_code(std::string course_code) {
    course_code_ = course_code;
}


void Course::set_title(std::string course_title) {
    course_title_ = course_title;
}

void Course::EnrollStudent(std::string student_id) {
    students_enrolled_id_.push_back(student_id);
}

void Course::AssignProfessor(std::string professor_id)
{
    professor_id_ = professor_id;
}

void Course::set_course_credit_hours(float course_credit_hours) {
    course_credit_hours_ = course_credit_hours;
}

void Course::set_assigned_room_id(std::string room_ID) {
    assigned_room_id_ = room_ID;
}


std::string Course::assigned_room_id() const {
    return assigned_room_id_;
}
std::string Course::course_code() const {
    return course_code_;
}

float Course::course_credit_hours() const {
    return course_credit_hours_;
}

std::string Course::course_title() const {
    return course_title_;
}

string Course::professor_teaching_id() const {
    return professor_id_;
}

std::vector<std::string> Course::student_enrolled_ids() const {
    return students_enrolled_id_;
}

bool Course::IsStudentExist(string student_roll_number) const {
    for(const auto& students_roll: students_enrolled_id_) {
        if(students_roll == student_roll_number) {
            return true;
        }
    }
    return false;
}


void Course::PrintCourse(bool single) const {
    if(single) {
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
    }

    cout << std::left << std::setw(15) << course_code_
    << std::setw(25) << course_title_
    << std::setw(15) << course_credit_hours_ 
    << std::setw(20) << students_enrolled_id_.size()
    << std::setw(15) <<assigned_room_id_
    << std::setw(15) << (professor_id_ != "NULL" ? professor_id_: "Not assigned yet")
    << endl
    << string(100,'=') << endl;
    
}

Course::Course(const Course& other) {
    this->course_code_ = other.course_code_;
    this->course_credit_hours_ = other.course_credit_hours_;
    this->course_title_ = other.course_title_;
    this->professor_id_ = other.professor_id_;
    this->students_enrolled_id_ = other.students_enrolled_id_;
}