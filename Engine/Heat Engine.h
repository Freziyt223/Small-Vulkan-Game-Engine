// -----------------------------------------------------------------------------------------------------------------
// Includes and defines for whole program

#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <mem.h>
#include <stdbool.h>
#include <dirent.h>
#include <string.h>

// -----------------------------------------------------------------------------------------------------------------
// Dynamic Arrays

typedef struct Array {
  size_t Size;

  union {
    void *Pointer;
    long long *LongInteger;
    double *LongFloat;
    int *Integer;
    float *Float;
    const char **String;
    bool *Boolean;
  };

} Array;

extern Array ArrayCreate(size_t NumberOfElements);

extern void ArrayDestroy(Array *Array);

extern void ArrayResize(Array *Array, size_t NewSize);

#define SmallArray(Type, Size) (Type *)SmallArrayCreate(sizeof(Type), Size)

extern void SmallArrayResize(void **Array, size_t NewSize);

extern void SmallArrayDestroy(void *Array);

extern void *SmallArrayCreate(int SizeOfElement, size_t NumberOfElements);

// -----------------------------------------------------------------------------------------------------------------
// Events

typedef void (*EventFunction)(Array Arguments);

#define MakeEventFunction(Name) void Name(Array Arguments)

extern int RegisterEvent(const char *Name);

extern void RemoveEvent(const char *Name);

extern int TriggerEvent(const char *Name, Array Arguments);

extern void OnEvent(const char *Name, EventFunction Function);

// -----------------------------------------------------------------------------------------------------------------
// Application itself

extern struct Application {
  struct {
    int X, Y;
    int Width, Height;
    char *Title;
    bool IsShown;
  } Window;
  char *Name;
} Application;

extern void StopExecuting(int ExitCode);