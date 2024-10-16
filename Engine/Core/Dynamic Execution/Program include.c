#include "../Platform/Platform.h"
#include "../Program/Defines.h"
#include "../Dynamic Arrays/Array.h"
#include <stdio.h>

typedef void (*FunctionType)(void);
HMODULE Dll;

void NoProgramInitialize(void) {
  printf("No Program passed to the engine\n");
};

void NoProgramUpdate(void) {
  printf("No Update function specified in file(s)\n");
};

void NoProgramTerminate(void) {
  printf("No Terminate function specified in file(s)\n");
};

FunctionType UserInitialize = &NoProgramInitialize;

FunctionType UserUpdate = &NoProgramUpdate;

FunctionType UserTerminate = &NoProgramTerminate;

void AddFile(char **Files, const char *File) {
  size_t currentLength = strlen(*Files);
  size_t newLength = currentLength + strlen(File) + 2;
  SmallArrayResize((void **)Files, newLength);
  strcat(*Files, File);
  strcat(*Files, " ");
}

int GetDirrectory(const char *Dirrectory, char **Files) {
  DIR *_Dirrectory = opendir(Dirrectory);
  struct dirent *entry;

  if (_Dirrectory == NULL) {
      return 0;
  }
  while ((entry = readdir(_Dirrectory)) != NULL) {

    char FilePath[strlen(Dirrectory) + entry->d_namlen + 2]; 
    snprintf(FilePath, sizeof(FilePath), "%s/%s.c", Dirrectory, entry->d_name);
    AddFile(Files, FilePath);

  }

  closedir(_Dirrectory);
  return 1;
}

int CompileFiles(char *Files) {
  char *MyCommand = "clang -shared -o ./Compiled/Application.dll -I./Engine/Core -L./Compiled -lCore ";
  size_t commandSize = strlen(MyCommand) + strlen(Files) + 1; // +1 для '\0'
  
  char *Command = SmallArray(char, commandSize);

  strcpy(Command, MyCommand);

  strcat(Command, Files);

  int Code = system(Command);

  SmallArrayDestroy((void *)Command);
    
  return Code;
}

void LoadFiles() {
  Dll = LoadLibraryA("./Compiled/Application.dll");
  
  if (Dll != NULL) {
    UserInitialize = (FunctionType)GetProcAddress(Dll, "Initialize");
    UserUpdate = (FunctionType)GetProcAddress(Dll, "Update");
    UserTerminate = (FunctionType)GetProcAddress(Dll, "Terminate");
  }

  if (UserInitialize == NULL) {
    UserInitialize = &NoProgramInitialize;
  }
  if (UserUpdate == NULL) {
    UserUpdate = &NoProgramUpdate;
  }
  if (UserTerminate == NULL) {
    UserTerminate = &NoProgramTerminate;
  }
}

int InitializeIncludes(int argc, char *args[]) {
  char *Files = SmallArray(char, 1);
  Files[0] = '\0';
  if (args[1] != NULL) {

    const char *Extension = strrchr(args[1], '.');
    if (Extension == NULL) {

      if (GetDirrectory(args[1], &Files) != 1) {
        CompileFiles(Files);
      }

    } else {
      AddFile(&Files, args[1]);
      CompileFiles(Files);
    }

  };
  
  LoadFiles();
  SmallArrayDestroy((void *)Files);
  return 0;
}

void TerminateIncludes() {
  if (Dll != NULL) {FreeLibrary(Dll);}
};
