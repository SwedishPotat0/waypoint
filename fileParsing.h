#ifndef fileParsing_H
#define fileParsing_H

#include <vector>
#include <string>

void makeConfig();
bool checkDir();
std::vector<std::vector<std::string>> splitWaypoint(std::string waypoint);
std::string getEditor();
bool checkLocal();

#endif
