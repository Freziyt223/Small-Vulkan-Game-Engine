#include "../Program/Defines.h"
#include "../Dynamic Arrays/Array.h"

typedef void (*EventFunction)(Array Arguments);

int FN1Hash(const char *String);

int InitializeEvents();

void TerminateEvents();

int RegisterEvent(const char *Name);

void RemoveEvent(const char *Name);

int TriggerEvent(const char *Name, Array Arguments);

void OnEvent(const char *Name, EventFunction Function);

void TestEvent(const char *Name);