#include <iostream>
#include <fstream>
#include "Managers/AssesmentManager.h"

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
    ofstream out_file("data/assesments_basics.txt",std::ios::app);
    out_file << course_code <<"|"<<assesment_ID<<"|"<<assesment_type<<"|" <<assesment_name<<"|"<<total_marks<<endl;
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

    ofstream out_file("data/assesment_record.txt");
    if(!out_file) {
        cout <<"Error: Failed to open data/assesment file!"<<endl;
        return;
    }
    for(const auto& ass: assesment_) {
        Assesment* current_assesment = ass.second;
        for(auto student_entry: current_assesment->marks_) {
            out_file << ass.first << "|" << ass.second->assesment_ID_ << "|" << ass.second->assesment_type_ << "|"
            <<ass.second->assesment_name_ << "|"<<student_entry.first<<"|"<<current_assesment->total_marks_<<"|" <<student_entry.second.first <<"|"<<current_assesment->calculateAverage() << student_entry.second.second<<endl;;
        }        
      }
      //file format would be... 
      //coures_code|assesment_ID|assesment_type|assesment_name|student_role_number|total_marks|obtained_marks|classAverage|percentage
      out_file.close();
//   std::map<std::string, std::pair<double, double>> marks_;//student_roll_number, obtained_marks, percentage //this will be for all the students

}

Assesment* AssesmentManager::get_assesment(std::string assesment_id) {
  for(auto ass: assesment_) {
        if(ass.second->assesment_ID_ == assesment_id) {
            return ass.second;
        }
    }
    return nullptr;
}


bool AssesmentManager::MarkStudent(string assesment_id, string roll_number, double obtained_marks) {
    Assesment* target_assesment = get_assesment(assesment_id);
    if(target_assesment == nullptr) {
        return false;
    }
    target_assesment->AddOrUpdateMarks(roll_number,obtained_marks);
    UpdateMarksAndFile(target_assesment);
    return true;
}


void AssesmentManager::LoadAssesmentsDataFromFile() {
    ifstream read_file("data/assesment_record.txt");
    if(!read_file) {
        cout << "Erro: file assesment_record is not exist!" << endl;
    }
    
}
