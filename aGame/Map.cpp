#include "Map.h"
#include <iostream>

Map::Map() : currentRoomId(-1)
{
}

bool Map::addRoom(int roomId)
{
	std::optional<Room*> target = findId(roomId);

	if (target == std::nullopt) {
		std::cerr << std::format("Room with ID {} does not exist!", roomId) << std::endl;
		return false;
	}

	rooms.insert({roomId, **target});

	if (rooms.size() == 1) {
		currentRoomId = roomId;
	}

	return true;
}

bool Map::go(Direction dir) {
	std::optional<Room> target = (**findId(currentRoomId)).goToDirection(dir);

	if (target == std::nullopt) {
		return false;
	}

	currentRoomId = (*target).getId();
	return true;
}

void Map::describeCurrentRoom() {
	Room* currentRoom = *findId(currentRoomId);

	std::cout << "You are in " << currentRoom->getName() << ".\n" << currentRoom->getDescription() << std::endl;
}

Room Map::getCurrentRoom() const
{
	return rooms.at(currentRoomId);
}

std::optional<Room> Map::findById(int roomId) const
{
	auto it = rooms.find(roomId);
	if (it != rooms.end()) {
		return it->second;
	}

	return std::nullopt;
}
