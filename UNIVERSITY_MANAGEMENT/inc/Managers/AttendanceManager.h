#pragma once
#include <iostream>
#include <vector>
#include "Interfaces/IStudentPortalReadOnly.h"

struct AttendenceRecord {
std::string course_id_;
std::string student_id_;
std::string date_;
std::string status_;//A or P
};
struct AttendenceStatus {
int total_clases_ = 0;
int status_present_ = 0;
int status_absents_ = 0;
double status_percentage = 0.0;
};

//file format 
//course_code|roll_number|date|Satus
class AttendanceManager: public IStudentPortalReadOnly {
private:
std::vector<AttendenceRecord> attendance_records_;
public:
void MarkAttendance(std::string course_code, std::string student_roll_number, std::string date, std::string attendance_status);
bool LoadAttendanceRecordFromFile();
bool SaveOrUpdateAttendanceRecord();
bool IsStudentExist(std::string course_code, std::string student_roll_number) const;
AttendenceRecord* GetStudentRecord(std::string course_code, std::string student_roll_number);
void ViewStudentAttendance(std::string course_code, std::string student_roll_number, bool single_student) override;
void ViewAllStudentsAttendanceReport(std::string course_code);//to print the attandace of all students of a specific record
void ViewAttandanceSummery(std::string course_code, std::string student_roll_number, bool single);
void ViewAllAttandanceSummery(std::string course_code);
AttendenceStatus* GetAttendanceStatus(std::string course_code, std::string student_roll_number); 
};