
#include <fstream>
#include <string>
#include "Utilities/InputValidator.h"
#include "Utilities/Security.h"
#include "Admin.h"
#include "Professor.h"
#include "Course.h"
#include "Managers/RoomManager.h"
using std::cout;
using std::endl;
using std::string;
using std::cin;
Admin::Admin(): IAccount("Admin123","Admin@123"), IPerson("NULL","NULL",0) {
    // name_ = "NULL";
    // age_ = 0;
    // gender_ = "NULL";
    private_info.address_ = "NULL";
    private_info.cnic_ = "NULL";
    private_info.personal_email_ = "NULL";
    private_info.date_of_birth_ = "NULL";
    private_info.father_name_ = "NULL";
    WriteOrUpdateAdminInfo();
}

void Admin::ViewProfile() const  {
    cout << "-------------  Admin Profile -----------------\n\n";
    if(name_ == "NULL") {
        cout << "You haven't added any info so please complete your profile first "<< endl;
        cout << "Note: You can add your info in Edit Profile settings"<< endl;
        return;
    }
    cout << "Name: " << name_ << endl;
    cout << "Age: " << age() << endl;
    cout << "Gender: " << gender() << endl;
    cout << "CNIC: " << private_info.cnic_ << endl;
    cout << "Date of Birth: " << private_info.date_of_birth_ << endl;
    cout << "Peronal Email: " << private_info.personal_email_ << endl;
    cout << "Father Name: " << private_info.father_name_ << endl;
    cout << "Address: " << private_info.address_ << endl;
    cout << string(70,'-') << endl;

}

bool Admin::Login() {
    cout << "|"  << string(70,'=') << "|" <<endl;
    cout <<"        \t\tAdmin Login Form\t\t        \n";
    cout << "|"  << string(70,'=') << "|" <<endl;
    return VerifyIdentity("",""); 
}


void Admin::WriteOrUpdateAdminInfo() {
    std::ofstream write_file("data/admin.txt");
    if(!write_file) {
        cout << "Coudn't open admin.txt for writing!" << endl;
        return;
    }
    write_file << name_ <<"," << age_ << "," << gender_ << "," << private_info.cnic_ <<","
    << private_info.date_of_birth_ << "," << private_info.father_name_ << "," << private_info.personal_email_ << "," 
    << private_info.address_ << endl; 
    write_file.close();
}
void Admin::LoadAdminPrivateInfo() {
    string username, password, age;
    std::ifstream read_file("data/admin.txt");
    if(!read_file) {
        cout << "Couldn't open adimin.txt or admin haven't added any private Info";
        return;
    }//just name,age,gender,privateInfo()
    getline(read_file,name_,',');
    getline(read_file,age,',');
    age_ = stoi(age);
    getline(read_file,gender_,',');
    getline(read_file,private_info.cnic_,',');
    getline(read_file,private_info.date_of_birth_,',');
    getline(read_file,private_info.father_name_,',');
    getline(read_file,private_info.personal_email_,',');
    getline(read_file,private_info.address_,',');
    read_file.close();

}

void Admin::EditProfile() {
    while(true) { 
    cout << "\n================ UPDATE PROFILE MENU ================\n";
        cout << "1.  Name          (" << name_ << ")\n";
        cout << "2.  Gender        (" << gender_ << ")\n";
        cout << "3.  Age           (" << age_ << ")\n";
        cout << "4.  CNIC          (" << private_info.cnic_ << ")\n";
        cout << "5.  Father Name   (" << private_info.father_name_ << ")\n";
        cout << "6.  Date of Birth (" << private_info.date_of_birth_ << ")\n";
        cout << "7.  Address       (" << private_info.address_ << ")\n";
        cout << "8.  Change Password\n";
        cout << "9.  Change Email\n";
        cout << "0.  Back\n";
        cout << "=====================================================\n";
        string choice = InputValidator::GetValidInput<string>("Select Field to Edit: ");
        if (std::cin.peek() == '\n')        cin.ignore();
        if (choice == "0")  break;
        if (choice == "1") {
            name_ = InputValidator::InputName();
            cout << "Name changed Successfully!"<<endl;
        } else if (choice == "2") {
        gender_ = InputValidator::InputGender();
    } else if (choice == "3") {
        int age = InputValidator::GetValidInput<int>("Enter your age: ");
        if (age < 0 || age > 130)    {
            cout <<"Invalid Age!";
            continue;
        } age_ = age;
    } else if (choice == "4") {
        private_info.cnic_ = InputValidator::InputCNIC();
    } else if (choice == "5") {
        private_info.father_name_ = InputValidator::InputFatherName();
    } else if (choice == "6") {
        private_info.date_of_birth_ = InputValidator::InputDOB();
    } else if (choice == "7") {
        private_info.address_ = InputValidator::InputAddress();
    } else if (choice == "8") {
        if(!VerifyIdentity(user_name_,password_)) {
            cout << "Invalid username or password!" << endl;
            continue;
        }
        while (true) {
            string password = InputValidator::InputPassword();
            if(password == password_) {
                cout << "New password can't be old password!"<<endl;
                continue;
            } 
            password_ = password;
            break;
        }
        
    } else if (choice == "9") {
        private_info.personal_email_ = InputValidator::InputEmail();
    }
    else if (choice == "0") {
        cout << "Saving changes...";
        break;
    } else {
        cout << "Invalid Choice !" << endl;
    }
}

}

bool Admin::VerifyIdentity(std::string username, std::string password) {
    cout << "Enter username: ";
    getline(cin,username);
    cout << "Enter Password: ";
    getline(cin,password);
    return (username == user_name_) && (password == password_ );
}

void Admin::RunAdminPanel(StudentManager* student_manager, CourseManager* course_manager, ProfessorManager* professor_manager) {
    string choice;
    while(true){
    cout << "-------------------- Admin Panel --------------------" << endl;
    cout << "[1] Manage Students" << endl;
    cout << "[2] Manage Professors" << endl;
    cout << "[3] Manage Courses" << endl;
    cout << "[4] View My Profile" << endl;
    cout << "[5] Edit Profile" << endl;
    cout << "[0] Logout" << endl;
    choice = InputValidator::GetValidInput<string>("Enter your Choice: ");
    if(cin.peek() == '\n') cin.ignore();
    //getline(cin,choice);
    if (choice == "1") {
        ManageStudents(student_manager);
    } else if (choice == "2") {
        ManageFaculty(professor_manager,course_manager);
    } else if (choice == "3") {
        ManageCourses(course_manager);
    } else if (choice == "4") {
        ViewProfile();
    } else if (choice == "5") {
        EditProfile();
        WriteOrUpdateAdminInfo();
    } else if (choice == "0") {
        cout << "Logging you out...." << endl;
        break;
    } else {
        cout << "Invalid Input!" << endl;
    }
    }
}


void Admin::ManageStudents(StudentManager* student_manager  ) {
    string choice;
    while (true) {
        cout << "\n================ STUDENT MANAGEMENT ================\n";
        cout << "1. Register New Student\n";
        cout << "2. View All Students (Basic List)\n";
        cout << "3. Search Student (View Full Profile)\n";
        cout << "4. Remove Student\n";
        cout << "0. Back to Main Menu\n";
        cout << "====================================================\n";
        
        choice = InputValidator::GetValidInput<string>("Enter your Choice: ");
        if(cin.peek() == '\n') cin.ignore();
        if (choice == "1") {
        student_manager->RegisterStudent();
     }  else if (choice == "2") {
        student_manager->ViewAllStudentsBasicProfile();
    } else if (choice == "3") {
        string roll_number;
        cout << "Enter student Roll Number: ";
        getline(cin,roll_number);
        cout << "Verify your credentials!" << endl;
        if(!VerifyIdentity(user_name_,password_))  {
            cout <<"Invlaid Credentials Entered!"<<endl;
            continue;
        }
        student_manager->ViewStudentBasicProfile(roll_number);
        student_manager->ViewStudentPrivateProfile(roll_number);
     } else if (choice == "4") {
        cout << "Verify your credentials!" << endl;
        if(!VerifyIdentity(user_name_,password_))  {
            cout <<"Invlaid Credentials Entered!"<<endl;
            continue;
        }
        string roll_number;
        cout << "Enter student Roll Number: ";
        getline(cin,roll_number);
        student_manager->RemoveStudent(roll_number);

    } else if (choice == "0") {
        cout << "Exiting...." << endl;
        break;
    } else {
        cout << "Invalid Input!" << endl;
    }
    
    }
}


void Admin::ManageFaculty(ProfessorManager* professor_manager,  CourseManager* course_manager) {
    while (true) {
        cout << "\n================ FACULTY MANAGEMENT ================\n";
        cout << "1. Hire New Professor\n";
        cout << "2. View All Professors\n";
        cout << "3. Search Professor (View Profile)\n";
        cout << "4. Fire Professor (Remove)\n";
        cout << "5. Assign Professor to a Course\n";
        cout << "6. UnAssign Professor from a Course\n";
        cout << "0. Back\n";
        cout << "====================================================\n";

        string choice = InputValidator::GetValidInput<string>("Enter Option: ");
        if(cin.peek() == '\n') cin.ignore(); 

        if (choice == "1") {
            cout << "\n--- HIRIING PROCESS ---\n";
            string name, gender, role, email,employee_id;
            int age;
            //cout << "Enter Name: ";
            name = InputValidator::InputName();
            cout << "Enter Gender (M/F): "<<endl; 
            gender = InputValidator::InputGender();
            //if (std::cin.peek() == '\n')    cin.ignore();    
            age = InputValidator::InputAge();
            cout <<"Enter role: (e.g assistant professor): ";
            getline(cin,role);
            cout << "Generating employee ID.....\n";
            cout << "Generating employee email id...\n";
            cout << "Generating default password....\n";
            employee_id = professor_manager->GenerateProfessorId();
            email = professor_manager->GenerateProfessorEmail(employee_id);
            string default_password = Security::GenerateStrongPassowrd();
            
            Professor* new_prof = new Professor(name,gender,age,role,email,employee_id,default_password);            
            
            professor_manager->AddProfessor(new_prof);
            professor_manager->WriteOrUpdateProfessor();
            cout << "\n[SUCCESS] Professor Hired!\n";
            cout << "Assigned Employee ID: " << employee_id << endl;
            cout << "Default Password:     " << default_password << endl;
            cout << "Note: Professor can change the default password after first login!" << endl;
        } 
        else if (choice == "2") {
            professor_manager->ViewAllProfessors();
        } 
        else if (choice == "3") {
            string id;
            cout << "Enter Employee ID (e.g. emp-1001): ";
            getline(cin, id);
            
            if(professor_manager->IsProfessorExist(id)) {
                professor_manager->ViewProfessor(id);
            } else {
                cout << "ERROR: Professor not found.\n";
            }
        } 
        else if (choice == "4") {
            string id;
            cout << "Enter Employee ID to Fire: ";
            getline(cin, id);

            if (professor_manager->IsProfessorExist(id)) {
                while (true) {
                cout << "Are you sure you want to remove " << id << "? (y/n): ";
                string confirm; 
                getline(cin, confirm);
                
                if(confirm == "y" || confirm == "Y") {
                    cout << "Verify your credentials!" << endl;
                    if (!VerifyIdentity(user_name_,password_)) {
                        cout << "Authentication failed!" << endl;
                        break;
                    }
                    professor_manager->RemoveProfessor(id);
                    cout << "professor " << id << " removed!" << endl;
                    break;
                } else if(confirm == "N" || confirm == "n") {
                    cout << "Operation Cancelled.\n";
                    break;
                } else {
                    cout << "Invalid Input!" << endl;
                }
                }
                
            } else {
                cout << "ERROR: Employee ID not found.\n";
            }
        } else if (choice == "5") {

            string emp_id, course_code;
            while (true) {
            cout << "Enter Employee ID: ";
            getline(cin, emp_id);
            cout << "Enter Course Code: ";
             getline(cin, course_code);

            Professor* prof = professor_manager->GetProfessor(emp_id);
            Course* temp_course = course_manager->GetCourse(course_code);

            if (prof == nullptr) {
                cout << "ERROR: Professor not found.\n";
                continue;
            } 
            else if (temp_course == nullptr) {
                cout << "ERROR: Course not found.\n";
                continue;
            } 
            else {

                if (prof->IsCourseExist(course_code)) {
                    cout << "Professor is already assigned to this course.\n";
                    continue;
                } else {
                    prof->AddCourse(temp_course);
                    professor_manager->WriteOrUpdateProfessor(); 
                    
                    cout << "[SUCCESS] Assigned " << temp_course->course_code() 
                     << prof->name() << ".\n";
                     break;
                }
            }
        }
            

        } else if (choice == "6")  {
            string emp_id, course_code;
            while (true) {
            cout << "Enter Employee ID: ";
             getline(cin, emp_id);
            
            Professor* prof = professor_manager->GetProfessor(emp_id);
            if(prof == nullptr) {
                cout << "ERROR: Professor not found.\n";
                continue;
            }

            cout << "--- Currently Teaching ---\n";
            prof->ViewCourses();
            cout << "Enter Course Code to Remove: ";
            getline(cin, course_code);

            if (prof->IsCourseExist(course_code)) {
                prof->RemoveCourse(course_code);
                professor_manager->WriteOrUpdateProfessor(); // Save
                cout << "Course removed from workload!.\n";
                break;
            } else {
                cout << "ERROR: Professor is not teaching this course.\n";
            }

            }
            
        }
        else if (choice == "0") break;
        else {
            cout << "Invalid Option. Try again.\n";
        }
    }

}

void Admin::ManageCourses(CourseManager* course_manager) {
while (true) {
        cout << "\n================ COURSE MANAGEMENT ================\n";
        cout << "1. Add New Course\n";
        cout << "2. View All Courses\n";
        cout << "3. Search Course (View Details)\n";
        cout << "4. Remove Course\n";
        cout << "0. Back\n";
        cout << "===================================================\n";

        string choice = InputValidator::GetValidInput<string>("Enter Option: ");
        if(cin.peek() == '\n') cin.ignore(); 

        if (choice == "1") {
            cout << "\n--- ADD NEW COURSE ---\n";
            string course_title, course_code, course_room_assigned;
            int credits_hours;

            cout << "Enter Course Code (e.g. CS-101): "; 
            getline(cin, course_code);
            
            if(course_manager->IsCourseExist(course_code)) {
                cout << "Course " << course_code << " already exists!\n";
                continue;
            }

            cout << "Enter Course Title: "; 
            getline(cin, course_title);
            cout << "Enter Building(A,B,C) to assign room: ";
            string building;
            getline(cin,building);
            int seating_capacity;
            bool has_multimedia;
            cout << "Enter seating capacity for the room: ";
            cin>>seating_capacity;
            cin.ignore();
            while(true) {
                string choice;
                cout << "Has multimedia? y/n: ";
                getline(cin,choice);
                if (choice == "y" || choice == "Y") {
                    has_multimedia = true;
                    break;
                } else if (choice == "n" || choice == "N") {
                    has_multimedia = false;
                    break;
                } else {
                    cout << "Invalid choice entered!" ;
                }
            }
            RoomManager rm;
            rm.LoadRoomsFromFile();
            string room_id = rm.GenerateRoomID(building);
            rm.CreateRoom(building,room_id,seating_capacity,has_multimedia);
            
            credits_hours = InputValidator::GetValidInput<int>("Enter Credit Hours (1-4): ");
            if(cin.peek() == '\n') cin.ignore();
            if (credits_hours < 1 || credits_hours > 4) {
                cout << "ERROR: Invalid Credit Hours. Course not added.\n";
                continue;
            }

            Course* new_course = new Course(course_code, course_title, room_id, credits_hours);
            course_manager->AddCourse(new_course);
            course_manager->WriteOrUpdateCourse();
            cout << "SUCCESS Course " << course_code << " added successfully.\n";
        } 
        
        else if (choice == "2") {
            course_manager->ViewAllCourses();
        } 
        
        else if (choice == "3") {
            string code;
            while (true) {
            cout << "Enter Course Code: ";
            getline(cin, code);
            
            Course* c = course_manager->GetCourse(code);
            if(c != nullptr) {
                c->PrintCourse(true);
                break;
            } else {
                cout << "ERROR: Course not found.\n";
            }
            }
            
        } 
        else if (choice == "4") {
            string code;
            while (true) {
            cout << "Enter Course Code to Remove: ";
            getline(cin, code);
            course_manager->LoadCourseDataFromFile();
            if (course_manager->GetCourse(code) != nullptr) {
                while (true) {

                cout << "Are you sure you want to delete " << code << "? (y/n): ";
                string confirm; getline(cin, confirm);
                
                if (confirm == "y" || confirm == "Y") {
                    course_manager->RemoveCourse(code);
                    cout << "Course Removed!" << endl;
                    break;
                } else if (confirm == "n" || confirm == "N") {
                    cout << "Operation Cancelled.\n";
                    break;
                } else {
                    cout << "Invalid input!" << endl;
                }

                }
                break;
                
            } else {
                cout << "[ERROR] Course not found.\n";
            }
            }
            
        } 

        else if (choice == "0") {
            break;
        } 
        else {
            cout << "Invalid Option. Try again.\n";
        }
    }
}


void Admin::AddPrivateInfo(
    std::string cnic,
    std::string address,
    std::string personal_email,
    std::string father_name,
    std::string date_of_birth
    ) {
        private_info.cnic_ = cnic;
        private_info.address_ = address;
        private_info.personal_email_ = personal_email;
        private_info.date_of_birth_ = date_of_birth;
        private_info.father_name_ = father_name;
}