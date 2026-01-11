#pragma once
#include "Admin.h"
#include "Managers/StudentManager.h" 
#include "Managers/CourseManager.h"
#include "Managers/ProfessorManager.h"
#include "Managers/AssesmentManager.h" 
#include "Managers/AttendanceManager.h"
#include "Student.h"
#include "Course.h"
#include "Professor.h"



class UMS{
private:
Admin admin;
CourseManager course_manager_;
StudentManager student_manager_;
ProfessorManager professor_manager_;
AssesmentManager assesment_manager_;
AttendanceManager attendance_manager_;
public:

void Start();

};