#pragma once
#include "Interfaces/IPerson.h"
#include "Interfaces/IAccount.h"
#include "Utilities/InfoStructs.h"
#include "Managers/CourseManager.h"
#include "Managers/StudentManager.h"
#include "Managers/ProfessorManager.h"

class Admin: public IPerson, public IAccount {
private:
std::string username,password; 
PrivateInfo private_info;
public:
Admin();
void LoadAdminPrivateInfo();
void WriteOrUpdateAdminInfo();
void RunAdminPanel(StudentManager* student_manager, CourseManager* course_manager, ProfessorManager* professor_manager);
void ManageStudents(StudentManager* student_manager);
void ManageFaculty(ProfessorManager* professor_manager, CourseManager* course_manager);
void ManageCourses(CourseManager* course_manager);
bool VerifyIdentity(std::string username, std::string password) override;
void ViewProfile() const override;
void EditProfile();
bool Login();
void AddPrivateInfo(
    std::string cnic,
    std::string address,
    std::string personal_email,
    std::string father_name,
    std::string date_of_birth
    ) override;
};