#include <vector>
#include <string>
#include <filesystem>
#include <fstream>

#include "fileParsing.h"

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
