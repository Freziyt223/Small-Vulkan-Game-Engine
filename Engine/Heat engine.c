// ------------------------------------------------------------------------------------------------------------------------
/**
 * Information about software:
 *
 */
// ------------------------------------------------------------------------------------------------------------------------
// Libraries and includes section, those are the feature program uses, basically, you can just put everything in one file,
// but that wouldn't have been a good one to read and understand, so everything is split up into multiple files.

#include "Core/Program/Program.h"

// ------------------------------------------------------------------------------------------------------------------------
// File structure is as follows:
// .(this folder) - files that are being runned or made for the user to use, and not the program, like this file.
// Core - files that contain basic functions, structures and some variables for program/engine to work.
// basically not everything is implemented yet, but i'm working on it.
// ------------------------------------------------------------------------------------------------------------------------
// Main function, that is the entry point of the program, where program begins to execute.
int main(int argc, char* argv[]) { // argc and argv are the arguments passed to the program from command line
  InitializeProgram(argv);
  UpdateProgram();
  TerminateProgram();

  return 0;
};
// ------------------------------------------------------------------------------------------------------------------------