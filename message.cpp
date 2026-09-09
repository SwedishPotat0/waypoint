#include <iostream>
#include <string>

#include "message.h"

const char* RESET = "\033[0m";
const char* RED = "\033[31m";
const char* GREEN = "\033[32m";

void throwError(std::string errorMSG) { std::cout << RED << "Error: " << RESET; std::cout << errorMSG << '\n'; }
void throwSuccses(std::string succsesMSG) {std::cout << GREEN << succsesMSG << RESET << '\n';}

