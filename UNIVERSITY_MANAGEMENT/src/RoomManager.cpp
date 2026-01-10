#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include "Managers/RoomManager.h"
#include "Room.h"

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
        std::stringstream ss(line);
        getline(ss,file_building_id,'|');
        getline(ss,file_room_id,'|');
        getline(ss,str_seating_capacity,'|');
        getline(ss,str_has_multimedia, '|');
        rooms_.emplace_back(new Room(file_building_id,file_room_id, std::stoi(str_seating_capacity),(str_has_multimedia == "YES"? true: false)));
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
void RoomManager::PrintAllRooms() const {
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