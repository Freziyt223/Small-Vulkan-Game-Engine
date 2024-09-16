// ------------------------------------------------------------------------------------------------------------------------
// Here we include other files

#include "../Platform/Platform.h"
#include "../Dynamic Execution/Program include.h"
#include "../Events/Events.h"
#include "Defines.h"

// ------------------------------------------------------------------------------------------------------------------------
// Those are the structs that whole program will use as the container

typedef struct Window {
  const char *Title;
  int X, Y, Width, Height;
  WindowType Handle;
} Window;
struct Program {
  Window Window;
  const char *Name;
} Program = {
  .Window = {
    .X = 0,
    .Y = 0,
    .Width = 560,
    .Height = 560,
    .Title = "Some game window",
  },
  .Name = "Some game program"
};
// ------------------------------------------------------------------------------------------------------------------------
// Functions to controll program

/**
 * Function that initializes all program features for startup
 * Takes no arguments and doesn't return
 */
void InitializeProgram(char *args[]) {
  InitializeEvents();
  InitializeIncludes(args);
  InitializePlatform();
  UserInitialize();
}
/**
 * Function updates program many many times and plays/checks for events
 * Takes no arguments and doesn't return
 */
void UpdateProgram() {
  while (UpdatePlatform() == 1) {
    UserUpdate();
  };
}
/**
 * Function that terminates and cleans up program after successful execution
 * Takes no arguments and doesn't return
 */
void TerminateProgram() {
  InitializeEvents();
  TerminatePlatform();
  UserTerminate();
  TerminateIncludes();
  remove("./Application.dll");
}
// ------------------------------------------------------------------------------------------------------------------------