#pragma once
#include <vector>
#include "Interfaces/IPerson.h"
#include "Interfaces/IAccount.h"
#include "Utilities/InfoStructs.h"
#include "Managers/AssesmentManager.h"
#include "Managers/AttendanceManager.h"
#include "Managers/StudentManager.h"
#include "Managers/CourseManager.h"
class Course;

class Professor: public IPerson, public IAccount{
private:

const std::string employee_ID_;
std::vector<Course*> courses_teaching_;
PrivateInfo professor_private_info_;
std::string role_;
std::string employee_email_id_;
// AssesmentManager* assesment_manager;
//file format:
//employee_id|password|employee_email_id|privateInfo(cinic,address....)|coursesteaching_id1,coursesteaching_id2...
public:
void RunProfessorPanel(AttendanceManager* attendane_manager, AssesmentManager* assesment_manager, CourseManager* course_manager, StudentManager* student_manager);
Professor(std::string name, std::string gender, int age, 
    std::string role, std::string employee_email_id, std::string employee_id, std::string password);
void AddCourse(Course* course);
void ViewCourses() const;
void RemoveCourse(std::string course_code);
void GradeStudent(AssesmentManager* assesment_manager);
void ProfessorCreateAssesment(AssesmentManager* assesment_manager);
Course* course(std::string course_code);
bool IsCourseExist(string course_code);
//Assesment* GetAssesmentToUpdate(std::string assesment_type, std::string course_code); //for assesment work like adding marks/updating marks
//void AssesmentHandler();
void ConductClassAttendance(AttendanceManager* attendance_manager); 
//bool CreateAssesment(std::string course_code, Assesment& assesment); //it will fill the assesment struct with like(total marks, assesment name, assesment type.....)
void ViewProfile() const override;
bool IsCourseExist(std::string cours_code);
bool VerifyIdentity(std::string username = "NULL", std::string password = "NULL") override;
std::string professor_email_id() const;
std::string professor_id() const;
std::string role() const;
PrivateInfo GetPrivateInfo() const;
std::vector<Course*> getAllCourse();
Course* GetCourse(string course_code);
void AddPrivateInfo(
    std::string cnic,
    std::string address,
    std::string personal_email,
    std::string father_name,
    std::string date_of_birth
    ) override;
};