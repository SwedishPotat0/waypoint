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
	std::string path; if (checkLocal()) { path = ".waypoint/waypoint.txt"; } else { path = std::string(getenv("HOME")) + "/.waypoint/waypoint.txt"; } 
	if (arg == "jump") { jump(path, name); }
	else if (arg == "open") { open(path, name, prg); }
	else if (arg == "add" && argc == 4) { add(path, name, argv); } else if (arg == "add") { throwError("add needs 3 arguments"); return 1;}
	else if (arg == "tag" && argc == 4) { tag(path, name, argv[3]); } else if (arg == "tag") { throwError("tag needs 3 arguments"); return 1;}
	else if (arg == "list") { return list(path, name, argv, argc); }
	else if (arg == "getPath") { getPath(path, name); }
	else if (arg == "remove") { remove(path, name); }
	else if (arg == "init") { init(); }
	else if (arg == "help") { help(); }
	else if (arg == "untag") { if(argc == 3){ untag(path, name); } else if(argc == 4) { untag(path, name, argv[3]); } }
	else if (arg == "link") { if (argc == 4) { link(name, argv[3]); } else { throwError("Not enought arguments for command link"); }}
	else if (arg == "rename") { if (argc == 4) { rename(path, name, argv[3]); } else { throwError("Not enought arguments for rename"); } }
	else {throwError("'" + arg + "' is a unkown command, for seeing avalibale operations run 'help'");}
	}
}
