// ------------------------------------------------------------------------------------------------------------------------
// Includes and defines

#include "../Program/Program.h"


// ------------------------------------------------------------------------------------------------------------------------
// Here we define some functions and methods to use platform related things such as windowing, audio settings, keybinds and other

// I DO RECOMMEND to read official microsoft documentation on things you don't understand

#ifdef Windows 
  /**
   * This function will do something if some event is happening, 
   * like change resolution if window is being scaled 
   * @param Window is a window "handler" which windows api provides, check windows api tutorial
   * @param MessageCode special code that specifies event that had happened and should be processed
   * @param WParameter 
   * @param LParameter
   * @returns Default windows procedure code, check windows api tutorial
   * */ 
  LRESULT ProcessWindowEvents(HWND Window, UINT MessageCode, WPARAM WParameter, LPARAM LParameter) {
    switch(MessageCode) {
      case WM_ERASEBKGND: 
      // Our program will handle erasing background and not default window manager
        return 1; 
      case WM_CLOSE:
        return 0;
      case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
      
    }
    return DefWindowProcA(Window, MessageCode, WParameter, LParameter);
  }
  // Defines and variables for windows
  struct Platform {
    HWND Window; // Window "handle"
    HINSTANCE Instance; // Instance for program
  } Platform;

  // ------------------------------------------------------------------------------------------------------------------------
  /**
   * So, C works in the way, that to initialize/change variables with function you have to be in some function,
   * mostly it's just main function, but here we can't do that, so we make other function that we'll use in main.
  */

  /**
   * Function to initialize platform related variables
   * Returns nothing
   */
  void InitializePlatform() {
    // Getting active handle for the program
    Platform.Instance = GetModuleHandleA(0);

    // Setup and register window class(class that will hold window appearance data)
      HICON Icon = LoadIcon(Platform.Instance, IDI_APPLICATION); // Making an icon

      WNDCLASSA WindowClass; // creating window class

      memset(&WindowClass, 0, sizeof(WNDCLASSA)); // reseting everything in window class

      WindowClass.style = CS_DBLCLKS; // Saying to windows, that we allow double clicks on the window
      WindowClass.lpfnWndProc = ProcessWindowEvents; // Setting the function that will be called when the window receive events
      WindowClass.cbClsExtra = 0; // idk, just something
      WindowClass.cbWndExtra = 0; // same
      WindowClass.hIcon = Icon; // Setting the icon
      WindowClass.hCursor = LoadCursor(NULL, IDC_ARROW); // Setting the cursor
      WindowClass.hInstance = Platform.Instance; // Setting the instance of the program
      WindowClass.hbrBackground = NULL; // Setting background to none(black)
      WindowClass.lpszClassName = "Window_Engine"; // Naming our class, so then we can access it later and use for windowses window manager

      if(!RegisterClassA(&WindowClass)) {return;} // Registering a class and checking if any error occured
    
    // We also need to tell window manager, how our window will behave with other windows, and what it will have
    long long Style = WS_OVERLAPPEDWINDOW | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_THICKFRAME | WS_MINIMIZEBOX;
    long long ExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE; // We also need to set some extra styles, to make our window look better on never platforms
    
    // Centering window if it wasn't done already by user
    if (Program.Window.X == 0) {
      Program.Window.X = GetSystemMetrics(SM_CXSCREEN) / 2 - Program.Window.Width / 2;
      Program.Window.Y = GetSystemMetrics(SM_CYSCREEN) / 2 - Program.Window.Height / 2;
    }
    // Creating the window
    Platform.Window = CreateWindowExA(
      ExStyle, // Setting the extra styles
      "Window_Engine", // Passing Class name
      Program.Window.Title, // Passing Program name(what will be shown in task manager for example)
      Style, // Setting the style of the window
      Program.Window.X, // Passing position and size
      Program.Window.Y, 
      Program.Window.Width, 
      Program.Window.Height, 
      NULL, // This is for extended window usage, unimplemented yet
      NULL, // same
      Platform.Instance, // Passing instance of the program 
      NULL); // same
    // Checking if any error occured
    if(Platform.Window == NULL) {return;}
      
    if(!(Program.Window.Handle = Platform.Window)) {return;}
    // Checking if any error occured
    
    ShowWindow(Program.Window.Handle, SW_SHOW); // Showing the window
    UpdateWindow(Program.Window.Handle); // Updating the window
  };

  /**
   * Function that terminates and cleans up platform related things after program is finished
   * Doesn't return anything
   */
  void TerminatePlatform() {
    // Terminating the window
    if(Program.Window.Handle != NULL) {
      DestroyWindow(Program.Window.Handle);
      Program.Window.Handle = NULL;
    }
  };
  /**
   * Function that will check for update from audio, window, key manager
   * @returns True or False if the process was successful
   */
  char UpdatePlatform() {
    MSG Message;
    while(PeekMessageA(&Message, NULL, 0, 0, PM_REMOVE)) { // Peek message, and if there is any, then process it
      TranslateMessage(&Message);
      DispatchMessageA(&Message);

    }
    return 1;
  };
#endif

// ------------------------------------------------------------------------------------------------------------------------