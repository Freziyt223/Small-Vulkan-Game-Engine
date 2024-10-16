// ------------------------------------------------------------------------------------------------------------------------
// In this section we include other files

#include "../Platform/Platform.h"
#include "../Events/Events.h"
#include "Defines.h"

// ------------------------------------------------------------------------------------------------------------------------
// In this section we declare variables that will be used later in all the program

typedef struct {
  char *Title;
  int X, Y, Width, Height;
  WindowType Handle;
  bool IsShown;
} Window;

// ------------------------------------------------------------------------------------------------------------------------
// Here we make our program struct which will hold all needed information

extern struct Program {
  Window Window;
  char *Name;
  struct UserMouse {
    int X, Y;
  } Mouse;
} Program;

// ------------------------------------------------------------------------------------------------------------------------
// Functions to controll program

void InitializeProgram(int argc, char *args[]);
void UpdateProgram();
void TerminateProgram();
void StopExecuting(int Code);

// ------------------------------------------------------------------------------------------------------------------------