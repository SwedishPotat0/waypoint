#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <filesystem>
#include <vector>

const char* RESET = "\033[0m";
const char* RED = "\033[31m";
const char* GREEN = "\033[32m";

void throwError(std::string errorMSG) { std::cout << RED << "Error: " << RESET; std::cout << errorMSG << '\n'; }
void throwSuccses(std::string succsesMSG) {std::cout << GREEN << succsesMSG << RESET << '\n';}

void makeConfig() {
	std::ofstream write(std::string(getenv("HOME")) + "/.waypoint/config.txt", std::ios::app);
	write << "editor=vim" << '\n';
	write.close();
}

bool checkDir() {
	std::filesystem::path dir = std::string(getenv("HOME")) + "/.waypoint";
	if (!std::filesystem::exists(dir)) { std::filesystem::create_directory(dir); makeConfig();  return true;}
	return false;
}

std::string getEditor() {
	std::string editor = "";
	std::string parameter = "";
	std::string line;
	std::fstream read(std::string(getenv("HOME")) + "/.waypoint/config.txt");
	bool parameterTrue = false;

	while(getline(read, line)) {
		parameter = "";
		for (size_t i = 0; i < line.length(); i++) {
				if (line[i] == '=') {
					if (parameter == "editor") { parameterTrue = true; continue;}	
				} else { parameter += line[i];}
				if (parameterTrue) { editor += line[i];}
		}
		if (!editor.empty()) {break;}
	}
	return editor;
}

std::vector<std::string> splitWaypoint(std::string waypoint) {
	std::string name = ""; std::string location = ""; std::string tag = "";	
	bool nameC = false; bool locationC = false; bool tagC = false;
	std::vector<std::string> Waypoint;
	for (size_t i = 0; i < waypoint.length(); i++) {
		if (waypoint[i] == '|') {
			if (name != "") {nameC = true;}
			if (location != "") {locationC = true;}
			continue;
		}
		if (locationC) {tag += waypoint[i];}
		else if (nameC) {location += waypoint[i];}	
		else {name += waypoint[i];}
	}
	Waypoint.push_back(name);
	Waypoint.push_back(location);
	Waypoint.push_back(tag);

	return Waypoint;
}

std::string trimLocation(std::string location) {
	std::vector<std::string> path;
	std::string temp = "";
	std::string Location;
	for (size_t i = 0; i < location.length(); i++) {
		if (location[i] == '/') {
			if (temp != "") {
				path.push_back(temp+"/");
				temp = "";
				continue;
			}
		}
		temp += location[i];
	}	
	for (const auto& p : path) {Location += p;}
	return Location;
}

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
		if (name == "all") {
		std::ifstream read(path);
		std::string line;
		while (getline(read, line)) {std::cout << line << std::endl;}
		} else if (name == "name") {
			if (argc != 4) {throwError("Parameter NAME needs 3 arguments"); return 1;}
			std::string search = argv[3];
		} else if (name == "tag") {
			if (argc != 4) {throwError("Parameter TAG needs 3 arguments"); return 1;}
			std::string search = argv[3];
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
