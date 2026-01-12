#pragma once

class Room;
#include<iostream>
#include<vector>
class RoomManager {
private:
std::vector<Room*> rooms_;
public:
static int rooms_count;
bool CreateRoom(std::string building_id, std::string room_id, int seating_capacity, bool has_multimedia);
bool LoadRoomsFromFile();
bool UpdateORSaveRoomsInFile(Room* room);//if(room == nullptr then it means just haven't updated any room so just save into file otherwise check the roomID and then replace it with room)
Room* GetRoom(std::string room_id) const;
bool IsRoomExist(std::string room_id);
void RemoveRoom(std::string room_id);
void PrintAllRooms() ;
void RoomPanal();
~RoomManager();
std::string GenerateRoomID(std::string building_id);
};