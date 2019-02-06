/////////////////////////////////////////////////////////////////////////////
// Convert.h - Convert files to HTML                                       //
// ver 1.0                                                                 //
// ----------------------------------------------------------------------- //
// Language:    Visual C++, Visual Studio 2017                             //
// Platform:    Dell Inspiron 7, Core i7, Windows 10                       //
// Application: Project 1 - Source Code Publisher                          //
//              CSE687 Object Oriented Design, Spring 2019                 //
// Author:      Takshil Mehta, tamehta@syr.edu                             //
/////////////////////////////////////////////////////////////////////////////
#include "Executive.h"

#include<iostream>
#include<regex>

using namespace Utilities;
using namespace FileSystem;
using namespace Requirements;

Utilities::ProcessCmdLine::Usage customUsage()
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

#ifdef TEST_EXECUTIVE

std::vector<std::string> filesToProcess;
std::string dirPath = "../convertedPages";

using namespace std;
int main(int argc, char *argv[]) {
	try {
		Tests test;
		test.requirement1234();
		ProcessCmdLine pcl(argc, argv);
		pcl.usage(customUsage());
		preface("Command Line: ");
		pcl.showCmdLine();
		pcl.showRegexes();
		putline();
		if (pcl.parseError()) {
			pcl.usage();
			std::cout << "\n\n";
			return 1;
		}		
		DirExplorerN de(pcl.path());
		for (auto patt : pcl.patterns())
			de.addPattern(patt);
		if (pcl.hasOption('s'))
			de.recurse();
		de.search();
		de.showStats();
		std::vector <std::string> previousfiles = FileSystem::Directory::getFiles(dirPath);
		for (auto file : previousfiles)
			FileSystem::File::remove(dirPath + "/" + file);
		cout << endl << "Files to be Converted" << endl;
		std::vector<std::string> finalFilestoprocess = de.mainFunction(de.providedPattern(), pcl.regexes());
		for (auto file : finalFilestoprocess)
			cout << "\t" << FileSystem::Path::getName(file) << endl;
		test.requirement5();
		if (finalFilestoprocess.empty()) {
			test.requirement7();
			cout << endl << endl << "No Files to display" << endl;
		} else {
			test.requirement6();
			Convert cvt;
			for (auto file : finalFilestoprocess)
				cvt.ConvertToHtml(file, "../convertedPages");
			test.requirement7();
			Display dis;
			dis.displayFiles();
		}
		test.requirement8();
		return 0;
	} catch(exception e){
		e.what();
	}
}
#endif

//need to take firefox path as the input