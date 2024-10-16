// ------------------------------------------------------------------------------------------------------------------------
// Here we include other files

#include "../Platform/Platform.h"
#include "../Dynamic Execution/Program include.h"
#include "../Events/Events.h"
#include "Defines.h"
struct Application {
  struct {
    int X, Y;
    int Width, Height;
    char *Title;
    bool IsShown;
  } Window;
  char *Name;
} Application;

static bool IsExecuting = true;

// ------------------------------------------------------------------------------------------------------------------------
// Those are the structs that whole Program will use as the container

typedef struct Window {
  char *Title;
  int X, Y, Width, Height;
  WindowType Handle;
  bool IsShown;
} Window;

// Static type(struct Program) Program, that means that Program struct can only be changed by functions from this file.
const struct Program {
  Window Window;
  char *Name;
  struct UserMouse {
    int X, Y;
  } Mouse;
} DefaultProgram = {
  .Window = {
    .X = 0,
    .Y = 0,
    .Width = 560,
    .Height = 560,
    .Title = "Some game window",
    .IsShown = false
  },
  .Name = "Some game Program"
};
// Actual Program struct for all program
struct Program Program;

// ------------------------------------------------------------------------------------------------------------------------
// Functions to controll Program

void RegisterProgramEvents();

/**
 * Function that initializes all Program features for startup
 * Takes no arguments and doesn't return
 */
void InitializeProgram(int argc, char *args[]) {
  Program = DefaultProgram;
  InitializeEvents();
  RegisterProgramEvents();
  InitializeIncludes(argc, args);
  InitializePlatform();
  UserInitialize();
}
/**
 * Function updates Program many many times and plays/checks for events
 * Takes no arguments and doesn't return
 */
void UpdateProgram() {
  Program.Window.X = Application.Window.X ? Application.Window.X : DefaultProgram.Window.X;
  Program.Window.Y = Application.Window.Y ? Application.Window.Y : DefaultProgram.Window.Y;
  Program.Window.Width = Application.Window.Width ? Application.Window.Width : DefaultProgram.Window.Width;
  Program.Window.Height = Application.Window.Height ? Application.Window.Height : DefaultProgram.Window.Height;
  Program.Window.Title = Application.Window.Title ? Application.Window.Title : DefaultProgram.Window.Title;
  Program.Window.IsShown = Application.Window.IsShown ? Application.Window.IsShown : DefaultProgram.Window.IsShown;
  Program.Name = Application.Name ? Application.Name : DefaultProgram.Name;

  while (UpdatePlatform() == 0 && IsExecuting == true) {
    UserUpdate();
  };
}

/**
 * Function that terminates and cleans up Program after successful execution
 * Takes no arguments and doesn't return
 */
void TerminateProgram() {
  TerminateEvents();
  TerminatePlatform();
  UserTerminate();
  TerminateIncludes();
  remove("./Compiled/Application.dll");
}

void StopExecuting(int Code) {
  IsExecuting = false;
  TerminateProgram();
  exit(Code);
};

void RegisterProgramEvents() {
  RegisterEvent("Key Pressed");
};
// ------------------------------------------------------------------------------------------------------------------------