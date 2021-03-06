///////////////////////////////////////////////////////////////////////
// Process.cpp - class used to start process                         //
// ver 1.0                                                           //
// Author - Rajat Vyas												 //
// Provided by - Jim Fawcett, CSE687								 //
///////////////////////////////////////////////////////////////////////

#include "Process.h"
#include <iostream>
//#include <windows.h>
#include <conio.h>

#ifdef TEST_PROCESS

int main()
{
  std::cout << "\n  Demonstrating code pop-up in notepad";
  std::cout << "\n ======================================";

  Process p;
  p.title("test application");
  std::string appPath = "c:/windows/system32/notepad.exe";  // path to application to start
  p.application(appPath);

  std::string cmdLine = "/A ../Process/Process.h";  // asking notepad to display Process.h
  p.commandLine(cmdLine);

  std::cout << "\n  Will start notepad 5 times and each time wait for termination.";
  std::cout << "\n  You need to kill each window (upper right button) to continue.";
  std::cout << "\n  Press key to start";
  _getche();
  
  for (int i = 0; i < 5; ++i)
  {
    std::cout << "\n  starting process: \"" << appPath << "\"";
    std::cout << "\n  with this cmdlne: \"" << cmdLine << "\"";
    p.create();
    CBP callback = []() { std::cout << "\n  --- child process exited with this message ---\n"; };
    p.setCallBackProcessing(callback);
    p.registerCallback();

    WaitForSingleObject(p.getProcessHandle(), INFINITE);  // wait for created process to terminate
  }

  std::cout << "\n  after OnExit";
  std::cout.flush();
  return 0;
}

#endif
