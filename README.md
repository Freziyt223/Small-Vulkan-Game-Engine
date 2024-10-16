Hello, this is Freziyt223, and what you are looking at is a simple C game engine.
Hope on your feadback.

# Table of contest:
- [English](###English) (For now only translation language, Ukrainian will be in future)
  - [Plans](##Plans)
  - [How to work with it](##Howto)
    - [Usage](#Usage)
    - [Redistribution](#Redistribution)
    - [How to contribute](#Contribution)
  - [How to support this project](##Howtosupport)
  - [Examples](##Examples)
  - [Instalation](##Instalation)
- [Ukrainian](###Ukrainian) Not made yet

### English
## Plans

So, what do i expect this to be in future? As a development platform capable of modifying, i want to make something that can be used to make anything and as you want.
For now big goal is to make it go to rendering on a made module, for that i'll make Vulkan and OpenGL which also be fully free to use and maybe documented(i don't have much time)

## Howto

# Usage
**For now** to use the engine you have to have clang compiler on your system(or simply modify the engine to work with any compiler you want, ./Engine/Core/Dynamic Execution/Program include.c:55)
So you make your C files, any directory is ok, you SHOULD have 
```c
void Initialize() {}; // This function will run before other and once, made for you to initialize variables
void Update() {}; // Will start updating program, will be run untill you tell program to stop
void Terminate() {}; // When you initialize something, you have to remove it, remove things you've made here
```
functions, but you can also not use them.
You should use header file provided by the engine, to use functions already implemented in it, path is ./Engine/Heat engine.h

# Redistribution
As i mentioned earlier, you can modify engine to make it work on yor system, you add yourself to the authors, but please keep me there:), also you can post your modifications online, users may like it and so i may,
you can add new license for your project and other stuff, also you can make working executable without help of an engine executor(A.K.A Heat.exe) you can compile your program files with Core.dll and some C file with main fucnction, example is engine's ./Engine/Heat engine.c 
```c
#include "Core/Program/Program.h"
int main(int argc, char* argv[]) { // argc and argv are the arguments passed to the program from command line
  InitializeProgram(argc, argv);
  UpdateProgram();
  TerminateProgram();
};
```
You can also mark these functions like extern and not use ./Engine/Core/Program/Program.h header file
# Contribution
You can add issues/forks on this, write me a message for contribution request (for now no socials). Also i do need someone to showcase features of this program as i don't have much time, if you can please write me a letter

## How to support

For now best thing you can do is to test features of this engine and give a feedback, tell other people and make modules, also if do really want to support me financial, write me a private letter we'll talk about this as i don't have registered donation platforms like Patreon or Buy Me A Coffe

## Examples

For examples you can go to ./Examples folder and see how to use the features of the engine, this is example program that utilizes all functions of the engine with comments:
```c
#include "../Engine/Heat engine.h" // header which contains declarations of engine functions

// This is a macro that will make a PostQuit function, which will have structure like void PostQuit(Array Arguments) with {} that you enter futher
MakeEventFunction(PostQuit) {
  printf("Stopping execution!\n");
  StopExecution(0); // 0 means no errors
};

/**
 * Function that runs once and should prepare the program,
 * User error handling, see below, that means that not the program itself does
 * error handling, but user.
 */
void Intialize() {
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
  Array Arguments = ArrayCreate(1); // Making dynamic array for arguments that we will give to the program
  Arguments.Boolean[0] = (bool)1; // setting 0st element to be 1, this can be interpreted as boolean, integer, long integer, double, float, char if you want. If you still have questions look at ./Engine/Heat engine.h declaration
  TriggerEvent("Post Quit", Arguments); // Triggering event, arguments should be Array type 
  OnEvent("Post Quit", &PostQuit); // One time launch function that will check if arguments are passed to event, if so, it will launch function you specify
}

/**
 * DON'T FORGET!
 * This function cleans up everything, everything that you initialized should be cleaned up
 */
void Terminate() {
  RemoveEvent("Post Quit");
}

```


## Instalation

For now this whole packed executable isn't ready, what you can do is just download it from github/clone it with git and just grab files from ./Compiled

### Ukrainian
