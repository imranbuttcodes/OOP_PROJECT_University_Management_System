#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>//using this for .find() funtion
#include "Managers/AttendanceManager.h"
using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::ofstream;
using std::stringstream;
bool AttendanceManager::LoadAttendanceRecordFromFile() {
    ifstream read_file("data/attendance.txt");
    if(!read_file)      return false;
    if(!attendance_records_.empty()) {
        attendance_records_.clear();
    }
    std::string line, file_course_code, file_roll_number, file_date, file_status;
    AttendenceRecord temp_record;
    while(getline(read_file,line)) {
        stringstream ss(line);
        getline(ss,file_course_code,'|');
        getline(ss,file_roll_number,'|');
        getline(ss,file_date,'|');
        getline(ss,file_status,'|');
        temp_record.course_id_ = file_course_code;
        temp_record.student_id_ = file_roll_number;
        temp_record.date_ = file_date;
        temp_record.status_ = file_status;
        attendance_records_.push_back(temp_record);
    }
    return true;
}

bool AttendanceManager::SaveOrUpdateAttendanceRecord() {
    ofstream write_file("data/attendance.txt");
    if(!write_file)     return false;
    for(auto record: attendance_records_) {
        write_file << record.course_id_ << "|" << record.student_id_ << "|" << record.date_ << "|" << record.status_ << endl;
    }
    return true;
}

bool AttendanceManager::IsStudentExist(std::string course_code, std::string student_roll_number) const {
    for(auto record: attendance_records_) {
        if(record.course_id_ == course_code && record.student_id_ == student_roll_number) {
            return true;
        } 
    }
    return false;
}

AttendenceRecord* AttendanceManager::GetStudentRecord(std::string course_code, std::string student_roll_number) {
for(auto& record: attendance_records_) {
    if(record.course_id_ == course_code && record.student_id_ == student_roll_number) {
        return &record;
    }
}
return nullptr;
}

void AttendanceManager::ViewStudentAttendance(std::string course_code, std::string student_roll_number, bool single_student) 
 {
    if (!IsStudentExist(course_code,student_roll_number)) {
        cout <<"Error: Invalid Course code or student not exist in this course!" << endl;
        return;
    }
    if(single_student) {
        cout << std::left << std::setw(15) << "Course_Code" 
        << std::setw(15) << "Roll Number" 
        << std::setw(15) << "Date" 
        << std::setw(15) << "Status"
        << endl << string(70,'-') <<endl;
    }
    bool found_any = false;
    for (auto student_record: attendance_records_) {
        if(student_record.student_id_ == student_roll_number && student_record.course_id_ == course_code) {
            cout << std::left << std::setw(15) << student_record.course_id_ 
                 << std::setw(20) << student_record.student_id_ 
                 << std::setw(15) << student_record.date_
                 << std::setw(10) << (student_record.status_ == "P" ? "Present" : "Absent")
                 << endl;
            found_any = true;
        }
    }

    if(found_any) {
        ViewAttandanceSummery(course_code,student_roll_number,single_student);
    } else {
        cout <<"No record found for student id "<< student_roll_number << endl;
    }


}

AttendenceStatus* AttendanceManager::GetAttendanceStatus(std::string course_code, std::string student_roll_number) {
    if (!IsStudentExist(course_code, student_roll_number)) {
        cout << "No records found for " << student_roll_number << " in " << course_code << endl;    
        return nullptr;
    }
    AttendenceStatus* attendance_status = new AttendenceStatus;
    bool found = false;
    for(auto record: attendance_records_) {
        if(record.course_id_ == course_code && record.student_id_ == student_roll_number) {
            found = true;
            attendance_status->total_clases_++;
            if(record.status_ == "A") attendance_status->status_absents_++;
            else attendance_status->status_present_++;
        }
    }
    if(attendance_status->total_clases_ > 0){
        attendance_status->status_percentage = ((double)attendance_status->status_present_ / attendance_status->total_clases_) * 100.0;
    } else {
        attendance_status->status_percentage = 0.0;
    }
    return (found ? attendance_status : nullptr );
}


void AttendanceManager::ViewAllStudentsAttendanceReport(string course_code) {
    if(attendance_records_.empty()) {
        cout << "Sorry No Students Attendance Conducted yet";
        return;
    }
     cout << std::left << std::setw(15) << "Course_Code" 
        << std::setw(15) << "Roll Number" 
        << std::setw(15) << "Date" 
        << std::setw(15) << "Status"
        << endl << string(70,'-') <<endl;
    for (auto record: attendance_records_) {
        if (course_code == record.course_id_) {
            ViewStudentAttendance(record.course_id_, record.student_id_,false); 
        }
    }
    
}
bool AttendanceManager::ViewStudentAssesment(std::string course_code, std::string student_roll_number, std::string assesment_id) {
    return true;
}

void AttendanceManager::ViewAttandanceSummery(std::string course_code, std::string student_roll_number, bool single) {
    if(!IsStudentExist(course_code,student_roll_number)) {
        cout << "Error: Student or course_code( " <<course_code<<" )" << "doesn't exist!"<< endl;
        return;
    }

    if(single) {
    cout << string(90,'=') << endl;
    cout << "|           \t\tAttendance Summery          |\n";
    cout  << string(70,'=')  << endl<<endl;
    cout << std::left << std::setw(15) <<"Course Code"
    << std::setw(15) << "Roll Number"
    << std::setw(15) << "Total Classes"
    << std::setw(15) << "Total Presents"
    << std::setw(15) << "Total Absents"
    << std::setw(15) << "Percentage %"
    <<endl << string(90,'=') << endl;
}
    AttendenceStatus* student_status = GetAttendanceStatus(course_code,student_roll_number);
    cout << std::left << std::setw(15) <<course_code
    << std::setw(15) << student_roll_number
    << std::setw(15) << student_status->total_clases_
    << std::setw(15) << student_status->status_percentage
    << std::setw(15) << student_status->status_absents_
    << std::setw(15) << student_status->status_present_
    <<endl << string(90,'=') << endl;
    delete student_status;
}


void AttendanceManager::ViewAllAttandanceSummery(string course_code) {
    std::vector<string> printed_students;
   cout <<" "<< string(90,'=')  << endl;
    cout << "|           \t\t\tAttendance Summery\t\t\t\t           |\n";
    cout <<" "<< string(90,'=') << endl<<endl;
    cout << std::left << std::setw(15) <<"Course Code"
    << std::setw(15) << "Roll Number"
    << std::setw(15) << "Total Classes"
    << std::setw(15) << "Total Presents"
    << std::setw(15) << "Total Absents"
    << std::setw(15) << "Percentage %"
    <<endl << string(90,'=') << endl;
    
    for(auto record: attendance_records_) {
        if(course_code == record.course_id_) {
            auto it = std::find(printed_students.begin(), printed_students.end(), record.student_id_);
            if(it == printed_students.end()){
                ViewAttandanceSummery(course_code,record.student_id_,false);
                printed_students.push_back(record.student_id_);
            }
        }
    }
}

void AttendanceManager::MarkAttendance(std::string course_code, std::string student_roll_number, std::string date, std::string attendance_status) {

AttendenceRecord record;
record.course_id_ = course_code;
record.student_id_ = student_roll_number;
record.date_ = date;
record.status_ = attendance_status;
attendance_records_.push_back(record);
SaveOrUpdateAttendanceRecord();
}



