// -----------------------------------------------------------------------------------------------------------------
// Includes and defines for example program
// Include API header file
#include "../Engine/Heat Engine.h"
// Setting up an application, it can be done in Initialize function if you want
void KeyPressed(Array Arguments);
void PostQuit(Array Arguments);
int ReachPoint = 0;

// -----------------------------------------------------------------------------------------------------------------
// Functions for the program

/**
 * Function that runs once and should prepare the program,
 * User error handling, see below, that means that not the program itself does
 * error handling, but user.
 */
void Initialize() {
  Application = (struct Application){
    .Name = "Example Program",
    .Window = {
      .Width = 1270,
      .Height = 720,
      .Title = "Example Window",
      .IsShown = true
    }
  };
  printf("Program Started!\n");
  RegisterEvent("Post Quit");
};
/**
 * Here is code that will be called on every program update, loop 
 */
void Update() {
  TriggerEvent("Post Quit", (Array){.Size = 1, .Boolean = &(bool){1}}); 
  OnEvent("Post Quit", &PostQuit);
};
/**
 * DON'T FORGET!
 * This function cleans up everything, everything that you initialized should be cleaned up
 */
void Terminate() {
  RemoveEvent("Post Quit");
}

// Function that will be called on event triggered, 1st variant on how to make event function
void KeyPressed(Array Arguments) {
  if (strcmp(Arguments.String[0], "LMB")) {

    // Even if Array SHOULD be created with dynamic arrays function, but here we can take shortcut, 
    // and not free it later, because this will be cleaned up after function execution automaically,
    // but i highly recommend doing: Array Arguments = ArrayCreate(1);
    //                               Arguments.Boolean[0] = true;
    //                               TriggerEvent("Post Quit", Arguments);

    TriggerEvent("Post Quit", (Array){.Size = 1, .Boolean = &(bool){1}}); 
  }
};

// Function that will terminate Program
MakeEventFunction(PostQuit) {
  printf("Stopping execution!\n");
  StopExecuting(2); // Means program executed successfully
};