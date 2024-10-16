$CoreFiles = Get-ChildItem -Path .\Engine\Core -Recurse -Filter *.c | ForEach-Object { $_.FullName }
clang -Wall -g $CoreFiles -shared -o .\Compiled\Core.dll

clang -g -Wall ".\Engine\Heat engine.c" -L".\Compiled" -l"Core" -o ".\Compiled\Heat.exe"