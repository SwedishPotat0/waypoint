#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <iomanip>

#include "command.h"
#include "fileParsing.h"
#include "message.h"

std::string writeTags (std::vector<std::string> tags) {
	std::string output;
	for (const auto& t : tags) { output += t; output += " ";}
	return output;
}

bool matchTags(std::string tag, std::vector<std::string> tags) {
	for (const auto& t : tags) { if(tag == t) { return true; } }
	return false;
}

bool checkDublicate(std::string path, std::string name) {
	std::string line;
	std::fstream read(path);
	std::vector<std::vector<std::string>> waypoint;
	while(getline(read, line)) {
		waypoint = splitWaypoint(line);
		if (name == waypoint[0][0]) {return true;}
	}
	return false;
}

bool checkLink(std::string name) {
	for (int i = 0; i < name.length(); i++) {
		if (name[i] == ':') {
			return true;
		}
	}
	return false;
}

void tag(std::string path, std::string name, std::string tag) {
	std::string line;
	std::string row;
	std::vector<std::string> rows;
	std::vector<std::vector<std::string>> waypoint;
	std::string location;
	std::ifstream read(path);

	while (getline(read, line)) { 
		std::string word = "";
		bool nameTrue = false;
		row = "";
		waypoint = splitWaypoint(line);
		if (name == waypoint[0][0]) {
			nameTrue = true;
			row += waypoint[0][0]; row += '|'; 
			row += waypoint[1][0]; row += '|';
			if (!waypoint[2].empty()) { for (const auto& t : waypoint[2]) { row += t; row += "|"; }}
		}
		if(nameTrue){row += tag; rows.push_back(row);}else{rows.push_back(line);}}
	std::ofstream write(path);
	for (const auto& r : rows) { write << r << '\n'; }
	write.close();
	throwSuccses("Tag '" + tag + "' added to waypoint '" + name + "'");
}

int list(std::string path, std::string name, char** argv, int argc) {
	std::ifstream read(path);
	std::string line;
	std::vector<std::vector<std::string>> waypoint;
	if (name == "all") {	
		std::cout << std::left << std::setw(20) << "Name" << std::setw(50) << "Path" << std::setw(20) << "Tag" << '\n';
		std::cout << std::left << std::string(90, '-') << '\n';
		while (getline(read, line)) {
			waypoint = splitWaypoint(line);
			std::cout << std::left << std::setw(20) << waypoint[0][0] << std::setw(50) << waypoint[1][0] << std::setw(20) << writeTags(waypoint[2]) << '\n';
		}
	} else if (name == "name") {
		if (argc != 4) {throwError("Parameter NAME needs 3 arguments"); return 1;}
		std::string search = argv[3];
		std::cout << std::left << std::setw(20) << "Name" << std::setw(50) << "Path" << std::setw(20) << "Tag" << '\n';
		std::cout << std::left << std::string(90, '-') << '\n';
		while (getline(read, line)) {
			waypoint = splitWaypoint(line);
			if (search == waypoint[0][0]) {
				std::cout << std::left << std::setw(20) << waypoint[0][0] << std::setw(50) << waypoint[1][0] << std::setw(20) << writeTags(waypoint[2]) << '\n';
			}
		}
	} else if (name == "tag") {
		if (argc != 4) {throwError("Parameter TAG needs 3 arguments"); return 1;}
		std::string search = argv[3];
		std::cout << std::left << std::setw(20) << "Name" << std::setw(50) << "Path" << std::setw(20) << "Tag" << '\n';
		std::cout << std::left << std::string(90, '-') << '\n';
		while (getline(read, line)) {
			waypoint = splitWaypoint(line);
			if (matchTags(search, waypoint[2])) {
				std::cout << std::left << std::setw(20) << waypoint[0][0] << std::setw(50) << waypoint[1][0] << std::setw(20) << writeTags(waypoint[2]) << '\n';
			}
		}
	} else if (name == "group") {
		if (argc != 4) {throwError("Parameter GROUP needs 3 arguments"); return 1;}
		std::string search = argv[3];
	} else {throwError("Unkown parameter for list: " + name ); return 1;}
	return 0;
}

void remove(std::string path, std::string name) {
	std::ifstream read(path);
	std::string line;
	std::vector<std::vector<std::string>> waypoint;
	std::vector<std::string> row;
 
	while (getline(read, line)) { 
		waypoint = splitWaypoint(line);
		if (name == waypoint[0][0]) {
			continue;
		} else {
			row.push_back(line);
		}
	}
	throwSuccses("Waypoint '" + name + "' removed");
	std::ofstream write(path);
	for (const auto& r : row) { write << r << '\n'; }
	write.close();

}

void getPath(std::string path, std::string name) {
	std::string location;
	std::ifstream read(path);
	std::string line;
	std::vector<std::vector<std::string>> waypoint;

	while (getline(read, line)) { 
		waypoint = splitWaypoint(line);
		if (name == waypoint[0][0]) {
			location = waypoint[1][0];
			break;
		}
	}
	std::cout << location;
}

std::string Path(std::string path, std::string name) {
	std::string location;
	std::ifstream read(path);
	std::string line;
	std::vector<std::vector<std::string>> waypoint;

	while (getline(read, line)) { 
		waypoint = splitWaypoint(line);
		if (name == waypoint[0][0]) {
			location = waypoint[1][0];
			break;
		}
	}
	return location;
}


void init() {
	std::filesystem::path dir = ".waypoint";
	if (!std::filesystem::exists(dir)) { std::filesystem::create_directory(dir);}
	else {std::cout << "Local Waypoint alredy exsists";}
}

void jump(std::string path, std::string name) {
	std::string location;
	std::ifstream read(path);
	std::string line;
	std::vector<std::vector<std::string>> waypoint;
 
	while (getline(read, line)) { 
		waypoint = splitWaypoint(line);
		if (name == waypoint[0][0]) {
			location = waypoint[1][0];
			break;
		}
	}
	location = trimLocation(location);
	std::cout << location;
}

void add(std::string path, std::string name, char** argv) {
	if (checkDublicate(path, name)) {throwError("Waypoint whit name " + name + " alredy exsists");}
	else {
		std::string Path;
		std::string file = argv[3];
		std::ofstream write(path, std::ios::app);
		write << name << "|" << file << "|" << '\n';
		write.close();
		throwSuccses("Waypoint '" + name + "' added");
	}
}

void open(std::string path, std::string name, std::string prg) {
	std::string location;
	std::ifstream read(path);
	std::string line;
	std::vector<std::vector<std::string>> waypoint;
	bool link = checkLink(name);
	std::string nameT;

	if (link) { std::string nameTEMP; bool linkFound = false; for (int i = 0; i < name.length(); i++) { if (name[i] == ':') { linkFound = true; continue; } if (linkFound) { nameT += name[i]; continue; } nameTEMP += name[i]; } name = nameTEMP; }
	while (getline(read, line)) { 
		waypoint = splitWaypoint(line);
		if (name == waypoint[0][0]) {
			location = waypoint[1][0];
			if (link) { location += "/" + Path(location + "/.waypoint/waypoint.txt", nameT); }
			break;
		}
	}
	if (!location.empty()) {
		std::string cmd = prg + " " + location;
		system(cmd.c_str());
	} else { throwError("No waypoint named '" + name + "' found"); }
}

void help() {
	std::vector<std::string> Help = {
		"add - adds a waypoint",
		"	waypoint add [name] [path]",
		"open - opens a waypoint in the configured editor",
		"	waypoint open [name]",
		"tag - tags a waypoint",
		"	waypoint tag [name] [tag]",
		"remove - removes a waypoint",
		"	waypoint remove [name]",
		"list - lists waypoints based on the given argument",
		"	waypoint list [arg] [serchterm]",
		"	Accsepted arguments:",
		"		all - needs no serch term",
		"		name - serches the name of waypoints",
		"		tag - serches the tag of waypoints",
		"getPath - fetches the path for a waypoint",
		"init - initilise a local waypoint in the current directory",
		"untag - removes one or all tags from a waypoint",
		"	waypoint untag [name]",
		"		remoives all tags",
		"	waypoint untag [name] [tag]",
		"		removies the specified tag"
	};
	

	for (const auto& r : Help) { std::cout << r << '\n'; }
}

void untag(std::string path,std::string name, std::string tag) {
	std::vector<std::vector<std::string>> waypoint;
	std::ifstream read(path);
	std::string line;
	std::vector<std::string> rows;
	std::string row;

	while(getline(read, line)) {
		waypoint = splitWaypoint(line);

		if (waypoint[0][0] == name) {
			row = waypoint[0][0] + "|" + waypoint[1][0] + "|";
			if (tag != "") {
				if (!waypoint[2].empty()) { for (const auto& t : waypoint[2]) { if (t != tag) {  row += t; row += "|"; }}}	
			}
		       rows.push_back(row);
		}
		else { rows.push_back(line); } 
	}
	std::ofstream write(path);
	for (const auto& r : rows) { write << r << '\n'; }
	write.close();

}

void link(std::string name, std::string location) {
	std::ofstream write(std::string(getenv("HOME")) + "/.waypoint/link.txt", std::ios::app);
	write << name + "|" << location << "|" << '\n';
	write.close();
}

void rename(std::string path, std::string name, std::string newName) {
	std::ifstream read(path);
	std::vector<std::vector<std::string>> waypoint;
	std::string line;
	std::string row;
	std::vector<std::string> rows;

	while(getline(read, line)) {
		waypoint = splitWaypoint(line);
		row = "";
		if (name == waypoint[0][0]) {
			row += newName; row += "|";
			row += waypoint[1][0]; row += "|";
			if (!waypoint[2].empty()) { for(const auto& tag : waypoint[2]) { row += tag; row += "|"; } }
			rows.push_back(row);
		}
		else { rows.push_back(line); }
	}
	std::ofstream write (path);
	for (const auto& r : rows) { write << r << '\n'; }
	write.close();
	throwSuccses("Renamed " + name + "succsesfully to " + newName);
}
