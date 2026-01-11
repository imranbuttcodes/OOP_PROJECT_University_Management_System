#include "UMS.h"
#include "Utilities/InputValidator.h"
#include <iostream>

void UMS::Start() {
    while (true) {
    system("cls");
    std::cout <<"|" << std::string(95,'=') <<"|" << std::endl;
    std::cout << "           Welcom to digital UMS(University Management System)            \n";
    std::cout <<"|" << std::string(95,'=') <<"|" << std::endl;
    std::cout << std::endl; 
    std::cout << "\t|                                                          |" << std::endl;
    std::cout << "\t|                  SELECT YOUR ROLE                        |" << std::endl;
    std::cout << "\t|                                                          |" << std::endl;
    std::cout << "\t|              [1] Administrator                           |" << std::endl;
    std::cout << "\t|              [2] Faculty Member                          |" << std::endl;
    std::cout << "\t|              [3] Student                                 |" << std::endl;
    std::cout << "\t|              [0] Exit                                    |" << std::endl;
    std::cout << "\t|                                                          |" << std::endl;
    
        std::string choice = InputValidator::GetValidInput<std::string>("Enter Your Choice: ");
        if (std::cin.peek() == '\n')        std::cin.ignore();

        if (choice == "1") {
            if (admin.Login()) {
                admin.RunAdminPanel(&student_manager_,&course_manager_, &professor_manager_);
            }
        } else if (choice == "2") {
            Professor* professor = professor_manager_.LoginProfessor();
            if (professor != nullptr) {
                professor->RunProfessorPanel(&attendance_manager_,&assesment_manager_,&course_manager_,&student_manager_);
            }
        } else if (choice == "3") {
            Student* student = student_manager_.LoginStudent();
            if(student != nullptr) {
                student->RunStudentPanel(&assesment_manager_, &attendance_manager_, &student_manager_);
            }
        } else if (choice == "0") {
            cout <<"Exiting UMS..........\n\n";
            break;
        } else {
            std::cout << "Invalid Input!" << std::endl;
            std::cout <<"Press any key to continue....\n";
            std::cin.ignore();
        }
    }
    
}