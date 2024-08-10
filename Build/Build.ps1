# MSVC is not supported yet. Sorry!

# Usage: Build.ps1 (options...)[-Compiler <gcc|clang|cl>] [-Presentation <Normal|Debug>] [-BitVersion <32|64>] [-Platform <Windows|Linux>] [-Run] [-Help]
# -----------------------------------------------------------------------------------------------------------------------------------------------------
#   Options:

# When writing option, higher or lower case is not important!
# All options can be used with "/" or "-" and in any order
# Enter options with [Name] [Value] format, example: -Compiler Gcc

#     -Compiler, -c <gcc|clang|cl(or msvc)|...>        Select compiler to use. If not specified, program will look at what compiler you have.
#                                                      If many compilers available, program will use first one from available list.
# ------------------------------------------------------------------------------------------------------------------------------------------------------
#     -Presentation, -l <Normal|Silent|Debug|Full>     Select information presentation mode.
#                                                      Normal: Shows only errors/warnings/Compilation info.
#                                                      Silent: Shows only errors.
#                                                      Debug: Shows information about files, libraries, compilers.
#                                                      Full: Shows all information.
# ------------------------------------------------------------------------------------------------------------------------------------------------------
#     -BitVersion, -b <32|64>                          Select bit version of compiler. If not specified, program will look at what you have on your system.
# ------------------------------------------------------------------------------------------------------------------------------------------------------
#     -Platform, -p <Windows|Linux>                    Select platform to build for. If not specified, program will look at what platform you have.
# ------------------------------------------------------------------------------------------------------------------------------------------------------
#     -Run, -r                                         Runs program after building.
# ------------------------------------------------------------------------------------------------------------------------------------------------------
#     -Help, -h, -?                                    Shows this help message.
# ------------------------------------------------------------------------------------------------------------------------------------------------------
#     -CompilerArguments, -a <Arguments>               Pass arguments dirrectly to the compiler.
# ------------------------------------------------------------------------------------------------------------------------------------------------------
#     -File, -f <File1, File2, File3, ...>             If this program can't find files, specify which files to compile.
# ------------------------------------------------------------------------------------------------------------------------------------------------------
#     -Paths, -s <Path1, Path2, Path3, ...>            Specify paths to search for files.
# ------------------------------------------------------------------------------------------------------------------------------------------------------
# Examples: Build.ps1 -Compiler Gcc -Platform Windows -BitVersion 64 -Presentation Normal -Run
#           Build.ps1 -Platform Linux -Compiler Clang -Paths '/home/user/Development/Engine'
#           Build.ps1 -Platform Linux -Compiler MSVC -Paths 'C:\Users\User\Documents\Dev\Engine'
# ------------------------------------------------------------------------------------------------------------------------------------------------------

# Preparing options
$Arguments = $args
$Compiler
$Help
$Presentation
$BitVersion
$Platform
$Run
$CaughtBadArguments

# This section will get arguments passed to the script, check them, get the system information and combine that for the compilation process

# Getting arguments passed to the script, using foreach loop and switch, but you can use any other way to do it
if ($Arguments.Length -gt 0) {
for ($i = 0; $i -lt $Arguments.Length; $i++) { #args is powershell variable that contains all arguments passed to the script
  switch ($Arguments[$i].ToString().ToLower()) { # Casting argument string to lowercase
    { $_ -in @("-help", "-h", "/help", "/h", "-?", "/?") } {$Help = $true; break} # checking if this argument is equal to parameters
    { $_ -in @("-compiler", "-c", "/compiler", "/c") } {$Compiler = $Arguments[++$i]; continue} #if the argument is compiler, get the next argument which should be name of the compiler
    { $_ -in @("-presentation", "-l", "/presentation", "/l") } {$Presentation = $Arguments[++$i]; continue} # same for others, but -run, because it's flag
    { $_ -in @("-bitversion", "-b", "/bitversion", "/b") } {$BitVersion = $Arguments[++$i]; continue}
    { $_ -in @("-platform", "-p", "/platform", "/p") } {$Platform = $Arguments[++$i]; continue}
    { $_ -in @("-run", "-r", "/run", "/r") } {$Run = $true; continue}
    default {$CaughtBadArguments = $true} # if this argument is not equal to parameters, do nothing
    }
}}

# -----------------------------------------------------------------------------------------------------------------------------------------------------
# In this section we will specify what to output in command line, how many and which information should be presented to user
## Implement presentation modes
# -----------------------------------------------------------------------------------------------------------------------------------------------------
# In this section we will get platform information(if not specified with arguments)
## Implement checking for system information
# Going through all possible platforms, to see which one is used
if ($null -eq $Platform) {
    switch ($env:OS) {
        "Windows_NT" { $Platform = "Windows" }
        "Linux" { $Platform = "Linux" }
        default {
            Write-Host "Unknown platform, or not supported yet"
            exit 1
        }
    }
}
# Getting OS architecture, processor architecture
if ($null -eq $BitVersion) {
    if ([System.Environment]::Is64BitProcess) {
        $BitVersion = 64
    } else {
        $BitVersion = 32
    }
    # How that works:
    #   [System.Environment]::Is64BitProcess - is a function that PowerShell provides to the user, that returns $true or $false, depending on the system architecture
    #   This if-else structure checks the value of the previous statement, and depending on the result, assigns the appropriate value to the variable
}
if ($Platform -eq "Windows") {
    $ExecutableExtension = ".exe"
} elseif ($Platform -eq "Linux") {
    $ExecutableExtension = ".elf"
} else {
    
}

# Getting available compilers
## Implement getting available compilers

# -----------------------------------------------------------------------------------------------------------------------------------------------------
#   if specified Debug presentation mode, we will show all arguments passed to the script
if ($CaughtBadArguments -eq $true) {
    Write-Host "Some argument(s) was passed wrong, or not specified. See -Help for more information about available arguments and syntax"
}

# ------------------------------------------------------------------------------------------------------------------------------------------------------

# Getting source directory
$ProjectDirectory = Split-Path -Parent (Split-Path -Parent $MyInvocation.MyCommand.Definition)

# How that works:
#   $MyInvocation.MyCommand.Definition - is the path to the script
#   Split-Path is command that allows to split path into parts, and use them in any order,
#     here -Parent gets path before the script name, example: Split-Path -Parent "C:\...\Build.ps1" will return "C:\...",
#     same result as cd .. , but for this current script 
#   Second Split-Path gets path before the parent path, example: Split-Path -Parent "C:\..." will return "C:\"

# -----------------------------------------------------------------------------------------------------------------------------------------------------
# In this section we will compile the project
#   Function that will gather all the given data and compile the project
function Compile {
    $Files = GetFiles
    clang -g -Werror -std=c99 $Files.SourceFiles -o "Compiled\Heat$ExecutableExtension"
}

# ------------------------------------------------------------------------------------
# This section contains all functions that will be used in the script
function HelpMessage {
    Write-Host "
    Current build path: $ProjectDirectory
    MSVC is not supported yet. Sorry!

Usage: Build.ps1 (options...)[-Compiler <gcc|clang|cl>] [-Presentation <Normal|Debug>] [-BitVersion <32|64>] [-Platform <Windows|Linux>] [-Run] [-Help]
-----------------------------------------------------------------------------------------------------------------------------------------------------
  Options:

When writing option, higher or lower case is not important!
All options can be used with "/" or "-" and in any order
Enter options with [Name] [Value] format, example: -Compiler Gcc

    -Compiler, -c <gcc|clang|cl(or msvc)|...>        Select compiler to use. If not specified, program will look at what compiler you have.
                                                     If many compilers available, program will use first one from available list.
------------------------------------------------------------------------------------------------------------------------------------------------------
    -Presentation, -l <Normal|Silent|Debug|Full>     Select information presentation mode.
                                                     Normal: Shows only errors/warnings/Compilation info.
                                                     Silent: Shows only errors.
                                                     Debug: Shows information about files, libraries, compilers.
                                                     Full: Shows all information.
------------------------------------------------------------------------------------------------------------------------------------------------------
    -BitVersion, -b <32|64>                          Select bit version of compiler. If not specified, program will look at what you have on your system.
------------------------------------------------------------------------------------------------------------------------------------------------------
    -Platform, -p <Windows|Linux>                    Select platform to build for. If not specified, program will look at what platform you have.
------------------------------------------------------------------------------------------------------------------------------------------------------
    -Run, -r                                         Runs program after building.
------------------------------------------------------------------------------------------------------------------------------------------------------
    -Help, -h, -?                                    Shows this help message.
------------------------------------------------------------------------------------------------------------------------------------------------------
    -CompilerArguments, -a <Arguments>               Pass arguments dirrectly to the compiler.
------------------------------------------------------------------------------------------------------------------------------------------------------
    -File, -f <File1, File2, File3, ...>             If this program can't find files, specify which files to compile.
------------------------------------------------------------------------------------------------------------------------------------------------------
    -Paths, -s <Path1, Path2, Path3, ...>            Specify paths to search for files.
------------------------------------------------------------------------------------------------------------------------------------------------------
Examples: Build.ps1 -Compiler Gcc -Platform Windows -BitVersion 64 -Presentation Normal -Run
          Build.ps1 -Platform Linux -Compiler Clang -Paths '/home/user/Development/Engine'
          Build.ps1 -Platform Linux -Compiler MSVC -Paths 'C:\Users\User\Documents\Dev\Engine'
------------------------------------------------------------------------------------------------------------------------------------------------------
"
}
#Function that gathers all files into variables and returns them
function GetFiles {
    $Files = @{
      SourceFiles = @()
      IncludePaths = @()
      Libraries = @()
    }
    $Files.SourceFiles = Get-ChildItem -Path "$ProjectDirectory\Engine" -Recurse -Include *.c, *.asm | ForEach-Object { $_.FullName }
    Get-ChildItem -Path "$ProjectDirectory\Libraries" -Directory | ForEach-Object {
        $Files.IncludePaths += Get-ChildItem -Path $_.FullName -Recurse -Include "include" | ForEach-Object { " -I " + $_.FullName }
    }
    return $Files
}
# -----------------------------------------------------------------------------------------------------------------------------------------------------
# That is point, where program will start executing

Compile

# -----------------------------------------------------------------------------------------------------------------------------------------------------
# End of the script