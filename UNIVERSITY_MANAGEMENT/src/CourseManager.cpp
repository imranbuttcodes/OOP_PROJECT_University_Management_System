#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iomanip> // for setw or left/rihgt
#include  "Managers/CourseManager.h"

#include "Course.h"
using std::ofstream;
using std::ifstream;
using std::string;
using std::cout;
using std::endl;


bool CourseManager::IsCourseExist(std::string course_code) {
   // LoadCourseDataFromFile();
    for(auto course: courses_) {
        if(course->course_code() == course_code) {
            return true;
        }
    }
    return false;
}


void CourseManager::AddCourse(Course* course) {
    if(IsCourseExist(course->course_code())) {
        cout <<"Course ALready Exist!" << endl;
        return;
    }
    courses_.push_back(course);
    WriteOrUpdateCourse();
    
}

void CourseManager::RemoveCourse(std::string course_code) {
    LoadCourseDataFromFile();
    if(!IsCourseExist(course_code)) {
    cout <<"Error: Course " << course_code << "Not found in database!" << endl;
    return;
    }
    for(auto& course: courses_) {
        if(course->course_code() == course_code) {
            auto it = std::find(courses_.begin(), courses_.end(), course);
            if (it != courses_.end()) {
                courses_.erase(it);
                WriteOrUpdateCourse();
                return;
            }
        }
    }
}


void CourseManager::ViewCourse(std::string course_code, bool single) {
    cout << "Course code passed  in viewCourse(): " << course_code << endl;
    if(!IsCourseExist(course_code)) {
        cout << "Error: Course not found!" << endl;
        return;
    }

    for (auto course: courses_) {
        if(course->course_code() == course_code) {
            course->PrintCourse(single);
            return;
        }
    }
}


bool CourseManager::ViewAllCourses() {
    if(courses_.empty()) {
        cout <<"Error: No courses created yet!" << endl;
        return false;;
    }
    cout <<" "<< string(100,'=') <<" "<< endl;
    cout <<"|       \t\t\t\tCourse Details\t\t\t\t                     |"<<endl;
    cout <<" "<< string(100,'=') <<" "<< endl;
    cout << std::left << std::setw(15) << "Course Code"
    << std::setw(25) << "Course Title"
    << std::setw(15) << "Credit Hourse" 
    << std::setw(20) << "Enrolled Students"
    << std::setw(15) <<"Assigned Room"
    << std::setw(15) <<"Instructor" 
    << endl
    << string(100,'=') << endl;

    for(auto& course: courses_) {
        course->PrintCourse(false);
    }
return true;
} 

Course* CourseManager::GetCourse(string course_code) {
    
    if(!IsCourseExist(course_code)) {
        cout <<"Error: Course Not found!" << endl;
        return nullptr;
    }
    for(auto& course: courses_) {
        if(course->course_code() == course_code) {
            return course;
        }
    }
    return nullptr;
}

void CourseManager::UpdateCourse(Course* course) {
    if(!IsCourseExist(course->course_code())) {
        cout << "Error: Course " << course->course_code() << "Not found to update!" << endl;
        return; 
    } 
    for (auto& course_entry: courses_) {
        if(course_entry->course_code() == course->course_code()) {
            delete course_entry;
            course_entry = course;
            WriteOrUpdateCourse();
            return;
        }
    }
}

void CourseManager::WriteOrUpdateCourse() {
    ofstream write_courses("data/courses.txt");
    if(!write_courses) {
        cout << "Couldn't open courses.txt to write data!" << endl;
        return;
    }
    for(auto& course: courses_) {
        write_courses<<course->course_code()<< "|" << course->course_title() << "|" << course->course_credit_hours()
        <<"|" << course->professor_teaching_id()<<"|" << course->assigned_room_id()<<"|";
        for(std::string student_id: course->student_enrolled_ids()) {
            write_courses << student_id <<",";
        }
        write_courses << endl;
    }

}


void CourseManager::LoadCourseDataFromFile() {
    ifstream read_courses("data/courses.txt");
    //courses.txt format: course_code|course_title|credit_hours|professor_teaching_id|room_assigned_id|student_id1,student_id2,....
    string line;
    if(!read_courses) {
        cout <<"Error: Couldn't open courses.txt or haven't added any course yet!" << endl;
        return;
    }
    if(!courses_.empty()) {
        for(auto& course: courses_) {
            delete course;
        }
        courses_.clear();
    }
    string file_course_code, file_course_title, file_credit_hourse,file_professor_teaching_id, file_room_assinged_id;
    string file_all_student_ids_with_commas;
    string file_single_student_id;
    std::vector<string> file_student_ids;
    while(getline(read_courses,line)) {
            
            std::stringstream ss(line);
            getline(ss,file_course_code,'|');
            getline(ss,file_course_title,'|');
            getline(ss,file_credit_hourse,'|');
            getline(ss,file_professor_teaching_id,'|');
            getline(ss,file_room_assinged_id,'|');
            getline(ss,file_all_student_ids_with_commas,'|');
            std::stringstream ss_new(file_all_student_ids_with_commas);
            Course* temp_course = new Course(file_course_code,file_course_title,file_room_assinged_id,stof(file_credit_hourse));
            temp_course->AssignProfessor(file_professor_teaching_id);
            while(getline(ss_new,file_single_student_id,',')) {
                temp_course->EnrollStudent(file_single_student_id);
            }
            cout << temp_course->course_code() << endl;
            courses_.push_back(temp_course);

        }
        read_courses.close();
}

CourseManager::~CourseManager() {
     if(!courses_.empty()) {
        for(auto& course: courses_) {
            delete course;
        }
        courses_.clear();
    }
}