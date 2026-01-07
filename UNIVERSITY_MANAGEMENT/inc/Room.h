#pragma once
#include <iostream>
class Room {
public:
Room(std::string room_id, int seating_capacity, bool has_multimedia);
const std::string room_id_;
int seating_capacity_;
bool has_multimedia_;
void PrintRoomDetails() const;
};