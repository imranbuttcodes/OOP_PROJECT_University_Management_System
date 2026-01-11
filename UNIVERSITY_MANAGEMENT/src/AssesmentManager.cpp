#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include "Managers/AssesmentManager.h"
#include "InfoStructs.h"
using std::ofstream;
using std::ifstream;
using std::cout;
using std::endl;
using std::string;

Assesment* AssesmentManager::CreateAssesment(string course_code, string assesment_name, string assesment_ID,string assesment_type, double total_marks) {
    Assesment* ass = new Assesment;
    ass->assesment_name_ = assesment_name; 
    ass->assesment_ID_ = assesment_ID;
    ass->assesment_type_ = assesment_type; 
    ass->total_marks_ = total_marks;
    assesment_.emplace_back(course_code,ass);//std::vector<std::pair<string,Assesment*>> assesment_;//course-code,Assesment
    ofstream out_file("data/assesments_records.txt",std::ios::app);
    out_file << course_code <<"|"<<assesment_ID<<"|"<<assesment_type<<"|" <<assesment_name<<"|" << "|NULL|" <<total_marks <<"|" << 0 <<"|" <<0<<"|" <<0 <<"|" <<endl;
    out_file.close();
    return ass;
}

void AssesmentManager::UpdateMarksAndFile(Assesment* assesment) {
    bool found = false;
    if(assesment != nullptr) {
    for(auto& ass: assesment_) {
        if(ass.second->assesment_ID_ == assesment->assesment_ID_) {
            found = true;
            if(ass.second != assesment){
                delete ass.second;
                ass.second = assesment;
            }
            break;
        }
    }
}
    if(!found) {
        cout <<"Assesment ID not found!" << endl;
        return;
    }

    ofstream out_file("data/assesments_records.txt");
    if(!out_file) {
        cout <<"Error: Failed to open data/assesment file!"<<endl;
        return;
    }
    for(const auto& ass: assesment_) {
        Assesment* current_assesment = ass.second;
        for(auto student_entry: current_assesment->marks_) {
            out_file << ass.first << "|" << ass.second->assesment_ID_ << "|" << ass.second->assesment_type_ << "|"
            <<ass.second->assesment_name_ << "|"<<student_entry.first<<"|"<<current_assesment->total_marks_<<"|" <<student_entry.second.first <<"|"<<current_assesment->class_average_ << "|" << student_entry.second.second<<endl;;
        }        
      }
      //file format for assesment_record.txt would be... 
      //coures_code|assesment_ID|assesment_type|assesment_name|student_role_number|total_marks|obtained_marks|classAverage|percentage
      out_file.close();
//   std::map<std::string, std::pair<double, double>> marks_;//student_roll_number, obtained_marks, percentage //this will be for all the students

}

Assesment* AssesmentManager::get_assesment(string assesment_id, string course_code) {
  for(auto ass: assesment_) {
        if(ass.second->assesment_ID_ == assesment_id && ass.first == course_code) {
            return ass.second;
        }
    }
    return nullptr;
}

bool AssesmentManager::IsAssesmentIdExist(string course_code, string assesment_Id) {
    for(auto assesment: assesment_) {
        if(assesment.first == course_code && assesment.second->assesment_ID_ == assesment_Id) {
            return true;
        }
    }
    return false;
}
void AssesmentManager::ViewStudentAttendance(std::string course_code, std::string student_roll_number, bool single_student) {
//
}
bool AssesmentManager::MarkStudent(string course_code, string assesment_id, string roll_number, double obtained_marks) {
    Assesment* target_assesment = get_assesment(assesment_id, course_code);
    if(target_assesment ==      nullptr) {
        return false;
    }
    target_assesment->AddOrUpdateMarks(roll_number,obtained_marks);
    UpdateMarksAndFile(target_assesment);
    return true;
}


bool AssesmentManager::LoadAssesmentsDataFromFile() {
    ifstream assesment_record("data/assesments_records.txt");
    if(!assesment_record) {
        return false;
    }
    //coures_code|assesment_ID|assesment_type|assesment_name|student_role_number|total_marks|obtained_marks|classAverage|percentage
    string line, file_roll_number,file_ass_Id, file_ass_type, file_ass_name;
    string  file_str_obtained_marks, file_str_average, file_str_percentage, file_str_total_marks;
    while(getline(assesment_record,line)) {
        std::stringstream ss(line);
        string course_code;
        getline(ss,course_code,'|');
        getline(ss, file_ass_Id,'|');
        getline(ss, file_ass_type,'|');
        getline(ss, file_ass_name,'|');
        getline(ss,file_roll_number,'|');
        getline(ss,file_str_total_marks,'|');
        getline(ss,file_str_obtained_marks,'|');
        getline(ss,file_str_average,'|');
        getline(ss,file_str_percentage, '|');
        
        Assesment* new_assesment = nullptr;

        for(auto ass: assesment_) {
            if(ass.second->assesment_ID_ == file_ass_Id && ass.first == course_code) {
                new_assesment = ass.second;
                break;
            }
        }
        if(new_assesment == nullptr) {
            new_assesment = new Assesment;
            new_assesment->assesment_ID_ = file_ass_Id;
            new_assesment->assesment_name_ = file_ass_name;
            new_assesment->assesment_type_ = file_ass_type;
            new_assesment->total_marks_ = stod(file_str_total_marks);
            assesment_.push_back({course_code,new_assesment});
        }
        if(file_roll_number != "NULL") {
        new_assesment->AddOrUpdateMarks(file_roll_number, stod(file_str_obtained_marks));
        }
    }
    
    

assesment_record.close();
   return true; 
}


bool AssesmentManager::ViewStudentAssesment(string course_code, string student_roll_number, string assesment_id)  {
    //student can only use this function inside not other edit functions
    LoadAssesmentsDataFromFile();
    Assesment* target_assesment = nullptr;
    for (const auto& ass: assesment_) {
        if (ass.second->assesment_ID_ == assesment_id && ass.first == course_code) {
            target_assesment = ass.second;
            break;
        }
        
    }
    if (target_assesment == nullptr) {
            return false;
        }
    auto it = target_assesment->marks_.find(student_roll_number);
    if (it != target_assesment->marks_.end()) {
            cout <<string(20,'-') <<" Student Grade Book "<<string(20,'-') <<"\n\n";
             cout << std::left <<std::setw(20) <<"Roll Number" 
             << std::setw(15) << "Assesment Type"
             << std::setw(20) << "Assesment Name "
             <<std::setw(20) << "Assesment ID" 
             <<std::setw(15) << "Total Marks" 
             <<std::setw(15) << "Obtained Marks" 
             <<std::setw(15) << "percentage %" 
             <<std::setw(15) << "Class Average" <<endl<<endl; 
             cout << string(60,'-');
             cout <<endl;
             cout << std::left <<std::setw(20) << it->first 
             << std::setw(15) <<target_assesment->assesment_type_  
             << std::setw(20) << target_assesment->assesment_name_  
             << std::setw(20) << target_assesment->assesment_ID_ 
             <<std::setw(15) << target_assesment->total_marks_  
             <<std::setw(15) << it->second.first  
             <<std::setw(15) << it->second.second 
             <<std::setw(15) << target_assesment->class_average_ << endl;
    } else {
        cout << "Student not found in assesment " << assesment_id << endl;
        return false;
    }
                    
    
    return true;
}