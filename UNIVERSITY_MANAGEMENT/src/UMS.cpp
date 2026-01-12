#include "UMS.h"
#include "Utilities/InputValidator.h"
#include <iostream>

void UMS::Start() {
    assesment_manager_.LoadAssesmentsDataFromFile();
    student_manager_.LoadStudentsFromFile();
    professor_manager_.LoadProfessors();
    course_manager_.LoadCourseDataFromFile();
    attendance_manager_.LoadAttendanceRecordFromFile();
    while (true) {
    system("cls");
    std::cout <<" \t\t " << std::string(75,'=') << std::endl;
    std::cout << "\t\t|           Welcom to digital UMS(University Management System)             |\n";
    std::cout  <<" \t\t " << std::string(75,'=') << std::endl;
    //std::cout << std::endl; 
    std::cout << "\t\t|                                                                     \t    |" << std::endl;
    std::cout << "\t\t|                         SELECT YOUR ROLE                            \t    |" << std::endl;
    std::cout << "\t\t|                                                                     \t    |" << std::endl;
    std::cout << "\t\t|                     [1] Administrator                               \t    |" << std::endl;
    std::cout << "\t\t|                     [2] Faculty Member                              \t    |" << std::endl;
    std::cout << "\t\t|                     [3] Student                                     \t    |" << std::endl;
    std::cout << "\t\t|                     [0] Exit                                        \t    |" << std::endl;
    std::cout << "\t\t|                                                                     \t    |" << std::endl;
        std::cout  <<" \t\t" << std::string(75,'=') << std::endl;
        std::string choice = InputValidator::GetValidInput<std::string>("Enter Your Choice: ");
        if (std::cin.peek() == '\n')        std::cin.ignore();

        if (choice == "1") {
            if (admin.Login()) {
                    student_manager_.LoadStudentsFromFile();
                    professor_manager_.LoadProfessors();
                    course_manager_.LoadCourseDataFromFile();
                admin.RunAdminPanel(&student_manager_,&course_manager_, &professor_manager_);
                student_manager_.WriteOrUpdateStudents();
                professor_manager_.WriteOrUpdateProfessor();
                course_manager_.WriteOrUpdateCourse();
                std::cout <<"Press any key to continue....\n";
                std::cin.ignore();
            } else {
            cout << "Invalid username or password!" << endl;
            std::cout <<"Press any key to continue....\n";
                std::cin.ignore();
            }
        } else if (choice == "2") {
            Professor* professor = professor_manager_.LoginProfessor();
            if (professor != nullptr) {
                //  student_manager_.LoadStudentsFromFile();
                //     professor_manager_.LoadProfessors();
                //     course_manager_.LoadCourseDataFromFile();
                //     attendance_manager_.LoadAttendanceRecordFromFile();
                //     assesment_manager_.LoadAssesmentsDataFromFile();
                professor->RunProfessorPanel(&attendance_manager_,&assesment_manager_,&course_manager_,&student_manager_,&professor_manager_);
                 student_manager_.WriteOrUpdateStudents();
                 attendance_manager_.SaveOrUpdateAttendanceRecord();
                 //assesment_manager_.UpdateMarksAndFile();
                 course_manager_.WriteOrUpdateCourse();
                 professor_manager_.WriteOrUpdateProfessor();
            }
            std::cout <<"Press any key to continue....\n";
            std::cin.ignore();
        } else if (choice == "3") {
            Student* student = student_manager_.LoginStudent();
            if(student != nullptr) {
                // attendance_manager_.LoadAttendanceRecordFromFile();
                // student_manager_.LoadStudentsFromFile();
                // assesment_manager_.LoadAssesmentsDataFromFile();
                student->RunStudentPanel(&assesment_manager_, &attendance_manager_, &student_manager_);
                attendance_manager_.SaveOrUpdateAttendanceRecord();
                attendance_manager_.SaveOrUpdateAttendanceRecord();
            }
            std::cout <<"Press any key to continue....\n";
            std::cin.ignore();
        } else if (choice == "0") {
            cout <<"Exiting UMS..........\n\n";
            std::cout <<"Press any key to continue....\n";
            std::cin.ignore();
            break;
        } else {
            std::cout << "Invalid Input!" << std::endl;
            std::cout <<"Press any key to continue....\n";
            std::cin.ignore();
        }
    }
    
}