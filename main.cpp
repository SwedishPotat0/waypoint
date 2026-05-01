#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <filesystem>

const char* RESET = "\033[0m";
const char* RED = "\033[31m";
const char* GREEN = "\033[32m";

void throwError(std::string errorMSG) { std::cout << RED << "Error: " << RESET; std::cout << errorMSG << '\n'; }

void checkDir() {
	std::filesystem::path dir = std::string(getenv("HOME")) + "/.waypoint";
	if (!std::filesystem::exists(dir)) { std::filesystem::create_directory(dir); }
}

int main(int argc, char* argv[]) {
	checkDir();

	if (argc < 3) { throwError("It needs to be atleast 2 arguments"); return 1;}
		 
	std::string arg = argv[1];
	std::string name = argv[2];
	std::string prg = "vim";
	std::string path = std::string(getenv("HOME")) + "/.waypoint/waypoint.txt";

	if (arg == "jump") {
		// Put code here
	}
	if (arg == "open") {	
		std::string location;
		std::ifstream read(path);
		std::string line;

		bool nameTrue = false;
		while (getline(read, line)) { 
			std::string word = "";
			for (size_t i = 0; i < line.length(); i++) {
				if (line[i] == ' ') { if (!word.empty()) { if (word == name) {
					nameTrue = true;			
				} } } else {word += line[i];}
				if (nameTrue) { location += line[i]; }
			}}	
		std::string cmd = prg + " " + location;
		system(cmd.c_str());
	}
	if (arg == "add" && argc == 4) {
		std::string file = argv[3];
		std::ofstream write(path, std::ios::app);
		write << name << " " << file << " " << '\n';
		write.close();
	} else if (arg == "add") { throwError("add needs 3 arguments"); return 1;}
	if (arg == "tag" && argc == 4) {
		// Put code here
	} else if (arg == "tag") { throwError("tag needs 3 arguments"); return 1;}
	if (arg == "list") {
		std::ifstream read(path);
		std::string line;
		while (getline(read, line)) { std::cout << line << std::endl; }
	}
}
