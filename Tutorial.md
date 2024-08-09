# File structure and reading the whole project

- [Engine Folder](#EngineFolder)
- [Build Folder](#BuildFolder)

## Engine Folder
So, to start, i recommend you follow this method: You start from Heat engine.c,
and see what it includes and uses, and futher and futher, but also this is structure:

- Program folder:
    Contains program struct and methods to keep program alive, this is basically end point for every other files
- Platform folder:
    Prepares platform specific things, like audio, inputs, windowing and other
- Argument parser folder:
    Here is where command line arguments parsing begins

this is reading order:

Heat engine.c -> Program.h, Program.c -> Platform.h, Platform.c -> Parser.c, Parser.h and Functions.h file.

## Build Folder
Also there is Build folder, there you can see how building works.
** NOT FINISHED YET **

## Libraries Folder

There are all libraries used, you can also add your own ones

## Compiled Folder

Compiled executables of this application(for now only for windows because early development)