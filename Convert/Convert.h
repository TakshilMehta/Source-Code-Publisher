#pragma once
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
/*
 * Module Operations:
 * ==================
 * This module provides class Convert
 * Convert class accepts filename and methods to convert a file to a HTML 
 * Files with same name by appending html extension and by replacing 
 * the escape squences with the valid html string.
 *
 * Public Interface:
 * =================
 * Convert cvt;
 *      cvt.convertToHtml(file, dirPath);
 *      convertChar(c);
 *
 * Required Files:
 * ===============
 * FileSystem.h
 * FileSystem.cpp
 *
 * Maintenance History:
 * ====================
 * ver 1.0 : 27 Jan 2019
 * - first release
 */

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <cstdlib>
#include "../DirectoryNavigator/FileSystem/FileSystem.h"

using namespace std;
using namespace FileSystem;

class Convert {
public:
	Convert() {};
	~Convert() {};

	// Converts file to HTML
	void ConvertToHtml(const std::string& filesToConvert, const std::string outputDir);

	// Replaces escape sequences
	std::string convertChar(char& c);
};

//----< replace the escape sequences with valid string >-----
/*
	While iterating through the contents of the file, replace
	'<' with "&lt" and '>' with "&gt".
*/
std::string Convert::convertChar(char& c) {
	if (c == '<')
		return "&lt;";
	else if (c == '>')
		return "&gt;";
	else if (c == '&')
		return "&amp";
	else{
		std::string s(1, c);
		return s;
	}
}

//----< convert the file to .html file >---------------------
/*
	Converts the entire file to html file with .html extension and
	inserting the tags for html.
*/
void Convert::ConvertToHtml(const std::string & fileToConvert, const std::string outputDir)
{
	try {
		string filename1 = FileSystem::Path::getName(fileToConvert);;
		string outputname;

		char c;
		ifstream inStream;
		ofstream outStream;

		inStream.open(fileToConvert.c_str());
		if (inStream.fail()) {
			cout << "I/O failure opening file." << endl;
			exit(1);
		}
		outputname = outputDir + "/" + filename1 + ".html";
		outStream.open(outputname.c_str());

		outStream << "<HTML>" << endl;
		outStream << "<TITLE>" << filename1 << "</TITLE>" << endl;
		outStream << "<BODY>" << endl << "<PRE>" << endl;

		while (!inStream.eof()) {
			inStream.get(c); 
			outStream << Convert::convertChar(c);
		}
		outStream << "</PRE>" << endl << "</BODY>" << endl << "</HTML>" << endl;
		inStream.close();
		outStream.close();
		cout << "Conversion of file \"" + FileSystem::Path::getName(fileToConvert) +"\" done." << endl << "\t\t Results are as file " << outputname << endl << endl;
	}
	catch (exception e) {
		cout << e.what();
	}
}
