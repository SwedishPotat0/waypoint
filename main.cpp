#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <filesystem>
#include <vector>

#include "fileParsing.h"

const char* RESET = "\033[0m";
const char* RED = "\033[31m";
const char* GREEN = "\033[32m";

void throwError(std::string errorMSG) { std::cout << RED << "Error: " << RESET; std::cout << errorMSG << '\n'; }
void throwSuccses(std::string succsesMSG) {std::cout << GREEN << succsesMSG << RESET << '\n';}

int main(int argc, char* argv[]) {
	bool dir = checkDir();
	if (dir) { throwSuccses("Succseded to creat directory & config file"); return 0;}
	else if (!dir) { if (argc < 2) { throwError("It needs to be atleast 1 arguments"); return 1;}
		 
	std::string arg = argv[1];
	std::string name; if (argc > 2) {name = argv[2];} else {name = "";}
	std::string prg = getEditor();
	std::string path = std::string(getenv("HOME")) + "/.waypoint/waypoint.txt";

	if (arg == "jump") {
		std::string location;
		std::ifstream read(path);
		std::string line;
		std::vector<std::string> waypoint;
 
		while (getline(read, line)) { 
			waypoint = splitWaypoint(line);
			if (name == waypoint[0]) {
				location = waypoint[1];
				break;
			}
		}
		location = trimLocation(location);
		std::cout << location;
	}
	if (arg == "open") {	
		std::string location;
		std::ifstream read(path);
		std::string line;
		std::vector<std::string> waypoint;
 
		while (getline(read, line)) { 
			waypoint = splitWaypoint(line);
			if (name == waypoint[0]) {
				location = waypoint[1];
				break;
			}
		}
		std::string cmd = prg + " " + location;
		system(cmd.c_str());
	}
	if (arg == "add" && argc == 4) {
		std::string file = argv[3];
		std::ofstream write(path, std::ios::app);
		write << name << "|" << file << "|" << '\n';
		write.close();
	} else if (arg == "add") { throwError("add needs 3 arguments"); return 1;}
	if (arg == "tag" && argc == 4) {
		std::string location;
		std::ifstream read(path);
		std::string line;
		std::string row;
		int index = 0;
		std::string tag = argv[3];
		std::vector<std::string> rows;
		std::vector<std::string> waypoint;

		while (getline(read, line)) { 
			std::string word = "";
			bool nameTrue = false;
			row = "";
			waypoint = splitWaypoint(line);
			if (name == waypoint[0]) {
				nameTrue = true;
				row += waypoint[0]; row += '|'; 
				row += waypoint[1]; row += '|';
				if (waypoint[2] != "") { row += waypoint[2]; row += '|';}
			}
			if(nameTrue){row += tag; rows.push_back(row);}else{rows.push_back(line);}}
		std::ofstream write(path);
		for (const auto& r : rows) { write << r << '\n'; }
		write.close();

	} else if (arg == "tag") { throwError("tag needs 3 arguments"); return 1;}
	if (arg == "list") {
		std::ifstream read(path);
		std::string line;
		std::vector<std::string> waypoint;
		if (name == "all") {	
			while (getline(read, line)) {std::cout << line << std::endl;}
		} else if (name == "name") {
			if (argc != 4) {throwError("Parameter NAME needs 3 arguments"); return 1;}
			std::string search = argv[3];
			while (getline(read, line)) {
				waypoint = splitWaypoint(line);
				if (search == waypoint[0]) {std::cout << line << std::endl;}
			}
		} else if (name == "tag") {
			if (argc != 4) {throwError("Parameter TAG needs 3 arguments"); return 1;}
			std::string search = argv[3];
			while (getline(read, line)) {
				waypoint = splitWaypoint(line);
				if (search == waypoint[2]) {std::cout << line << std::endl;}
			}
		} else if (name == "group") {
			if (argc != 4) {throwError("Parameter GROUP needs 3 arguments"); return 1;}
			std::string search = argv[3];
		} else {throwError("Unkown parameter for list: " + name ); return 1;}
	}
	if (arg == "getPath") {
		std::string location;
		std::ifstream read(path);
		std::string line;
		std::vector<std::string> waypoint;

		while (getline(read, line)) { 
			waypoint = splitWaypoint(line);
			if (name == waypoint[0]) {
				location = waypoint[1];
				break;
			}
		}
		std::cout << location;
	}
	if (arg == "remove") {
		std::ifstream read(path);
		std::string line;
		std::vector<std::string> waypoint;
		std::vector<std::string> row;
 
		while (getline(read, line)) { 
			waypoint = splitWaypoint(line);
			if (name == waypoint[0]) {
				continue;
			} else {
				row.push_back(line);
			}
		}
		std::ofstream write(path);
		for (const auto& r : row) { write << r << '\n'; }
		write.close();

	}
	if (arg == "init") {
		std::filesystem::path dir = ".waypoint";
		if (!std::filesystem::exists(dir)) { std::filesystem::create_directory(dir);}
		else {std::cout << "Local Waypoint alredy exsists";}
	}
}}
