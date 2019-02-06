#pragma once
/////////////////////////////////////////////////////////////////////////////
// Executive.h - Demonstration of Source Code Publisher                    //
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
 * This module provides class Executive and Tests
 * Executive class is used to create object of executive class in future.
 *
 * Test class shows the requirements if they are fulfiled or not.
 * 
 * Public Interface:
 * =================
 * Execution ex;
 * Tests test;
 *		void test.reuirement1();
 *		void test.reuirement2();
 *		void test.reuirement3();
 *		void test.reuirement4();
 *		void test.reuirement5();
 *		void test.reuirement6();
 *		void test.reuirement7();
 *		void test.reuirement8();
 *		void test.reuirement1234();
 *
 * Required Files:
 * ===============
 * DirExplorer.h
 * CodeUtilities.h
 * StringUtilities.h
 * Convert.h
 * Display.h
 *
 * Maintenance History:
 * ====================
 * ver 1.0 : 03 Feb 2019
 * - first release
 */
#include "../DirectoryNavigator/DirExplorer-Naive/DirExplorerN.h"
#include "../DirectoryNavigator/Utilities/CodeUtilities/CodeUtilities.h"
#include "../DirectoryNavigator/Utilities/StringUtilities/StringUtilities.h"
#include "../Convert/Convert.h"
#include "../Display/Display.h"


class Executive
{
public:
	//Executive();
	//~Executive();
};

namespace Requirements {
	class Tests {
	public:
		void requirement1();
		void requirement2();
		void requirement3();
		void requirement4();
		void requirement5();
		void requirement6();
		void requirement7();
		void requirement8();
		void requirement1234();
	};


	void Requirements::Tests::requirement1() {
		cout << "===============================================================================================================" << endl;
		cout << "Fulfilling Requirement 1 :" << endl;
		cout << "I am using Visual Studio 2017 and its C++ Windows Console Projects, as provided in the ECS computer labs." << endl;
		cout << "===============================================================================================================" << endl << endl << endl;
	}
	
	void Requirements::Tests::requirement2() {
		cout << "===============================================================================================================" << endl;
		cout << "Fulfilling Requirement 2 :" << endl;
		cout << "I am using the standard streams libraries for all I/O and operators new and delete for memory management." << endl;
		cout << "===============================================================================================================" << endl << endl << endl;
	}

	void Requirements::Tests::requirement3() {
		cout << "===============================================================================================================" << endl;
		cout << "Fulfilling Requirement 3 :" << endl;
		cout << "I have provided Executive, Converter, and Display packages." << endl;
		cout << "===============================================================================================================" << endl;
		cout << "Here I am showing all the packages of the Project 01 using File System" << endl;
		std::vector<std::string> packages = FileSystem::Directory::getDirectories("..");
		for (auto package : packages) {
			if (FileSystem::File::exists("../" + package + "/" + package + ".vcxproj") || FileSystem::File::exists("../" + package + "/" + package + ".sln"))
				cout << "\t" << package << endl;
		}
		cout << endl << endl;
	}

	void Requirements::Tests::requirement4() {
		cout << "===============================================================================================================" << endl;
		cout << "Fulfilling Requirement 4 :" << endl;
		cout << "I am accepting a path that specifies where file(s) to be analyzed are found from the Command Line" << endl;
		cout << "Also a regular expression used to select filenames to process is also accepted from the Command Line." << endl;
		cout << "==============================================================================================================="<< endl;
	}

	void Requirements::Tests::requirement5() {
		cout << endl << "===============================================================================================================" << endl;
		cout << "Fulfilling Requirement 5 :" << endl;
		cout << "Should no matches be found, shall write an error message to the console." << endl;
		cout << "===============================================================================================================" << endl;
		cout << "Pattern :*.h" << endl << "Regular Expression: [Q](.*)" << endl;
		DirExplorerN de("../");
		de.addPattern("*.h");
		de.recurse(); 
		de.search();
		cout << endl << endl;
		de.mainFunction(de.providedPattern(), std::vector<std::string>{"[Q](.*)"});
		cout << endl << endl;
	}

	void Requirements::Tests::requirement6() {
		cout << "===============================================================================================================" << endl;
		cout << "Fulfilling Requirement 6 :" << endl;
		cout << "Shall, for each matching file, convert the file text, as described in the purpose section, to a" << endl << "valid html file, and save to a folder in your project tree, named convertedPages." << endl;
		cout << "===============================================================================================================" << endl << endl;
	}

	void Requirements::Tests::requirement7() {
		cout << endl;
		cout << "===============================================================================================================" << endl;
		cout << "Fulfilling Requirement 7 :" << endl;
		cout << "Shall display, in a child process using the default browser, each converted file, waiting for the" << endl << " child to exit before displaying the next file." << endl;
		cout << "===============================================================================================================" << endl;
	}

	void Requirements::Tests::requirement8() {
		cout << endl << "===============================================================================================================" << endl;
		cout << "Fulfilling Requirement 8 :" << endl;
		cout << "Shall include an automated test that demonstrates you meet all the functional requirements above." << endl << " Note that this is just a set of tests that show clearly the results of each step of processing" << endl << " you've used to implement this project." << endl;
		cout << "===============================================================================================================" << endl << endl << endl;
	}

	void Requirements::Tests::requirement1234() {
		requirement1();
		requirement2();
		requirement3();
		requirement4();
	}
}
