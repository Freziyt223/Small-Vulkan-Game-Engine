#pragma once
#include "../Program/Defines.h"
/**
 * This is struct that holds information and data
 * of an array
 * 
 */
typedef struct Array {
  size_t Size;

  union {
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