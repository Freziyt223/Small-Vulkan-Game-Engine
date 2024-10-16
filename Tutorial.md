# File structure and reading the whole project

- [Engine Folder](#EngineFolder)
- [Build Folder](#BuildFolder)
- Compiled folder - folder that countains all compiled versions for the programm, executable, dynamic library or even object files.

## Engine Folder
So, to start, i recommend you follow this method: You start from Heat engine.c,
and see what it includes and uses, and futher and futher, but also this is structure:

- Program folder:
    Contains program struct and methods to keep program alive, this is basically end point for every other files
- Platform folder:
    Functions that prepare platform specific things, like audio, inputs, windowing and other.
- Dynamic Execution folder:
    Here are functions which resolve and parse command line arguments.
- Dynamic Arrays folder:
    Functions for dynamic arrays(arrays that can change size through out the program).
- Events folder:
    Functions for event system, system that can send some information and aquire it in other file, for example press of W button will trigger event that will transfer data for event, and button pressed.
-
    

**This is reading order:**

Heat engine.c -> Program.h, Program.c -> Platform.h, Platform.c -> Parser.c, Events.h, Events.c -> Program Include.h, Program Include.c

## Build Folder
Also there is Build folder, there you can see how building works.
** NOT FINISHED YET **

## Libraries Folder

There are all libraries used, you can also add your own ones