#ifndef command_H
#define command_H

#include <string>

void tag(std::string path, std::string name, std::string tag);
int list(std::string path, std::string name, char** argv, int argc);

#endif
