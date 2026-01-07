#include "Course.h"

using std::cout;
using std::endl;
using std::string;

Course::Course(std::string course_code, std::string course_title, std::string room, float course_credit_hours = 0.0f) {
    course_code_ = course_code;
    course_title_ = course_title;
    course_credit_hours_ = course_credit_hours;
    professor_teaching_id_ = "NULL";
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

void Course::AssignProfessor(std::string professor_id) {
    professor_teaching_id_ = professor_id;
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

bool Course::IsStudentExist(string student_roll_number) const {
    for(const auto& students_roll: students_enrolled_id_) {
        if(students_roll == student_roll_number) {
            return true;
        }
    }
    return false;
}



