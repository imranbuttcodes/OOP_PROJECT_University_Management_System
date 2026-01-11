#pragma once
#include <iostream>
#include "InfoStructs.h"

class InputValidator {
public:
static bool isDigit(std::string var);
static  PrivateInfo GetPrivateInfo();
static bool isleapYear(int year);
static bool IsValidEmail(string email);
static bool IsValidDOBFormat(string dob);
static bool IsValidDOB(std::string DOB);
static bool IsValidCNIC(std::string cnic);
static bool IsValidPassword(std::string password);


static std::string InputCNIC();
static std::string InputName();
static std::string InputGender();
static int InputAge();
static string InputDate();
static std::string InputPassword();
static std::string InputDOB();
static std::string InputEmail();
static std::string InputAddress();
static std::string InputFatherName();
static bool IsValidPassword(string password);

template <typename T>
static T GetValidInput(std::string prompt) {
        T value;
        while (true) {
            std::cout << prompt;
            if (std::cin >> value) {
                return value;
            } else {
                std::cout << "Invalid input! Please enter a number.\n";
                std::cin.clear();
                std::cin.ignore(10000, '\n');
            }
        }
}
};