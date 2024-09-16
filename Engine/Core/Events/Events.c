#include "Events.h"
#include <stdbool.h>

struct MyEvents {
  int Size;
  struct Event {
    char *Name;
    Array Data;
  } *Event;
} Events;

int FN1Hash(const char *String) {
  int Hash = 2166136261u;
  while (*String) {
    Hash ^= (unsigned char)(*String++);
    Hash *= 16777619u;
    
  }
  return Hash % Events.Size;
};

int InitializeEvents() {
  Events.Size = 10;
  Events.Event = SmallArray(struct Event, Events.Size);
  if (Events.Event == NULL) {
    return 1;
    printf("Events is null!\n");
  }
  return 0;
};

void TerminateEvents() {
  SmallArrayDestroy(Events.Event);
};

int RegisterEvent(const char *Name) {
  int Hash = FN1Hash(Name);

  if (!Events.Event[Hash].Name) {

  } else {
    struct MyEvents NewEvents;
    NewEvents.Size = Events.Size + 10;
    NewEvents.Event = SmallArray(struct Event, NewEvents.Size);
    if (NewEvents.Event == NULL) {
      return 1;
      printf("NewEvents is null!\n");
    }
    
    for (int i = 0; i < Events.Size; i++) {
      if (*Events.Event[i].Name == '\0') {
        if (!(NewEvents.Event[FN1Hash(Events.Event[i].Name)].Data.Boolean[0] = Events.Event[i].Data.Boolean[0])) {
          return 2;
          printf("Couldn't reassign events\n");
        };

      }
    };
    SmallArrayDestroy(Events.Event);
    Events.Event = SmallArray(struct Event, NewEvents.Size);
    if (Events.Event == NULL) {
      return 1;
      printf("Couldn't recreate Events in RegisterEvent function\n");
    }
    memcpy(Events.Event, NewEvents.Event, NewEvents.Size);
    SmallArrayDestroy(NewEvents.Event);
  };
  Events.Event[Hash].Name = (char *)Name;
  if (Events.Event[Hash].Name == Name) {
    return 0;
  } else {return 3;};
};

void RemoveEvent(const char *Name) {
  int Hash = FN1Hash(Name);

  Events.Event[Hash].Name = "\0";
  ArrayDestroy(&Events.Event[Hash].Data);
};

int TriggerEvent(const char *Name, Array Arguments) {
  int Hash = FN1Hash(Name);
  
  if (Events.Event[Hash].Name) {
    Events.Event[Hash].Data = Arguments;
    return 0;
  } else {return 1;}

};

void OnEvent(const char *Name, EventFunction Function) {
  int Hash = FN1Hash(Name);

  if (Events.Event[Hash].Name && Events.Event[Hash].Data.Size != 0) {
    Function(Events.Event[Hash].Data);
    ArrayDestroy(&Events.Event[Hash].Data);
  };
};

void TestEvent(const char *Name) {
  if (Events.Event[FN1Hash(Name)].Name == Name) {printf("Test passed!\n");} else {printf("Test Failed!\n");};
};