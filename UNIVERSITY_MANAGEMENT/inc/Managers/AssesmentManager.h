#pragma once 
#include <string>
#include "Professor.h"
#include "Utilities/InfoStructs.h"
#include "Interfaces/IStudentPortalReadOnly.h"

class AssesmentManager: public IStudentPortalReadOnly{
private:
std::vector<std::pair<std::string,Assesment*>> assesment_;//course-code,Assesment
void ViewStudentAttendance(std::string course_code, std::string student_roll_number, bool single_student) override;
public:
Assesment* get_assesment(std::string assesment_id, std::string course_code);
Assesment* CreateAssesment(std::string course_code, std::string assesment_name, std::string assesment_ID, std::string assesment_type, double total_marks);
void UpdateMarksAndFile(Assesment* assesment);
bool MarkStudent(std::string course_code, std::string assesment_id, std::string roll_number, double obtained_marks);
bool IsAssesmentIdExist(std::string course_code, std::string assesment_Id);
bool ViewStudentAssesment(std::string course_code, std::string student_roll_number, std::string assesment_id) override;//student can only use this function
bool LoadAssesmentsDataFromFile();
};
