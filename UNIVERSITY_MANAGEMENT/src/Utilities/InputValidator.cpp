#include <cctype>
#include <regex>
#include "Utilities/InputValidator.h"
using std::cout;
using std::string;
using std::endl;
using std::cin;
bool InputValidator::isDigit(std::string var) {
    if(var.empty())     return false;
    int start_idx = 0;
    if (var[0] == '-' || var[0] == '+') {
        if(var.size() == 1) return false;
        start_idx = 1;
    }
    for(int i = start_idx; i < var.size(); i++) {
        if(!isdigit(var[i]))        return false; 
    }
    
    return true;
} 


/*
    std::string cnic_ = "NULL";
    std::string address_ = "NULL";
    std::string personal_email_ = "NULL";
    std::string father_name_ = "NULL";
    std::string date_of_birth_ = "NULL";
*/

void pharseDOB(const string &DOB, int& day,int& month,int& year){
     day = stoi(DOB.substr(0,2));
     month = stoi(DOB.substr(3,2));
     year = stoi(DOB.substr(6,4));
}

bool InputValidator::IsValidDOBFormat(string dob){
        std::regex pattern(R"(^[0-9]{2}-[0-9]{2}-[0-9]{4}$)");
        return std::regex_match(dob,pattern);
}

bool InputValidator::isleapYear(int year){
    return (year% 4 == 0 && year % 100 != 0) ||(year%400 == 0);
}


bool InputValidator::IsValidDOB(string DOB) {
        if(!IsValidDOBFormat(DOB)) {
            return false;
        }   

        int days,month,year;
        pharseDOB(DOB,days,month,year);
        int daysInmonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        if(month <1 || month > 12)   return false;
        if(isleapYear(year)){
        daysInmonth[2] = 29;
    }
    if(days < 1 || days>daysInmonth[month]){
        return false;
    }
    if(year < 1900){
    return false;
}
if(year > 2026) {
    return false;  
}
return true;
}



bool InputValidator::IsValidCNIC(string cnic) {
    std::regex pattern(R"(^[0-9]{5}-[0-9]{7}-[0-9]{1}$)");
    return std::regex_match(cnic,pattern);
}


 std::string InputValidator::InputName() {
    string name;
    cout <<"Enter Name: ";
    getline(cin,name);
    return name;
}

int InputValidator::InputAge() {
    int age;
    while (true) {
        cout <<"Enter age: ";
        if(cin>>age) {
            if(age > 0 && age < 130)  return age;
            cout << "Invalid Age!" << endl;
            continue;
        } else {
            cout << "Invalid Age!" << endl;
            cin.clear();
            cin.ignore(10000,'\n');
        }
    }
}

std::string InputValidator::InputGender() {
    string choice;
    while (true) {
        cout << "[1] Male" << endl;
        cout << "[2] Femail" << endl;
        cout << "[3] Other" << endl;
        cout << "Enter your choice: ";
        getline(cin,choice);
        if (choice == "1")      return "Male";
        if (choice == "2")      return "Female";
        if (choice == "3")      return "Other";
        cout << "Invalid Input!" << endl;
    }
}

bool InputValidator::IsValidEmail(string email) {
    std::regex pattern(R"(^[a-zA-Z0-9][a-zA-Z0-9.]*@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");
    return std::regex_match(email,pattern);
}

 bool InputValidator::IsValidPassword(string password) {
std::regex pattern(R"(^(?=.*[a-z])(?=.*[A-Z])(?=.*[0-9])(?=.*[!@#$%^&*()_=~`{}\[\]:;"'<>,.?/\\|+-])([a-zA-Z0-9!@#$%^&*()_=~`{}\[\]:;"'<>,.?/\\|+-]{8,})$)"); 
   return std::regex_match(password,pattern);

}
string InputValidator::InputEmail() {
     string email;
    while(true) {
        cout <<"Enter Email: ";
        getline(cin,email);
        if(!IsValidEmail(email)) {
            cout << "Invalid Email!"<<endl;
            continue;
        } 
        break;
    }
    return email;
}

string InputValidator::InputCNIC() {
    string cnic;
    while(true) {
        cout <<"Enter CNIC(format: 12345-7891011-2): ";
        getline(cin,cnic);
        if(!IsValidCNIC(cnic)) {
            cout << "Invalid CNIC or format!"<<endl;
            continue;
        } 
        break;
    }
    return cnic;
}

string InputValidator::InputPassword() {
    string password;
    while(true) {
        cout <<"Enter Password: ";
        getline(cin,password);
        if(!IsValidPassword(password)) {
            cout << "Week Password!"<<endl;
            continue;
        } 
        break;
    }
    return password;
}

string InputValidator::InputDate() {
    while (true) {
    string date;
    cout << "Enter date(dd-mm-yyyy): ";
    getline(cin,date);
    if(!IsValidDOB(date)) {
        cout <<"Invalid date or invalid date format!" << endl;
        continue;
    }
    return date;

    }
}

string InputValidator::InputDOB() {
    string DOB;
    while(true) {
        cout <<"Enter Date of Birth(dd-mm-yyyy): ";
        getline(cin,DOB);
        if(!IsValidDOB(DOB)) {
            cout << "Incalid DOB!"<<endl;
            continue;
        } 
        break;
    }
    return DOB;
}

string InputValidator::InputAddress() {
    string address;
    cout <<"Enter address: ";
    getline(cin,address);
    return address;
}

string InputValidator::InputFatherName() {
    string father_name;
    cout <<"Enter father name: ";
    getline(cin,father_name);
    return father_name;
}

PrivateInfo InputValidator::GetPrivateInfo() {
    //string cnic,address,personal_email,father_name,date_of_birth;
    PrivateInfo private_info;
    cout << "------------------------ Filling Private Info ------------------------\n\n";
    private_info.cnic_ = InputCNIC();
    private_info.date_of_birth_ = InputDOB();
    private_info.address_ = InputAddress();
    private_info.father_name_ = InputFatherName();
    private_info.personal_email_ = InputEmail();

    return private_info;

}