# MSVC is not supported yet. Sorry!
#     Currently default compiler names are ggc, clang, and cl, if you changed them, or they were changed by default, Program will not work!
#     If you want to use other compilers, you have to change the code. Instruction will be below.
#     Usage: Build.ps1 (options...)[-Compiler <gcc|clang|cl>] [-Linker <gcc|clang|cl>] [-Presentation <Normal|Debug>] [-BitVersion <32|64>] [-Platform <Windows|Linux>] [-Run] [-Help]
#     --------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#       Options:

#   When writing option, higher or lower case is not important

#         -Compiler <gcc|clang|cl(or msvc)|...>           Select compiler to use. If not specified, program will look at what compiler you have.
#                                                         If many compilers available, program will use first one from available list.
#     --------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#         -Presentation <Normal|Silent|Debug|Full>         Select information presentation mode.
#                                                          Normal: Shows only errors/warnings/Compilation info.
#                                                          Silent: Shows only errors.
#                                                          Debug: Shows information about files, libraries, compilers.
#                                                          Full: Shows all information.
#     --------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#         -BitVersion <32|64>                             Select bit version of compiler. If not specified, program will look at what you have on your system.
#     --------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#         -Platform <Windows|Linux>                       Select platform to build for. If not specified, program will look at what platform you have.
#     --------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#         -Run                                            Runs program after building.
#     --------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#         -Help                                           Shows this help message.
#     --------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#         -CompilerArguments <Arguments>                  Pass arguments dirrectly to the compiler.
#     --------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#         -File <File1, File2, File3, ...>                If this program can't find files, specify which files to compile.
#     --------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#         -Paths <Path1, Path2, Path3, ...>               Specify paths to search for files.
#     --------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#     Examples: Build.ps1 -Compiler Gcc -Platform Windows -BitVersion 64 -Presentation Normal -Run
#               Build.ps1 -Platform Linux -Compiler Clang -Paths '/home/user/Development/Engine'
#               Build.ps1 -Platform Linux -Compiler MSVC -Paths 'C:\Users\User\Documents\Dev\Engine'
# ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

# Parameters for calling this script from command line,
# Example is above
