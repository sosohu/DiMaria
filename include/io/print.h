#ifndef __PRINT__MSG__
#define __PRINT__MSG__

#include <stdio.h>
#include "comm.h"

#define NONE         "\033[m"
#define RED          "\033[0;32;31m"
#define LIGHT_RED    "\033[1;31m"
#define GREEN        "\033[0;32;32m"
#define LIGHT_GREEN  "\033[1;32m"
#define BLUE         "\033[0;32;34m"
#define LIGHT_BLUE   "\033[1;34m"
#define DARY_GRAY    "\033[1;30m"
#define CYAN         "\033[0;36m"
#define LIGHT_CYAN   "\033[1;36m"
#define PURPLE       "\033[0;35m"
#define LIGHT_PURPLE "\033[1;35m"
#define BROWN        "\033[0;33m"
#define YELLOW       "\033[1;33m"
#define LIGHT_GRAY   "\033[0;37m"
#define WHITE        "\033[1;37m"

// defined pring msg
#ifdef DEBUG
	#define PRINT_MSG(format, args...) \
	{\
		printf(BLUE "%s %s %d :  " NONE, __FILE__, __func__, __LINE__);\
		printf(BLUE format NONE"\n", ##args);\
	}

	#define PRINT_ERROR(format, args...) \
	{\
		printf(RED "%s %s %d :  " NONE, __FILE__, __func__, __LINE__);\
		printf(RED format NONE"\n", ##args);\
	}
#else
	#define PRINT_MSG(format, args...)
	#define PRINT_ERROR(format, args...) 
#endif

#endif
