#pragma once
#include "../Program/Defines.h"
/**
 * This is struct that holds information and data
 * of an array
 * First thing it does contain is Size which is capacity(whole space that is given to this array) in bytes;
 * Second thing it does contain is an array of elements(they all are the same), they do act just like an array of given type and you can easily switch them;
 */
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

Array ArrayCreate(size_t NumberOfElements);

void ArrayDestroy(Array *Array);

void ArrayResize(Array *Array, size_t NewSize);

#define SmallArray(Type, Size) (Type *)SmallArrayCreate(sizeof(Type), Size)

void SmallArrayResize(void **Array, size_t NewSize);

void SmallArrayDestroy(void *Array);

void *SmallArrayCreate(int SizeOfElement, size_t NumberOfElements);

//TODO: implement some sort of size storage, to see the which part of the program uses the most of user given memory, or has leaks/overflows