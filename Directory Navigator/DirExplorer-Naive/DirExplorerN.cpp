/////////////////////////////////////////////////////////////////////////////
// DirExplorerN.cpp - Demonstrates Naive Directory Navigator               //
// ver 1.5                                                                 //
// ----------------------------------------------------------------------- //
// Language:    Visual C++, Visual Studio 2017                             //
// Platform:    Dell Inspiron 7, Core i7, Windows 10                       //
// Application: Project 1 - Source Code Publisher                          //
//              CSE687 Object Oriented Design, Spring 2019                 //
// Source:      Jim Fawcett, CST 4-187, Syracuse University                //
//              (315) 443-3948, jfawcett@twcny.rr.com                      //
// Author:      Takshil Mehta, tamehta@syr.edu                             //
/////////////////////////////////////////////////////////////////////////////

#ifdef TEST_DIREXPLORERN  // only compile the following when defined

#include "DirExplorerN.h"
#include "../Utilities/StringUtilities/StringUtilities.h"
#include "../Utilities/CodeUtilities/CodeUtilities.h"
#include "../../Convert/Convert.h"

using namespace Utilities;
using namespace FileSystem;

ProcessCmdLine::Usage customUsage()
{
  std::string usage;
  usage += "\n  Command Line: path [/option]* [/pattern]*";
  usage += "\n    path is relative or absolute path where processing begins";
  usage += "\n    [/option]* are one or more options of the form:";
  usage += "\n      /s - walk directory recursively";
  usage += "\n    [pattern]* are one or more pattern strings of the form:";
  usage += "\n      *.h *.cpp *.cs *.txt or *.*";
  usage += "\n";
  return usage;
}

int main(int argc, char *argv[])
{
  Title("Demonstrate DirExplorer-Naive, " + DirExplorerN::version());

  ProcessCmdLine pcl(argc, argv);
  pcl.usage(customUsage());

  preface("Command Line: ");
  pcl.showCmdLine();
  putline();

  if (pcl.parseError())
  {
    pcl.usage();
    std::cout << "\n\n";
    return 1;
  }

  DirExplorerN de(pcl.path());
  for (auto patt : pcl.patterns())
  {
    de.addPattern(patt);
  }

  if (pcl.hasOption('s'))
  {
    de.recurse();
  }

  de.search();
  de.showStats();
  std::cout << "\n\n";

  for (auto file : de.matchedFiles())
	  cout << file;
	
  std::vector<std::string> finalFilestoprocess = de.mainFunction(de.providedPattern(), pcl.regexes());
  for (auto file : finalFilestoprocess)
	  cout << FileSystem::Path::getName(file) << endl;

  return 0;
}

#endif