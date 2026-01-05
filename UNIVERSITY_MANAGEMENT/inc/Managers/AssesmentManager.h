#pragma once 
#include "Professor.h"
#include "Utilities/InfoStructs.h"
#include "Interfaces/IStudentPortalReadOnly.h"

class AssesmentManager: public IStudentPortalReadOnly{
private:
std::vector<std::pair<string,Assesment*>> assesment_;//course-code,Assesment
public:
Assesment* get_assesment(string assesment_id);
Assesment* CreateAssesment(string course_code, std::string assesment_name, string assesment_ID,string assesment_type, double total_marks);
void UpdateMarksAndFile(Assesment* assesment);
bool MarkStudent(string assesment_id, string roll_number, double obtained_marks);

void ViewGrade(std::string student_roll_number, std::string assesment_id) override;//student can only use this function
void LoadAssesmentsDataFromFile();
};
