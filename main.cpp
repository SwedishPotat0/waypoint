#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <filesystem>

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

int main(int argc, char* argv[]) {
	bool dir = checkDir();
	if (dir) { throwSuccses("Succseded to creat directory & config file"); return 0;}
	else if (!dir) { if (argc < 3) { throwError("It needs to be atleast 2 arguments"); return 1;}
		 
	std::string arg = argv[1];
	std::string name = argv[2];
	std::string prg = getEditor();
	std::string path = std::string(getenv("HOME")) + "/.waypoint/waypoint.txt";

	if (arg == "jump") {
		// Put code here
	}
	if (arg == "open") {	
		std::string location;
		std::ifstream read(path);
		std::string line;
 
		while (getline(read, line)) { 
			std::string word = "";
			bool nameTrue = false;
			for (size_t i = 0; i < line.length(); i++) {
				if (line[i] == '|') { if (!word.empty()) { if (word == name) {
					nameTrue = true;
					continue;			
				} } } else {word += line[i];}
				if (nameTrue) { if(line[i] == '|'){break;} location += line[i]; }
			}}	
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
 
		while (getline(read, line)) { 
			std::string word = "";
			bool nameTrue = false;
			if (!row.empty()) {break;}
			for (size_t i = 0; i < line.length(); i++) {
				if (line[i] == '|') { if (!word.empty()) { if (word == name) {
					nameTrue = true;
					row += word;
					continue;			
				} } } else {word += line[i];}
				if (nameTrue) {row += line[i];}
			}index++;}
		row += tag;
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
 	
		while (getline(read, line)) { 
			std::string word = "";
			bool nameTrue = false;
			for (size_t i = 0; i < line.length(); i++) {
				if (line[i] == '|') { if (!word.empty()) { if (word == name) {
					nameTrue = true;
					continue;			
				} } } else {word += line[i];}
				if (nameTrue) { if(line[i] == '|'){break;} location += line[i]; }
			}}
		std::cout << location;
	}
}}
