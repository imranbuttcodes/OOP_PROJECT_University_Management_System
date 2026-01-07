#include <iomanip>
#include "Room.h"

Room::Room(std::string building_id, std::string room_id, int seating_capacity, bool has_multimedia): room_id_(room_id), building_id_(building_id){
    seating_capacity_ = seating_capacity;
    has_multimedia_ = has_multimedia;
}

void Room::PrintRoomDetails() const {
    
    std::cout << std::left << std::setw(15) << building_id_ 
    << std::setw(15) << room_id_ 
    << std::setw(15) << seating_capacity_ 
    << std::setw(15) << (has_multimedia_? "YES": "NO")
    << std::endl<<std::endl;
    
}
