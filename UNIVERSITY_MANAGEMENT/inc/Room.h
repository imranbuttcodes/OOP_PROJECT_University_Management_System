#pragma once
#include <iostream>
class Room {
public:
Room(std::string building_id, std::string room_id, int seating_capacity, bool has_multimedia);
const std::string room_id_; // room_id = building_id_ + -ROOM_NUMBER(SYSTEM GENERATED)
const std::string building_id_;
int seating_capacity_;
bool has_multimedia_;
void PrintRoomDetails() const;
};