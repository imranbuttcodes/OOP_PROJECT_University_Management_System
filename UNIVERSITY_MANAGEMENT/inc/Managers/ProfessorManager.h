#pragma once
#include <iostream>
#include <vector>
class Professor;
class ProfessorManager {
private:
std::vector<Professor*> professors_;
public:
void AddProfessor(Professor* professor);
void AssignCourseToProfessor(std::string professor_id, std::string course_code);
Professor* LoginProfessor();
bool IsProfessorExist(std::string professor_id);
void LoadProfessors(); // it will load and populate the professor's 
void WriteOrUpdateProfessor();
void ViewProfessor(std::string professor_id);
void ViewAllProfessors();
Professor* GetProfessor(std::string professor_id);
std::string GenerateProfessorId();
std::string GenerateProfessorEmail(std::string professor_id);
void RemoveProfessor(std::string professor_id);
~ProfessorManager();
};