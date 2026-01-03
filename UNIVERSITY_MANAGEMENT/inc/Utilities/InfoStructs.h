#include <iostream>

struct PrivateInfo
{
    std::string cnic_;
    std::string address_;
    std::string personal_email_;
    std::string father_name_;
    std::string age_;
    std::string gender_;
};

struct CourseInfo {
int attentance_count_ = 0;
double quiz_marks_;
double assignment_marks_;
double mid_marks_;
double finals_marks_;
double quiz_marks_average_;
double assignment_marks_average_;
double mid_marks_average_;
double finals_marks_average_;
};
