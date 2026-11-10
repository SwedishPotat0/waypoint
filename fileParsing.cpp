#include <vector>
#include <string>
#include <filesystem>
#include <fstream>

#include "fileParsing.h"
#include "color.h"

void makeConfig() {
	std::ofstream write(std::string(getenv("HOME")) + "/.waypoint/config.txt", std::ios::app);
	write << "editor=vim" << '\n';
	write.close();
}

bool checkDir() {
	std::filesystem::path dir = std::string(getenv("HOME")) + "/.waypoint";
	if (!std::filesystem::exists(dir)) { std::filesystem::create_directory(dir); makeConfig(); return true;}
	return false;
}

std::vector<std::vector<std::string>> splitWaypoint(std::string waypoint) {
	std::string name = ""; std::string location = ""; std::string tag = "";	
	bool nameC = false; bool locationC = false; bool tagC = false;
	std::vector<std::string> tags; std::vector<std::vector<std::string>> Waypoint; 	
	for (size_t i = 0; i < waypoint.length(); i++) {
		if (waypoint[i] == '|') {
			if (name != "") {nameC = true;}
			if (location != "") {locationC = true;}
			if (tag != "") {tags.push_back(tag); tag = "";}
			continue;
		}
		if (locationC) {tag += waypoint[i];}
		else if (nameC) {location += waypoint[i];}	
		else {name += waypoint[i];}
	}
	if(tag != "") { tags.push_back(tag); }
	Waypoint.push_back({name});
	Waypoint.push_back({location});
	Waypoint.push_back(tags);

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

bool checkLocal() {
	if (std::filesystem::is_directory(".waypoint")) {
		return true;
	} else {
		return false;
	}
}

const char* getColor(const std::string TAG) {
	if (TAG == "RESET") { return colors[RESET]; }
	std::string path; if (checkLocal()) { path = ".waypoint/colors.txt";} else { path = std::string(getenv("HOME")) + "/.waypoint/colors.txt";}
	if (!std::filesystem::exists(path)) { return colors[RESET]; }
	else {
		std::fstream read(path);
		std::string line;

		bool tagFound = false;
		std::string tag = "";
		std::string c = "";
		while (getline(read, line)) {
			tagFound = false;
			tag = "";
			c = "";		
			for (size_t i = 0; i < line.length(); i++) {
				if (line[i] == '=' && tag != "") { if (TAG == tag) { tagFound = true; continue; } else { continue; } }
				else if (!tagFound) { tag += line[i]; }
				else if (tagFound) { c += line[i]; }
			}
			if (c != "") {
				for (int i = 0; i < COLOR_COUNT; i++) {
					if (c == colorNames[i]) { return colors[i]; }
				}
			}
	}
	return colors[RESET];
	}
}
