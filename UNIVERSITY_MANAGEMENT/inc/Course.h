#pragma once

#include <iostream>
#include <vector>
#include "Utilities/InfoStructs.h"

class Professor;
class Course {
private:
std::string course_code_;//primary course-code like CS101

std::string course_title_;
float course_credit_hours_;
std::string professor_id_; 
std::vector<std::string> students_enrolled_id_; // course-code, student_roll_number                    
//std::vector<Assesment*> assesments_; 
std::string assigned_room_id_;
//AssesmentManager assesment_manager_;
public:

Course(std::string course_code, std::string course_title, std::string room, float course_credit_hours = 0.0f);
void set_course_code(std::string course_code);
void set_title(std::string course_title);
void EnrollStudent(std::string student_id);
void AssignProfessor(std::string professor_id);
void set_course_credit_hours(float course_credit_hours);
void set_assigned_room_id(std::string room_ID);


std::string assigned_room_id() const;
std::string course_code() const;
std::vector<std::string> student_enrolled_ids() const;
float course_credit_hours() const;
std::string course_title() const;
bool IsStudentExist(std::string student_roll_number) const;
std::string professor_teaching_id() const;
void PrintCourse(bool single) const;

};
