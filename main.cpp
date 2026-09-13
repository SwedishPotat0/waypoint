#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <filesystem>
#include <vector>

#include "fileParsing.h"
#include "command.h"
#include "message.h"

int main(int argc, char* argv[]) {
	bool dir = checkDir();
	if (dir) { throwSuccses("Succseded to creat directory & config file"); return 0;}
	else if (!dir) { if (argc < 2) { throwError("It needs to be atleast 1 arguments"); return 1;}
		 
	std::string arg = argv[1];
	std::string name; if (argc > 2) {name = argv[2];} else {name = "";}
	std::string prg = getEditor();
	std::string path = std::string(getenv("HOME")) + "/.waypoint/waypoint.txt";

	if (arg == "jump") { jump(path, name); }
	if (arg == "open") { open(path, name, prg); }
	if (arg == "add" && argc == 4) { add(path, name, argv); } else if (arg == "add") { throwError("add needs 3 arguments"); return 1;}
	if (arg == "tag" && argc == 4) { tag(path, name, argv[3]); } else if (arg == "tag") { throwError("tag needs 3 arguments"); return 1;}
	if (arg == "list") { return list(path, name, argv, argc); }
	if (arg == "getPath") { getPath(path, name); }
	if (arg == "remove") { remove(path, name); }
	if (arg == "init") { init(); }
	}
}
