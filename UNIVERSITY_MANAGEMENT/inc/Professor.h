#pragma once
#include <vector>
#include "Interfaces/IPerson.h"
#include "Interfaces/IAccount.h"
#include "Utilities/InfoStructs.h"
#include "Managers/AssesmentManager.h"
class Course;

class Professor: public Person, public Account{
private:

const std::string employee_ID_;
std::vector<Course*> courses_teaching_;
PrivateInfo professor_private_info_;
std::string role_;
std::string employee_email_id_;
// AssesmentManager* assesment_manager;

public:
Professor(std::string name, std::string gender, int age, 
    std::string role, std::string employee_email_id, std::string employee_id, std::string pasword);
void AddCourse(Course* course);
void ViewCourses() const;
void RemoveCourse(std::string course_code);
void GradeStudent(std::string student_roll_number, std::string course_code);

Course* course(std::string course_code);

//Assesment* GetAssesmentToUpdate(std::string assesment_type, std::string course_code); //for assesment work like adding marks/updating marks
//void AssesmentHandler();
void MarkAttendance(std::string student_roll_no, std::string course_code); 

//bool CreateAssesment(std::string course_code, Assesment& assesment); //it will fill the assesment struct with like(total marks, assesment name, assesment type.....)
void ViewProfile() const override;
bool VerifyIdentity() override;
void AddPrivateInfo(
    std::string cnic,
    std::string address,
    std::string personal_email,
    std::string father_name,
    std::string date_of_birth
    ) override;
};