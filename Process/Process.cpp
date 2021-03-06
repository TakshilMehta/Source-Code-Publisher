/////////////////////////////////////////////////////////////////////////////
// Process.cpp - class used to start process                               //
// ver 1.2                                                                 //
// ----------------------------------------------------------------------- //
// Language:    Visual C++, Visual Studio 2017                             //
// Platform:    Dell Inspiron 7, Core i7, Windows 10                       //
// Application: Project 1 - Source Code Publisher                          //
//              CSE687 Object Oriented Design, Spring 2019                 //
// Source:      Jim Fawcett, CST 4-187, Syracuse University                //
//              (315) 443-3948, jfawcett@twcny.rr.com                      //
// Author:      Takshil Mehta, tamehta@syr.edu                             //
/////////////////////////////////////////////////////////////////////////////

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


  std::string appPath = "C:\\Program Files\\Mozilla Firefox\\firefox.exe";  // path to application to start
  p.application(appPath);

  std::string cmdLine = "/A ../convertedPages/CodeUtilities.cpp.html";  // asking notepad to display Process.h
  p.commandLine(cmdLine);
 
  //std::string appPath = "C:\\Program Files\\Mozilla Firefox\\firefox.exe";  // path to application to start
  //p.application(appPath);

  //std::string cmdLine = "/A ../Converted Files/CodeUtilities.cpp.html";  // asking notepad to display Process.h
  //p.commandLine(cmdLine);
  
  std::cout << "\n  Will start notepad 5 times and each time wait for termination.";
  std::cout << "\n  You need to kill each window (upper right button) to continue.";
  std::cout << "\n  Press key to start";
  _getche();
  
  for (int i = 0; i < 5; ++i)
  {
    std::cout << "\n  starting process: \"" << appPath << "\"";
    std::cout << "\n  with this cmdlne: \"" << cmdLine << "\"";
    p.create();
    CBP callback = []() { std::cout << "\n  --- child process exited with this message ---"; };
    p.setCallBackProcessing(callback);
    p.registerCallback();

    WaitForSingleObject(p.getProcessHandle(), INFINITE);  // wait for created process to terminate
  }

  std::cout << "\n  after OnExit";
  std::cout.flush();
  char ch;
  std::cin.read(&ch,1);
  return 0;
}

#endif
