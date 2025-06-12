#pragma once
#include "Room.h"
#include <unordered_map>

class Map
{
private:
	std::unordered_map<int, Room> rooms;
	int currentRoomId;

public:
	// construction
	Map();

	// setter
	bool addRoom(int roomId);
	bool go(Direction dir);
	void describeCurrentRoom();

	// getter
	Room getCurrentRoom() const;
	std::optional<Room> findById(int roomId) const;
};

