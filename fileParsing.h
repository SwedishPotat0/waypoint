#ifndef fileParsing_H
#define fileParsing_H

#include <vector>
#include <string>

void makeConfig();
bool checkDir();
std::vector<std::vector<std::string>> splitWaypoint(std::string waypoint);
std::string getEditor();
std::string trimLocation(std::string location);
bool checkLocal();

#endif
