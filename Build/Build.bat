@ECHO OFF
SETLOCAL EnableDelayedExpansion
chcp 65001
if not exist "%cd%\Build and compile" (
    cd /d ..
)
REM All c files in the current directory
SET "FileNames="
FOR /R "Engine" %%f in (*.c) DO (
    echo %%f
    SET "FileNames=!FileNames! "%%f""
)

REM Initialize variables
SET "Argument=%1"
SET "BuildType=%2"
SET "Compiler="
SET "CompilerFlags="
SET GCC=0
SET CLANG=0
SET MSVC=0
for %%I in (gcc clang cl) do (
    where /q %%I > nul 2>nul
    if not errorlevel 1 (
        SET "Compiler=%%I"
        if "%%I" == "gcc" (
            SET GCC=1
        ) else if "%%I" == "clang" (
            SET CLANG=1
        ) else if "%%I" == "cl" (
            SET MSVC=1
        )
    )
)

REM Getting compilers list
if NOT "!Argument!" == "" (
    if "!Argument!" == "-GCC" (
        if "!GCC!" == "1" (
            SET "Compiler=gcc"
        )
    ) else if "!Argument!" == "-Clang" (
        if "!CLANG!" == "1" (
            SET "Compiler=clang"
        )
    ) else if "!Argument!" == "-MSVC" (
        if "!MSVC!" == "1" (
            SET "Compiler=cl"
        )
    ) else if "!Argument!" == "-Debug" (
        SET "CompilerFlags=!CompilerFlags! -v"
    )
)
if NOT "!BuildType!" == "" (
    if "!BuildType!" == "-Debug" (
        SET "CompilerFlags=!CompilerFlags! -v"
    )
)
echo Compiling with !Compiler!

REM Setting compiler flags based on compiler type
SET "Includes="
SET "LibraryPaths="
SET "LibraryNames="
SET "IncludeFlag="
SET "LibraryPathFlag="
SET "LibraryFlag="
REM Setting compiler flags based on compiler type
if "!Compiler!" == "gcc" (
    SET "CompilerFlags=!CompilerFlags! -std=c99 -Wall -g"
    SET "IncludeFlag=-I"
    SET "LibraryPathFlag=-L"
    SET "LibraryFlag=-l"
) else if "!Compiler!" == "clang" (
    SET "CompilerFlags=!CompilerFlags! -std=c99 -Wall -g -Isrc"
    if "!GCC!" == "1" (
        SET "CompilerFlags=!CompilerFlags! --target=x86_64-pc-windows-gnu"
    ) else if "!MVSC!" == "1" (
        SET "CompilerFlags=!CompilerFlags! -target x86_64-pc-windows-msvc"
    )

    SET "IncludeFlag=-I"
    SET "LibraryPathFlag=-L"
    SET "LibraryFlag=-l"
)

REM Setting library paths and names based on compiler type
for /D %%I in (Libraries\*) do (
    if "%%~nI" == "GLFW" (
        SET "Includes=!Includes! %IncludeFlag% Libraries\%%~nI\include"
        SET "LibraryPaths=!LibraryPaths! %LibraryPathFlag% Libraries\%%~nI\lib-mingw-w64"
        SET "LibraryNames=!LibraryNames! !LibraryFlag! glfw3 !LibraryFlag! gdi32"
    )
    if "%%~nI" == "Vulkan" (
        SET "Includes=!Includes! !IncludeFlag! Libraries\%%~nI\Include"
        SET "LibraryPaths=!LibraryPaths! !LibraryPathFlag! Libraries\%%~nI\Lib"
        SET "LibraryNames=!LibraryNames! !LibraryFlag! vulkan-1"
    )
    if "%%~nI" == "Lua" (
        SET "Includes=!Includes! !IncludeFlag! Libraries\%%~nI\include"
        SET "LibraryPaths=!LibraryPaths! !LibraryPathFlag! Libraries\%%~nI"
        SET "LibraryNames=!LibraryNames! !LibraryFlag! lua54"
    )
)
REM Compiling using selected compiler and flags
!Compiler! !CompilerFlags! !FileNames! !Includes! !LibraryPaths! !LibraryNames! -o "Compiled\HEAT"

ENDLOCAL
pause