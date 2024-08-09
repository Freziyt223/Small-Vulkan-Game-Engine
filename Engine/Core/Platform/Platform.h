#pragma once
// We define, that we use Unicode at the start, and then, if the program doesn't support Unicode, we use ASCII.
#define UNICODE
// ------------------------------------------------------------------------------------------------------------------------
// Compiler specific defines and variables.

#if defined(__clang__) || defined(__gcc__)
#define STATIC_ASSERT _Static_assert
#else
#define STATIC_ASSERT static_assert
#endif
// ------------------------------------------------------------------------------------------------------------------------
// Platform specific defines and variables.

#if defined (WIN32) || defined (_WIN32) || defined (__WIN32__)
  #define Windows 1
  // ------------------------------------------------------------------------------------------------------------------------
  // Aquire the window functions declarations(to let program know that they do exist)

  #include <windows.h>
  #include <windowsx.h>
  
  // ------------------------------------------------------------------------------------------------------------------------
  #ifndef UsingGLFW          // if we are not using GLFW(in future also will be other libraries), we need to use default windows api
    typedef HWND WindowType; // Window type differ for each platform, so we define it here, to use for the graphics and other
                             // window related functions.
  #endif
  // ------------------------------------------------------------------------------------------------------------------------
  #if defined (WIN64) || defined (_WIN64) || defined (__WIN64__)
  #define Windows64Bits 1
  #else
  #define Windows32Bits 1
  #endif

// Others aren't implemented yet. But will be:)
#elif defined (__linux__) || defined (__linux) || defined (__gnu_linux__)
  #define PLATFORM_LINUX 1
#if defined(__ANDROID__) 
  #define PLATFORM_ANDROID 1
#endif
#elif defined(__unix__)
  #define PLATFORM_UNIX
#elif defined(_POSIX_VERSION)
  #define PLATFORM_POSIX 1
#elif __APPLE__
  #define PLATFORM_APPLE 1
  #include <TargetConditionals.h>
  #if TARGET_IPHONE_SIMULATOR
      #define PLATFORM_IOS 1
      #define PLATFORM_IOS_SIMULATOR 1
  #elif TARGET_OS_IPHONE
      #define PLATFORM_IOS 1
      #define PLATFORM_IOS_DEVICE 1
  #elif TARGET_OS_MAC
      #define PLATFORM_MACOS 1
      #define PLATFORM_MACOS_DEVICE 1
  #else 
      #define UNSUPPORTED_PLATFORM 1
      #define PLATFORM_UNKNOWN_APPLE 1
  #endif
#else 
  #define UNSUPPORTED_PLATFORM 1
#endif
// ------------------------------------------------------------------------------------------------------------------------
// Now definitions and variables for other files

void InitializePlatform();
void TerminatePlatform();
char UpdatePlatform();
// ------------------------------------------------------------------------------------------------------------------------