#pragma once
//this class would interact with Student and assesmentManager with restricted mode so that student can't access
// the edit marks types function in assesment manager
#include<iostream>
class IStudentPortalReadOnly {
public:
virtual bool ViewStudentAssesment(std::string course_code, std::string student_roll_number, std::string assesment_id) = 0;
virtual void ViewStudentAttendance(std::string course_code, std::string student_roll_number, bool single_student, bool single_student_summery) = 0;
virtual ~IStudentPortalReadOnly() = default;
};