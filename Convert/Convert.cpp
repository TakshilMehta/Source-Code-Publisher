/////////////////////////////////////////////////////////////////////////////
// Convert.cpp - Demonstrate Conversion of files to HTML                   //
// ver 1.0                                                                 //
// ----------------------------------------------------------------------- //
// Language:    Visual C++, Visual Studio 2017                             //
// Platform:    Dell Inspiron 7, Core i7, Windows 10                       //
// Application: Project 1 - Source Code Publisher                          //
//              CSE687 Object Oriented Design, Spring 2019                 //
// Author:      Takshil Mehta, tamehta@syr.edu                             //
/////////////////////////////////////////////////////////////////////////////

#include"Convert.h"
#ifdef TEST_CONVERT // only compile the following when defined

int main() {
	std::string dirPath = "../convertedPages";
	std::vector <std::string> previousfiles = FileSystem::Directory::getFiles(dirPath);
	for (auto file : previousfiles)
		FileSystem::File::remove(dirPath + "/" + file);

	Convert cvt;
	cvt.ConvertToHtml("./Convert.h", dirPath);
	return 0;
}
#endif






