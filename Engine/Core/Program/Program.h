// ------------------------------------------------------------------------------------------------------------------------
// In this section we include other files

#include "../Platform/Platform.h"
#include "Defines.h"

// ------------------------------------------------------------------------------------------------------------------------
// In this section we declare variables that will be used later in all the program

typedef struct {
  const char *Title;
  int X, Y, Width, Height;
  WindowType Handle;
} Window;

// ------------------------------------------------------------------------------------------------------------------------
// Here we make our program struct which will hold all needed information

extern struct Program {
  Window Window;
  const char *Name;
} Program;

// ------------------------------------------------------------------------------------------------------------------------
// Functions to controll program

void InitializeProgram(char *args[]);
void UpdateProgram();
void TerminateProgram();

// ------------------------------------------------------------------------------------------------------------------------