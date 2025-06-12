#include "Room.h"
#include <stdexcept>
#include <iostream>

std::optional<Direction> parseDirection(const std::string& str)
{
	if (str == "north" || str == "w" || str == "W") {
		return Direction::North;
	}
	else if (str == "south" || str == "s" || str == "S") {
		return Direction::South;
	}
	else if (str == "east" || str == "d" || str == "D") {
		return Direction::East;
	}
	else if (str == "west" || str == "a" || str == "A") {
		return Direction::West;
	}

	return std::nullopt;
}

std::string toString(Direction dir)
{
	switch (dir) {
		case Direction::North: return "North";
		case Direction::South: return "South";
		case Direction::East: return "East";
		case Direction::West: return "West";
		default: throw std::invalid_argument("Invalid direction");
	}
}

Direction oppositeDirection(Direction dir)
{
	switch (dir) {
		case Direction::North: return Direction::South;
		case Direction::South: return Direction::North;
		case Direction::East: return Direction::West;
		case Direction::West: return Direction::East;
		default: throw std::invalid_argument("Invalid direction");
	}
}



std::unordered_map<int, Room> allRooms;

int Room::hashId()
{
	int hash = 0;
	const int tableSize = 137;

	for (char c : name) {
		hash = (hash * 31 + c) % tableSize;
	}
	for (char c : description) {
		hash = (hash * 31 + c) % tableSize;
	}

	return hash;
}

Room::Room() : name(""), description(""), id(0)
{
}

Room::Room(const std::string& name, const std::string& description)
	: name(name), description(description)
{
	id = hashId();
	if (allRooms.find(id) != allRooms.end()) {
		int i;
		for (i = 1; allRooms.find(id + i) != allRooms.end(); i++);
		id += i;
	}	

	allRooms.insert({ id, *this });
}

void Room::setName(const std::string& name)
{
	this->name = name;
}

void Room::setDescription(const std::string& description)
{
	this->description = description;
}

bool Room::addNeighbor(Direction dir, int roomId)
{
	if (allRooms.find(roomId) == allRooms.end()) {
		std::cerr << "Room with ID " << roomId << " does not exist." << std::endl;
		return false;
	}
	if (neighbors.find(dir) != neighbors.end()) {
		OPTION:
		std::cout << "Direction " << toString(dir) << " is already set for room ID " << id << "." << std::endl;
		std::cout << "Replace it or not(Y/n): ";

		char choice;
		std::cin >> choice;

		switch (choice) {
		case 'Y':
		case 'y':
			neighbors.erase(dir);
			break;
		case 'N':
		case 'n':
			std::cout << "Neighbor not changed." << std::endl;
			return false;
		default:
			std::cout << "Invalid answer. Try again." << std::endl;
			goto OPTION;
		}
	}

	neighbors[dir] = roomId;

	for (auto& pair : neighbors) {
		std::cout << std::format("[{}: {}]", toString(pair.first), pair.second) << std::endl;
	}
	return true;
}

bool Room::connectWith(int roomId, Direction dir)
{
	return addNeighbor(dir, roomId) && allRooms[roomId].addNeighbor(oppositeDirection(dir), getId());
}

int Room::getId() const
{
	return id;
}

std::string Room::getName() const
{
	return name;
}

std::string Room::getDescription() const
{
	return description;
}

std::unordered_map<Direction, int> Room::getNeighbors() const
{
	return neighbors;
}

std::optional<Room> Room::goToDirection(Direction dir) const
{
	printInfo();
	auto target = neighbors.find(dir);

	if (target == neighbors.end()) {
		std::cerr << "No neighbor in direction " << toString(dir) << std::endl;
		return std::nullopt;
	}

	return allRooms[target->second]; // Return the room object from the global map
}

void Room::printInfo() const
{
	std::cout << std::format("[{}]{}: {}", id, name, description) << std::endl;

	std::cout << "{"  << std::endl;
	for (auto neighbor : neighbors) {
		std::cout << std::format("{}£º {}\n", toString(neighbor.first), neighbor.second);
	}
	std::cout << "}\n";
}

std::optional<Room*> findId(int roomId)
{
	if (allRooms.find(roomId) == allRooms.end()) {
		std::cerr << "Room with ID " << roomId << " does not exist." << std::endl;
		return std::nullopt;
	}

	return &allRooms[roomId];
}