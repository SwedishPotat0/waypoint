#ifndef command_H
#define command_H

#include <string>

void tag(std::string path, std::string name, std::string tag);
int list(std::string path, std::string name, char** argv, int argc);
void remove(std::string path, std::string name);
void getPath(std::string path, std::string name);
void init();
void jump(std::string path, std::string name);
void add(std::string path, std::string name, char** argv);
void open(std::string path, std::string name, std::string prg);

#endif
