// ------------------------------------------------------------------------------------------------------------------------
// Includes and defines

#include "Array.h"

// ------------------------------------------------------------------------------------------------------------------------
// Functions and variables that will be used futher in program

/** 
 * Function that creates array with specified number of elements
 * @param NumberOfElements enter number of elements in the array
 * @returns Array type(check at the ./Array.h file) 
 * */ 
Array ArrayCreate(size_t NumberOfElements) {

  Array Header = {.Size = 8 * NumberOfElements}; // Making an empty array 
  Header.LongInteger = calloc(NumberOfElements, 8); // Allocating memory for our array
  if (Header.LongInteger == NULL) { // If it wasn't successfull
    printf("Failed to allocate memory for dynamic array"); // Tell about it in a console
    return (Array){
      .Size = 0,
      .Boolean = 0
    }; // And Return empty Array
  }

  return Header;
};
/**
 * Function that removes an array when no longer usefull or needed
 * @param Array Specify pointer to the Array
 * @returns Nothing
 */
void ArrayDestroy(Array *Array) {
  if(Array->Size == 0) { // Size is always not zero when creating Array, so when it's opposite, Array isn't valid
    printf("Array is empty or non existing"); // Tell about it in a console
    return; // End execution of this function
  }
  free(Array->LongInteger); // If Array is valid, clean up it's constituents,
  Array->LongInteger = NULL; // make so data inside of the Array can not be longer used, to prevent accidental and undefined behaviour
  Array->Size = 0; // Setting Array size to 0 so Array becomes "empty"
};

/**
 * Function that resizes Array while keeping it's insidings, 
 * @param Array pointer to an Array that has to be resized
 * @param NewSize value of new size in bytes(not bits)
 * @returns Nothing
 */
void ArrayResize(Array *Array, size_t NewSize) {
  Array->LongInteger = (long long *)realloc(Array->LongInteger, NewSize); // Reallocating memory space for our data with new size
  Array->Size = NewSize; // Remembering our size
}

void *SmallArrayCreate(int SizeOfElement, size_t NumberOfElements) {
  void *Array = calloc(NumberOfElements, SizeOfElement);
  return Array;
}

void SmallArrayResize(void **Array, size_t NewSize) {
  *Array = realloc(*Array, NewSize);
}

void SmallArrayDestroy(void *Array) {
  free(Array);
  Array = NULL;
}
// ------------------------------------------------------------------------------------------------------------------------