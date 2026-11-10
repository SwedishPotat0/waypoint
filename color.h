#ifndef color_H
#define color_H

enum color : int {
	RESET = 0,
	RED = 1,
	GREEN = 2,
	YELLOW = 3,
	BLUE = 4,
	COLOR_COUNT
};

static const char* const colors[COLOR_COUNT] = { "\033[0m", "\033[31m", "\033[32m", "\033[33m", "\033[34m"};
inline const char* colorNames[COLOR_COUNT] = { "reset", "red", "green", "yellow", "blue" };

#endif
