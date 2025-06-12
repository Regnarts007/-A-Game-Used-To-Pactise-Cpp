#include "Map.h"
#include <iostream>
#include <sstream>

int main() {
	Map map;
	bool quit = false;

	do {
		std::string line;

		std::cout << ">";
		std::getline(std::cin, line);

		std::istringstream iss(line);

		std::string cmd;
		iss >> cmd;

		if (auto dirOpt = parseDirection(cmd)) {
			if (!map.go(*dirOpt)) {
				std::cout << "You can't go that way." << std::endl;
			}
			else {
				map.describeCurrentRoom();
			}
		}
		else if (cmd == "look") {
			map.describeCurrentRoom();
		}
		else if (cmd == "help") {
			std::cout << "Available commands: north/south/west/east/w/a/s/d, look, quit";
		}
		else if (cmd == "quit") {
			quit = true;
		}
		else if (cmd == "create") {
			std::string name, description;
			
            iss >> std::ws;
			std::getline(iss, name);

			std::cout << "Describe " << name << ": ";
			std::getline(std::cin, description);

			Room newRoom = Room(name, description);
			if (map.addRoom(newRoom.getId())) {
				std::cout <<  name << " is successfully created with ID: " << newRoom.getId() << std::endl;
			}
			else {
				std::cout << "Failed to create room: " << name << std::endl;
			}
		}
		else if (cmd == "connect") {
			int id1, id2;
			std::string dir;
			iss >> id1 >> dir >> id2;

			auto room1 = map.findById(id1), room2 = map.findById(id2);
			auto direction = parseDirection(dir);
			if (room1 && room2 && direction) {
				if ((*room1).connectWith(id2, *direction)) {
					std::cout << "Connected room " << id1 << " to room " << id2 << " in direction " << toString(*direction) << std::endl;
				}
				else {
					std::cout << "Failed to connect rooms." << std::endl;
				}
			}
			else {
				std::cout << "Invalid room IDs or direction." << std::endl;
			}
		}
		else if (cmd == "check") {
			map.getCurrentRoom().printInfo();
		}
		else {
			std::cout << "Unknown command: " << cmd << std::endl;
		}
	} while (!quit);
}