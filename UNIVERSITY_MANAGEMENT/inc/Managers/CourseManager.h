#pragma once
class Course;
#include<iostream>
#include<vector>
class CourseManager {
private:
std::vector<Course*> courses_;

public:
void AddCourse(Course* course);
void RemoveCourse(std::string course_code);
void ViewCourse(std::string course_code, bool single);
void ViewAllCourses();
bool IsCourseExist(std::string course_code);
void LoadCourseDataFromFile();
void WriteOrUpdateCourse();
void UpdateCourse(Course* course);
Course* GetCourse(string course_code);
~CourseManager();
};