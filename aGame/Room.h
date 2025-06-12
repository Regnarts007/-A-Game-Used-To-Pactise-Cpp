#pragma once
#include <optional>
#include <string>
#include <map>
#include <unordered_map>

enum class Direction
{
	North,
	South,
	East,
	West
};

std::optional<Direction> parseDirection(const std::string& str);
std::string toString(Direction dir);
Direction oppositeDirection(Direction dir);


class Room
{
private:
	int id;
	std::string name;
	std::string description;
	std::unordered_map<Direction, int> neighbors;

public:
	Room();
	Room(const std::string& name, const std::string& description);

	// setters
	int hashId();
	void setName(const std::string& name);
	void setDescription(const std::string& descriptiong);
	bool addNeighbor(Direction dir, int roomId);
	bool connectWith(int roomId, Direction dir);

	// getters
	int getId() const;
	std::string getName() const;
	std::string getDescription() const;
	std::unordered_map<Direction, int> getNeighbors() const;
	std::optional<Room> goToDirection(Direction dir) const;

	// print information
	void printInfo() const;
};

std::optional<Room*> findId(int roomId);

extern std::unordered_map<int, Room> allRooms; // Global map of rooms by ID

