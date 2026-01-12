#pragma once

#include <iostream>
#include <vector>
using std::cout;
using std::string;
using std::endl;
using std::vector;

class Student;
class StudentManager {
private:
vector<Student*> students_;
public:
StudentManager() = default;
StudentManager(const StudentManager& other);
void LoadStudentsFromFile();
void WriteOrUpdateStudents();
bool IsStudentExist(string roll_number);
void RemoveStudent(string roll_number);
void ViewStudentBasicProfile(string roll_number);
void ViewStudentPrivateProfile(string roll_number);
void ViewAllStudentsBasicProfile();
void ViewAllStudentsPrivateProfile();
bool RegisterStudent();
string generateRollNumber(string program,string department);
Student* GetStudent(string roll_number);
Student* LoginStudent();
~StudentManager();
};