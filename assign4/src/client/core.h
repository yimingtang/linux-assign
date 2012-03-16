#ifndef CORE_H
#define CORE_H
#include "common.h"

typedef bool (*HANDLE_FUNC)();

HANDLE_FUNC find_handler(char *name);

#endif
