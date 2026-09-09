#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "command.h"
#include "fileParsing.h"
#include "message.h"

void tag(std::string path, std::string name, std::string tag) {
	std::string line;
	std::string row;
	std::vector<std::string> rows;
	std::vector<std::string> waypoint;
	std::string location;
	std::ifstream read(path);

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

}

int list(std::string path, std::string name, char** argv, int argc) {
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
	return 0;
}
