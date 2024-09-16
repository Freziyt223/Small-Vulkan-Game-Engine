#pragma once
#include <stdio.h>

typedef void (*FunctionType)(void);

extern FunctionType UserInitialize;
extern FunctionType UserUpdate;
extern FunctionType UserTerminate;

int InitializeIncludes(char *args[]);

void TerminateIncludes();