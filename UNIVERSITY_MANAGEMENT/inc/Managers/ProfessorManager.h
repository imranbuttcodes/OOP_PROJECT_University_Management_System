#pragma once
#include <iostream>
#include <vector>
class Professor;
class ProfessorManager {
private:
std::vector<Professor*> professors_;
public:
void AddProfessor(Professor* professor);
bool isProfessorExist(std::string professor_id);
void LoadProfessors(); // it will load and populate the professor's 
Professor* GetProfessor(std::string professor_id);
std::string GenerateProfessorId();
void RemoveProfessor(std::string professor_id);
~ProfessorManager();
};