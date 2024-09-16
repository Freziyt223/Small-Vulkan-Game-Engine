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
  size_t commandSize = 41 + strlen(Files);
  char *Command = SmallArray(char, commandSize);
  strcpy(Command, "clang -shared -o Application.dll ");
  strcat(Command, Files);
  int Code = system(Command);
  SmallArrayDestroy((void *)Command);
  return Code == 0;
}

void LoadFiles() {
  Dll = LoadLibraryA("Application.dll");
  if (Dll == NULL) {
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

int InitializeIncludes(char *args[]) {
  char *Files = SmallArray(char, 1);
  Files[0] = '\0';
  if (args[1] != NULL) {
    const char *Extension = strrchr(args[1], '.');
    if (Extension == NULL) {
      if (GetDirrectory(args[1], &Files)) {
        if (!CompileFiles(Files)) {
          return 1;
        }
      }
    } else {
      AddFile(&Files, args[1]);
      if (!CompileFiles(Files)) {
        return 1;
      }
    }
  };
  LoadFiles();
  SmallArrayDestroy((void *)Files);
  return 0;
}

void TerminateIncludes() {
  FreeLibrary(Dll);
};
