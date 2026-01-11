#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include "Managers/ProfessorManager.h"
#include "Professor.h"
#include "Managers/CourseManager.h"
#include "Course.h"
using std::ofstream;
using std::ifstream;
using std::cout;
using std::endl;
using std::string;
void ProfessorManager::AddProfessor(Professor* professor) {
    if (IsProfessorExist(professor->professor_id())) {
        cout << "Error: Professor Already exist!";
        return;
    }
    professors_.push_back(professor);
} 
//employee_id|password|employee_email_id|name|gender|age|role|privateInfo(cinic,address....)|coursesteaching_id1,coursesteaching_id2...

void ProfessorManager::LoadProfessors() {
    ifstream read_file("data/professors.txt");
    if(!read_file) {
        cout <<"Error: File professors.txt not exist!"<<endl;
        return;
    } 
    if(!professors_.empty()) {
        for(auto& professor: professors_) {
            delete professor;
        }
        professors_.clear();
    }
    CourseManager course_manager;
    string line,file_password, file_employee_id, file_name, file_private_info_line, file_gender,file_age,file_role,file_employee_email_id,course_file_line;
    PrivateInfo file_private_info;
    std::vector<string> file_course_teaching_;
    while(getline(read_file,line)) {
        std::stringstream ss(line);
        getline(ss,file_employee_id, '|');
        getline(ss,file_password, '|');
        getline(ss,file_employee_email_id, '|');
        getline(ss,file_name, '|');
        getline(ss,file_gender, '|');
        getline(ss,file_age, '|');
        getline(ss,file_role, '|');
        getline(ss,file_private_info_line,'|');
        getline(ss,file_private_info_line,'|');
        std::stringstream private_info_entry(file_private_info_line);
        getline(private_info_entry,file_private_info.cnic_,',');
        getline(private_info_entry,file_private_info.address_,',');
        getline(private_info_entry,file_private_info.father_name_,',');
        getline(private_info_entry,file_private_info.personal_email_,',');
        getline(private_info_entry,file_private_info.date_of_birth_,'|');

         Professor* temp_professor = new  Professor(file_name,file_gender,stoi(file_age),file_role, file_employee_email_id,file_employee_id, file_password);
        
         temp_professor->AddPrivateInfo(file_private_info.cnic_,file_private_info.address_,file_private_info.personal_email_,file_private_info.father_name_,file_private_info.date_of_birth_);
        getline(ss,course_file_line);
        std::stringstream courses_entry(course_file_line);
        string file_course;
        course_manager.LoadCourseDataFromFile();
        while(getline(courses_entry,file_course,',')) {
            Course* temp_course = new Course(*course_manager.GetCourse(file_course));
                temp_professor->AddCourse(temp_course);
        }
        professors_.push_back(temp_professor);
    }
}


/*
void StudentManager::WriteOrUpdateStudents() {
    ofstream write_file("data/students.txt");
    if(!write_file) {
        cout <<"Error: Couldn't open students.txt file for writing!" << endl;
        return;
    }
    for(auto& student: students_) {
        write_file << student->roll_number() << "|" 
        << student->password() << "|"
        << student->name() << "|"
        << student->age() << "|"
        << student->gender() << "|"
        << student->program() << "|"
        << student->department() << "|"
        << student->GetPrivateInfo().cnic_ << ","
        << student->GetPrivateInfo().address_ << ","
        << student->GetPrivateInfo().father_name_ << ","
        << student->GetPrivateInfo().personal_email_ << ","
        << student->GetPrivateInfo().date_of_birth_ << "|";
        for(string& student_course_id_entry: student->GetStudentEnrolledCourse()) { 
                write_file << student_course_id_entry <<",";

        }
        write_file << endl;

    }
}
*/
//employee_id|password|employee_email_id|name|gender|age|role|privateInfo(cinic,address....)|courses teaching_id1,coursesteaching_id2...

void ProfessorManager::WriteOrUpdateProfessor() {
ofstream write_file("data/professors.txt");
    if(!write_file) {
        cout <<"Error: Couldn't open professors.txt file for writing!" << endl;
        return;
    }
    if(professors_.empty()) {
        write_file.close();
        return;
    }
    for(auto& professor: professors_) {
        write_file << professor->professor_id() << '|'
        << professor->password() << '|'
        << professor->professor_email_id() << '|'
        << professor->name() << '|'
        << professor->gender() << '|'
        << professor->age() << '|'
        << professor->role() << '|'
        << professor->GetPrivateInfo().cnic_ << ","
        << professor->GetPrivateInfo().address_ << ","
        << professor->GetPrivateInfo().father_name_ << ","
        << professor->GetPrivateInfo().personal_email_ << ","
        << professor->GetPrivateInfo().date_of_birth_ << "|";
        for(auto course: professor->getAllCourse()) {
            write_file << course->course_code() << ',';
        }
        write_file << endl;
    }   
    write_file.close();
}

void ProfessorManager::RemoveProfessor(std::string professor_id) {
    LoadProfessors();
    if(!IsProfessorExist(professor_id)) {
        cout << "Error: Profossor Not found!" << endl;
        return;
    } 
    for(auto& professor: professors_) {
        if(professor->professor_id() == professor_id) {
            auto it = std::find(professors_.begin(),professors_.end(),professor);
            if(it != professors_.end()) {
                professors_.erase(it);
                WriteOrUpdateProfessor();
                return;
            }
        }
    }
} 

ProfessorManager::~ProfessorManager() {
 if(!professors_.empty()) {
        for(auto& professor: professors_) {
            delete professor;
        }
        professors_.clear();
    }   
}


string ProfessorManager::GenerateProfessorEmail(std::string professor_id) {
std::stringstream id_stream(professor_id);
string temp_mail;
getline(id_stream,temp_mail,'-');
getline(id_stream,temp_mail);
return "emp-" + temp_mail + "@uni.edu.pk";
}

std::string ProfessorManager::GenerateProfessorId() {
    LoadProfessors();
    if(professors_.empty()) {
        return "emp-1000";
    }
    int max_id = 0;
    string temp_id ;
    for(auto& professor: professors_) {
        std::stringstream professor_id_stream(professor->professor_id());//emp-1000
        getline(professor_id_stream,temp_id,'-');
        getline(professor_id_stream,temp_id,'-');
        if(stoi(temp_id) > max_id) {
            max_id = stoi(temp_id);
        }

    }
    return "emp-" + std::to_string(++max_id);
}
bool ProfessorManager::IsProfessorExist(std::string professor_id) {
    for (auto& professor: professors_) {
        if(professor->professor_id() == professor_id) {
            return true;
        }
    }
    return false;
}
void ProfessorManager::ViewProfessor(std::string professor_id) {
    Professor* temp_professor = GetProfessor(professor_id);
    if(temp_professor != nullptr) {
        temp_professor->ViewProfile();
        cout << string(100,'-') << endl;
    cout << endl;
    }
}

void ProfessorManager::ViewAllProfessors() {
    cout << "------------------------- All Professors List -------------------------\n\n";
    for(auto& professor: professors_) {
        professor->ViewProfile();
        cout << string(75,'-') << endl;
    }
}


Professor* ProfessorManager::GetProfessor(std::string professor_id) {
    if(!IsProfessorExist(professor_id)) {
        cout << "Error: Professor " << professor_id << " not found!" << endl;
        return nullptr;
    }
      for (auto& professor: professors_) {
        if(professor->professor_id() == professor_id) {
            return professor;
        }
    }
    return nullptr;
}

Professor* ProfessorManager::LoginProfessor() {
    string username, password;
    cout << "----------------- Faculty Login Form -----------------" << endl;
    cout << "Enter username: " ;
    getline(std::cin,username);
    cout << "Enter Password: ";
    getline(std::cin,password);
    for (auto& professor: professors_) {
        if (professor->user_name()== username && professor->password() == password ) {
            return professor;
        }
    }
    cout << "Invalid username or password";
    return nullptr;
}



void ProfessorManager::AssignCourseToProfessor(string professor_id, string course_code) {
    LoadProfessors();
    if (!IsProfessorExist(professor_id)) {
        cout << "Professor with id "<< professor_id << " not found" << endl;
        return;
    }
    CourseManager cm;
    cm.LoadCourseDataFromFile();
    if (cm.IsCourseExist(course_code)) {
        cout << "Course not found!" << endl;
        return;
    }
    Course* temp_course = cm.GetCourse(course_code);
    Professor* professor = GetProfessor(professor_id);
    professor->AddCourse(temp_course);
}

