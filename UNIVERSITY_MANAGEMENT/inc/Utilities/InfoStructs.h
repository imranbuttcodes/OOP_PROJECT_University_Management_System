#include <iostream>
#include<vector>
#include <map>
struct PrivateInfo
{
    std::string cnic_;
    std::string address_;
    std::string personal_email_;
    std::string father_name_;
    std::string date_of_birth_;
};


struct Assesment {
   std::string assesment_name_;
   std::string assesment_type_; // like (cp1,quiz3...)
   std::string assesment_ID_;
   
   std::map<std::string, std::pair<double, double>> marks_;//student_roll_number, obtained_marks, percentage //this will be of that student
   double total_marks_= 0;
   double sum = 0.0;
   double class_average_;
   void AddOrUpdateMarks(std::string student_roll_number, double obtained_marks) {
    if(total_marks_ == 0) {
        cout <<"Error: total_marks for the assesment haven't set please set it" << endl;
        return;
    }
    if(marks_.count(student_roll_number)) {
        sum -= marks_[student_roll_number].first;
    }
    marks_[student_roll_number] = {obtained_marks,(obtained_marks/total_marks_) * 100};

    sum += obtained_marks;
    class_average_ = calculateAverage();
   }

    double calculateAverage() {
        return sum == 0? 0.0: sum/marks_.size();
    }
};

struct StudentPerformance {
int attentance_count_ = 0;
int total_attantance = 0;
double attentance_percentage = (attentance_count_ / total_attantance) * 100;
//total,obtained
// std::pair<double,double> quiz_marks_; 
// std::pair<double,double> assignment_marks_;
// std::pair<double,double> mid_marks_;
// std::pair<double,double> finals_marks_;
};

