#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include "Utilities/Security.h"
#include "Managers/StudentManager.h"
#include "Student.h"
#include "Utilities/InputValidator.h"
using std::ifstream;
using std::ofstream;

void StudentManager::LoadStudentsFromFile() {
    ifstream read_file("data/students.txt");
    if(!read_file) {
        cout << "Error: Couldn't open students.txt for loading data!" ;
        return;
    }
    if(!students_.empty()) {
        for(auto& student: students_) {
            delete student;
        }
        students_.clear();
    }
    
    string line, file_roll_number,file_password, file_student_name,file_age, file_gender, file_program, file_department,private_info_line,course_file_line,file_course;
    PrivateInfo file_private_info;
    //vector<string> file_courses;
    while(getline(read_file,line)) {
        std::stringstream ss(line);
        getline(ss,file_roll_number,'|');
        getline(ss,file_password,'|');
        getline(ss,file_student_name,'|');
        getline(ss,file_age,'|');
        getline(ss,file_gender,'|');
        getline(ss,file_program,'|');
        getline(ss,file_department,'|');
        getline(ss,private_info_line,'|');
        std::stringstream private_info_entry(private_info_line);
        getline(private_info_entry,file_private_info.cnic_,',');
        getline(private_info_entry,file_private_info.address_,',');
        getline(private_info_entry,file_private_info.father_name_,',');
        getline(private_info_entry,file_private_info.personal_email_,',');
        getline(private_info_entry,file_private_info.date_of_birth_,'|');
        Student* temp_student = new  Student(file_student_name,stoi(file_age),file_gender,file_roll_number,file_password,file_department,file_program);
        temp_student->AddPrivateInfo(file_private_info.cnic_,file_private_info.address_,file_private_info.personal_email_,file_private_info.father_name_,file_private_info.date_of_birth_);
        //students_.push_back(temp_student);
        getline(ss,course_file_line);
        std::stringstream courses_entry(course_file_line);
        
        while(getline(courses_entry,file_course,',')) {
            temp_student->EnrollCourse(file_course);
        }
        students_.push_back(temp_student);
        //cnic,address,father_name,personal_email,date_of_birth
    }

read_file.close();
}

//file format roll_number|password|student_name|age|gender|program|department|privateInfo(cnic,address,father_name,personal_email,date_of_birth)|enrolled_course_id1,enrolled_course_id1...

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
    write_file.close();
    
}
bool StudentManager::IsStudentExist(string roll_number) {
    for(auto student: students_) {
        if(student->roll_number() == roll_number) {
            return true;
        }
    }
    return false;
}


void StudentManager::RemoveStudent(string roll_number) {
    if(!IsStudentExist(roll_number)) {
        cout <<"Error: Student not found! "<<endl;
        return;
    }
    LoadStudentsFromFile();
    for (auto student: students_) {
        if(student->roll_number() == roll_number) {
            auto it = std::find(students_.begin(),students_.end(),student);
            if(it != students_.end()) {
                students_.erase(it);
                WriteOrUpdateStudents();
                cout << "Student " << roll_number <<" removed Successfully!" << endl;
                return;
            }
        }
    } 
    


}


void StudentManager::ViewStudentBasicProfile(string roll_number) {
    LoadStudentsFromFile();
    if(!IsStudentExist(roll_number)) {
        cout << "Error Student Not exist!" << endl;
        return;
    }
    for(auto student: students_) {
        if(student->roll_number() == roll_number) {
            student->ViewProfile();
            return;
        }
    }

}

void StudentManager::ViewStudentPrivateProfile(string roll_number) {
    if(!IsStudentExist(roll_number)) {
         cout << "Error Student Not exist!" << endl;
        return;
    }

    for(auto student: students_) {
        if(student->roll_number() == roll_number) {
            student->ViewPrivateInfo();
            return;
        }
    }
    
}

void StudentManager::ViewAllStudentsBasicProfile() {
    if(students_.empty()) {
        cout << "Error: No students exists yet!" << endl;
        return;
    }
    for (auto student: students_) {
        student->ViewProfile();
        cout << endl;
    }

}

void StudentManager::ViewAllStudentsPrivateProfile() {
     if(students_.empty()) {
        cout << "Error: No students exists yet!" << endl;
        return;
    }
    for (auto student: students_) {
        student->ViewPrivateInfo();
        cout << endl;
    }
}

string StudentManager::generateRollNumber(string program,string department) {
    int max_roll_number = 0;
    ifstream read_file("data/students.txt");
    if(!read_file && students_.empty())  {
    return program + "-" + department + "-" + std::to_string(25) + "-" + std::to_string(1000);
    }

    if(!read_file) {
        cout << "Error: couldn't open students.txt for reading in generateRollNumber() method!";
        return "";
    }
    bool found = false;
    string line, file_roll_number,file_program,file_department,garbage;
    while(getline(read_file,line)) {
        std::stringstream ss(line);
        getline(ss,file_roll_number,'|');
        getline(ss,garbage,'|');
        getline(ss,garbage,'|');
        getline(ss,garbage,'|');
        getline(ss,garbage,'|');
        getline(ss,file_program,'|');
        getline(ss,file_department,'|');
        if(file_program == program && file_department == department) { 
            found = true;
            std::stringstream roll_stream(file_roll_number);//e.g BS-CS-25-1000 or BS-ENG-25-1000
            string temp_roll_number;
            getline(roll_stream,temp_roll_number,'-');
            getline(roll_stream,temp_roll_number,'-');
            getline(roll_stream,temp_roll_number,'-');
            getline(roll_stream,temp_roll_number,'-');
            if(stoi(temp_roll_number) > max_roll_number) {
                max_roll_number = stoi(temp_roll_number);
            }
        }
    }
    if(!found) {
        return program + "-" + department + "-" + std::to_string(25) + "-" + std::to_string(1000);
    }
    return program + "-" + department + "-" + std::to_string(25) + "-" + std::to_string(++max_roll_number);

}
bool StudentManager::RegisterStudent() {
    string name,age,gender,program,department;
    cout <<"-------------------- Student Registeration Form --------------------\n";
    cout << "Enter Name: ";
    getline(std::cin,name);
    cout << "Enter Age: ";
    getline(std::cin,age);
    if(!InputValidator::isDigit(age))   return false;
    if (!Security::IsValidAge(stoi(age))) return false;
    cout << "Enter Gender: ";
    getline(std::cin,gender);
    cout <<"Enter Program Name: ";
    getline(std::cin,program);    
    cout << "Enter Department: ";
    getline(std::cin,department);
    
    string default_password = Security::GenerateStrongPassowrd();
    string generated_roll_number = generateRollNumber(program,department);
    Student* temp_student = new Student(name,stoi(age),gender,generated_roll_number,default_password,department,program);
    temp_student->set_student_private_info();
    students_.push_back(temp_student);
    cout << "Student Roll Number: " << generated_roll_number << endl;
    cout << "Generated Defualt Password: " << default_password << endl;
    cout << "Note: this is your defualt system generated password you can change this password in settings" << endl;
    WriteOrUpdateStudents();
    return true;
}


Student* StudentManager::GetStudent(string roll_number) {
    if(!IsStudentExist(roll_number)) {
        cout <<"Student not found!" << endl;
        return nullptr;
    }
    for (auto& student : students_) {
        if(student->roll_number() == roll_number) {
            return student;
        }
    }
    return nullptr;
}

Student* StudentManager::LoginStudent() {
    string username, password;
    cout << "----------------- Student Login Form -----------------" << endl;
    cout << "Enter username: " ;
    getline(std::cin,username);
    cout << "Enter Password: ";
    getline(std::cin,password);
    for (auto& student: students_) {
        if (student->VerifyIdentity(username, password)) {
            return student;
        }
    }
    cout << "Invalid username or password";
    return nullptr;
    
}