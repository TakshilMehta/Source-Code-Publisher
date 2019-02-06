#pragma once
/////////////////////////////////////////////////////////////////////////////
// Display.h - Display Files to Browser                                    //
// ver 1.0                                                                 //
// ----------------------------------------------------------------------- //
// Language:    Visual C++, Visual Studio 2017                             //
// Platform:    Dell Inspiron 7, Core i7, Windows 10                       //
// Application: Project 1 - Source Code Publisher                          //
//              CSE687 Object Oriented Design, Spring 2019                 //
// Source:      Jim Fawcett, CST 4-187, Syracuse University                //
//              (315) 443-3948, jfawcett@twcny.rr.com                      //
// Author:      Takshil Mehta, tamehta@syr.edu                             //
/////////////////////////////////////////////////////////////////////////////
/*
 * Module Operations:
 * ==================
 * The module provides class Display
 * 
 * The Display class creates a process and will pop up the application
 * to display the files. 
 * On invoking displayFiles() function. files present at the path are
 * displayed in a browser (currently firefox).
 *
 * Public Interface:
 * =================
 * Display dis;
 * dis.displayFiles();
 *
 * Required Files:
 * ===============
 * FileSystem.h, FileSystem.cpp  // Directory and Path classes
 * Process.h                       // Process class
 *
 * Maintenance History:
 * ====================
 * ver 1.0 : 30 Jan 2019
 * - first release
 */
#include "../Process/Process.h"
#include "../DirectoryNavigator/FileSystem/FileSystem.h"
#include <conio.h>
class Display
{
public:
	Display() {};
	~Display() {};
	void displayFiles();
};

void Display::displayFiles()
{
	std::cout << "\n  Demonstrating code pop-up in Firefox";
	std::cout << "\n ======================================";

	Process p;
	p.title("Display");
	std::ifstream outputFile;
	std::string fileInfo;
	outputFile.open("../browserPath.txt");
	if (outputFile.fail()) {
		std::cout << "browserPath.txt does not exist" << std::endl << "create ../browserPath.txt" << std::endl ;
	}
	std::cout << std::endl << "\t\tIf display not working" << std::endl <<"\t\tEnter valid firefox.exe path in browserPath.txt" << std::endl;
	std::getline(outputFile, fileInfo);
	std::string appPath = fileInfo;  // path to application to start
	p.application(appPath);
	std::cout << "\n  Will start Firefox and each time wait for termination.";
	std::cout << "\n  You need to kill each window (upper right button) to continue.";
	std::cout << "\n  Press key to start";
	_getche();

	std::string dirPath = "../convertedPages";
	std::vector <std::string> files = FileSystem::Directory::getFiles(dirPath);
	int count = 0;
	for (auto file : files) {
		if (count < 5)
		{
			std::string cmdLine = "/A " + dirPath + "/" + file;
			p.commandLine(cmdLine);
			std::cout << "\n  starting process: \"" << appPath << "\"";
			std::cout << "\n  with this cmdlne: \"" << cmdLine << "\"";
			p.create();
			CBP callback = []() { std::cout << "\n  --- child process exited with this message ---"; };
			p.setCallBackProcessing(callback);
			p.registerCallback();
			count++;
			WaitForSingleObject(p.getProcessHandle(), INFINITE);  // wait for created process to terminate
		}
		else
			break;
	}
	std::cout << "\n  after OnExit";
	std::cout.flush();
	char ch;
	std::cin.read(&ch, 1);
}


