#pragma once

#include <iostream>
#include <vector>
#include "Utilities/InfoStructs.h"

class Professor;
class Student;
class Course {
private:
std::string course_code_;
std::string title_;
int students_enrolled_;
float course_credit_hours_;
std::vector  <std::pair<Student*, StudentPerformance>> students_;                    
//Professor* professor_assigned_;
std::vector<Assesment*> assesments_;
AssesmentManager* assesment_manager_;
public:
 
Course(std::string course_code, std::string title);

void set_course_code(std::string course_code);
void set_title(std::string title);
void AssignStudent(Student* student);
void AddAssesment(Assesment* assesment);
Assesment* assesments(std::string assesment_type) const;
void set_course_credit_hours_(float course_credit_hours_);

// void set_quiz_marks(double quiz_marks, std::string student_roll_number);
// void set_assignment_marks(double assignment_marks, std::string student_roll_number);
// void set_mid_marks(double mid_marks, std::string student_roll_number);
// void set_final_marks(double quiz_marks, std::string student_roll_number);
//void AssignProfessor(Professor* professor);
std::string course_code() const;
float course_credit_hours() const;
std::string title() const;
int enrolled_students() const;
Student* student(std::string student_roll_number) const;
};
