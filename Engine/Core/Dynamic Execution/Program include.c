#include "Program include.h"
#include "../Platform/Platform.h"
#include "../Program/Defines.h"
#include "../Dynamic Arrays/Array.h"

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
        const char *Extension = strrchr(entry->d_name, '.');
        if (Extension != NULL && strcmp(Extension, ".c") == 0) {
            char FilePath[strlen(Dirrectory) + entry->d_namlen]; 
            snprintf(FilePath, sizeof(FilePath), "%s/%s", Dirrectory, entry->d_name);
            AddFile(Files, FilePath);
        }
    }

    closedir(_Dirrectory);
    return 1;
}

int CompileFiles(char *Files) {
    size_t commandSize = 41 + strlen(Files);
    char *Command = SmallArray(char, commandSize);
    strcpy(Command, "clang -shared -o Compiled/Libraries.dll ");
    strcat(Command, Files);
    int Code = system(Command);
    SmallArrayDestroy((void *)Command);
    return Code == 0;
}

void LoadFiles() {
    HMODULE Dll = LoadLibraryA("Compiled/Libraries.dll");
    if (Dll == NULL) {
        return;
    }

    FunctionType Function = (FunctionType)GetProcAddress(Dll, "SomeFunc");
    if (Function == NULL) {
        FreeLibrary(Dll);
        return;
    }

    Function();
    FreeLibrary(Dll);
}

int InitializeIncludes(char *args[]) {
    char *Files = SmallArray(char, 1);
    Files[0] = '\0';

    if (GetDirrectory(args[1], &Files)) {
        if (CompileFiles(Files)) {
            LoadFiles();
            SmallArrayDestroy((void *)Files);
            return 1;
        }
    }

    SmallArrayDestroy((void *)Files);
    return 0;
}
