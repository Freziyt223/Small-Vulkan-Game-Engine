#pragma once
#include <Windows.h>

typedef void (*FunctionType)(void);

extern FunctionType UserInitialize;
extern FunctionType UserUpdate;
extern FunctionType UserTerminate;

int InitializeIncludes(int argc, char *args[]);

void TerminateIncludes();