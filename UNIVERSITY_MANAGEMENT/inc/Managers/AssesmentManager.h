#pragma once 
#include "Professor.h"
#include "Utilities/InfoStructs.h"
#include "Interfaces/IStudentPortalReadOnly.h"

class AssesmentManager: public IStudentPortalReadOnly{
private:
std::vector<std::pair<string,Assesment*>> assesment_;//course-code,Assesment
void ViewStudentAttendance(std::string course_code, std::string student_roll_number, bool single_student) override;
public:
Assesment* get_assesment(string assesment_id, string course_code);
Assesment* CreateAssesment(string course_code, string assesment_name, string assesment_ID,string assesment_type, double total_marks);
void UpdateMarksAndFile(Assesment* assesment);
bool MarkStudent(string course_code, string assesment_id, string roll_number, double obtained_marks);
bool IsAssesmentIdExist(string course_code, string assesment_Id);
bool ViewStudentAssesment(string course_code, string student_roll_number, string assesment_id) override;//student can only use this function
bool LoadAssesmentsDataFromFile();
};
