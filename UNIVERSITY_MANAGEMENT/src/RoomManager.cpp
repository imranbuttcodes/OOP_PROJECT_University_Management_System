#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include "Managers/RoomManager.h"
#include "Room.h"

using std::cout;
using std::endl;
using std::string;
using std::cin;
// std::string RoomManager::GenerateRoomID(std::string building_id) {
    
// }
bool RoomManager::UpdateORSaveRoomsInFile(Room* room) {
    std::ofstream write_rooms("data/rooms.txt");
    if(!write_rooms) {
        return false;
    }
    if(room == nullptr) {
        for(const auto& room_entry: rooms_) {
            write_rooms<<room_entry->building_id_ <<'|'<< room_entry->room_id_ << '|' << room_entry->seating_capacity_ << '|' << (room_entry->has_multimedia_?"YES":"NO") << std::endl;
        }
    } else {
        for (auto& room_entry: rooms_) {
            if(room_entry->room_id_ == room->room_id_) {
                delete room_entry;
                room_entry = room;
            }
            write_rooms<< room_entry->building_id_ <<'|' << room_entry->room_id_ << '|' << room_entry->seating_capacity_ << '|' << (room_entry->has_multimedia_?"YES":"NO") << std::endl;       
        }
    }
    write_rooms.close();
    return true;
}


void RoomManager::RemoveRoom(std::string room_id) {
    rooms_count--;
    if (!IsRoomExist(room_id)) {
        cout << "Room not found! "<< endl;
        return ;
    }
    for (auto& room: rooms_){
        if (room->room_id_ == room_id) {
            auto it = std::find(rooms_.begin(), rooms_.end(), room);
            if (it != rooms_.end()) {
                rooms_.erase(it);
                UpdateORSaveRoomsInFile(nullptr);
                return;
            }
        }
    }
}


void RoomManager::RoomPanal() {
    string choice, building;
    int seating_capacity;
    string has_multimedia, room_id;
    while (true) {
    cout << "-------------------- Room Panel --------------------" << endl;
    cout << "[1] Add Room" << endl;
    cout << "[2] Search Room" << endl;
    cout << "[3] Remove Room" << endl;
    cout << "[4] View All Rooms" << endl;
    cout << "[0] Exit" << endl;
    cout << "Enter your choice: ";
    getline(cin,choice);
    if (choice == "1") {
        while (true) {
        cout << "Enter Building: ";
        getline(cin, building);
        cout << "Enter seating capacity: " ;
        if(cin >> seating_capacity) {
            if (cin.peek() == '\n')      cin.ignore();
            if (seating_capacity < 0) {
                cout << "Enter positive numbers only!" << endl;
            } 
            
        } else {
            cout << "Enter integer numbers only!" << endl;
        }
        cout << "Has Multimedia? [y/n]: ";
        getline(cin, has_multimedia);
        if (has_multimedia == "y" || has_multimedia == "Y") {
            CreateRoom(building, GenerateRoomID(building), seating_capacity, true);
            cout << "Room created!" << endl;
            break;
        } else if (has_multimedia == "n" || has_multimedia == "N") {
            CreateRoom(building, GenerateRoomID(building), seating_capacity, false);
            cout << "Room created!" << endl;
            break;
        }
    }
    } else if (choice == "2") {
        cout << "Enter room id: ";
        getline(cin, room_id);
        if (!IsRoomExist(room_id)) {
            cout << "Room not found!" << endl;
        } else {
            Room* target_room = GetRoom(room_id);
            if (target_room != nullptr) {
                std::cout << std::left << std::setw(15) <<"Building ID"
                << std::setw(15) <<"Room ID"
                << std::setw(15) <<"Seating Capacity  "
                << std::setw(15) << "Has Multimedia?" 
                <<std::endl;
                target_room->PrintRoomDetails();
                cout << endl;
            } else {
                cout << "Room not found!" << endl;
            }

        }
    } else if (choice == "3") {
       cout << "Enter room id: ";
        getline(cin, room_id);
        if (!IsRoomExist(room_id)) {
            cout << "Room not found!" << endl;
        } else {
            RemoveRoom(room_id);
            cout << "Room " << room_id << " removed successfully! " << endl;
        }
    } else if (choice == "4") {
             PrintAllRooms();
    } else if (choice == "0") {
           cout << "Exiting...\n";
           break;
    } else {
        cout << "Invlaid Input!" << endl;
    }
    }

}



bool RoomManager::LoadRoomsFromFile() {
    std::ifstream read_file("data/rooms.txt");
    if(!read_file)  return false;
    if(!rooms_.empty()) {
        for(auto r: rooms_) {
            delete r;
        }
        rooms_.clear();
    }
    std::string line, file_building_id, file_room_id, str_seating_capacity, str_has_multimedia;
    while(getline(read_file,line)) {
        if (line.empty()) {
            read_file.close();
            return false;
        }
        std::stringstream ss(line);
        getline(ss,file_building_id,'|');
        getline(ss,file_room_id,'|');
        getline(ss,str_seating_capacity,'|');
        getline(ss,str_has_multimedia, '|');
        rooms_.emplace_back(new Room(file_building_id,file_room_id, !str_seating_capacity.empty() ? std::stoi(str_seating_capacity): 0,(str_has_multimedia == "YES"? true: false)));
    }
    return true;
}


Room* RoomManager::GetRoom(std::string room_id) const {
     for (auto room_entry: rooms_) {
            if(room_entry->room_id_ == room_id) {
                return room_entry;
        }
    }
    return nullptr;
}

bool RoomManager::CreateRoom(std::string building_id, std::string room_id, int seating_capacity, bool has_multimedia) {
    if(IsRoomExist(room_id))    return false;
    rooms_.push_back(new Room(building_id, room_id,seating_capacity,has_multimedia));
    rooms_count++;
    return UpdateORSaveRoomsInFile(nullptr);
}

bool RoomManager::IsRoomExist(std::string room_id) {
    return GetRoom(room_id) != nullptr;
}

RoomManager::~RoomManager() {
    for(auto& room: rooms_) {
        delete room;
    }
    rooms_.clear();
}

void RoomManager::PrintAllRooms()  {
    std::cout << std::left << std::setw(15) <<"Building ID"
    << std::setw(15) <<"Room ID"
    << std::setw(15) <<"Seating Capacity  "
    << std::setw(15) << "Has Multimedia?" 
    <<std::endl;
    std::cout << std::string(50,'-') <<std::endl;
    for(auto room: rooms_) {
        room->PrintRoomDetails();
    } 

}

std::string RoomManager::GenerateRoomID(std::string building_id) {
    LoadRoomsFromFile();
    if(rooms_.empty()) {
        return building_id + "-100"; 
    } 
    int max_room_id = 0;
    for(auto room: rooms_) {
        if(room->building_id_ == building_id) {
            std::stringstream ss(room->room_id_);
            std::string temp_id;
            getline(ss,temp_id,'-');
            getline(ss,temp_id,'|');
            int id = stoi(temp_id);
            if(id > max_room_id) {
                max_room_id = id;
            }
        }
    }
    ++max_room_id;
    return building_id + "-" + std::to_string(max_room_id);
    
}


int RoomManager::rooms_count = 0;