#pragma once
/////////////////////////////////////////////////////////////////////////////
// DirExplorerN.h - Naive Directore Navigator                              //
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
/*
 * Package Operations:
 * -------------------
 * DirExplorerN provides a class, of the same name, that executes a
 * depth first search of a directory tree rooted at a specified path.
 * Each time it enters a directory, it invokes its member function
 * doDir, and for every file in that directory, it invokes doFile.
 *
 * We call this a "Naive Directory Explorer" because, while it carries
 * out its assigned responsibilities well, there is no way to change
 * what its doDir and doFile functions do, without changing the class
 * itself.  It would be much better to provide a mechanism to allow
 * a using application to supply this processing without changing
 * the Directory Navigator. 
 *
 * Other projects in the DirectoryNavigator folder in Repository/Cpp 
   do just that, in different ways.  

 * - DirExplorer-Naive (this project):
 *     Implements basic processing well, but applications have to
 *     change its code to affect how files and directories are
 *     handled.
 *     
 * We'll be using the Repository/Cpp solution to illustrate techniques 
 * for building flexible software.
 *
 * Public Interface:
 * =================
 * DirExplorerN de
 *    DirExplorerN de(path);
 *    void addPattern(string patt);
 * 	  void recurse(bool);
 *    void search();
 *    void find(string& path);
 *    void searchFiles(vector<string> reg);
 * 	  void finalfind(vector<string> files, vector<string> reg);
 * 	  files mainFunction(vector<string> patt, const vector<string> reg);
 *	  void doFile(string& filename);
 *    void doDir(string& dirname);
 *	  size_t fileCount();
 * 	  size_t dirCount();
 *	  void showStats();
 *	  patterns& providedPattern();
 *	  const files& filestoProcess();
 *	  const files& matchedFiles();
 *
 *
 * Required Files:
 * ---------------
 * DirExplorerN.h, DirExplorerN.cpp
 * FileSystem.h, FileSystem.cpp      // Directory and Path classes
 * StringUtilities.h                 // Title function
 * CodeUtilities.h                   // ProcessCmdLine class
 *
 * Maintenance History:
 * --------------------
 * ver 1.5 : 1 Feb 2019
 * - Added functionality to get files that match the given regex in command line.
 * ver 1.4 : 25 Jan 2019
 * - Removed all projects except those needed for DirExplorerN.
 * ver 1.4 : 24 Jan 2019
 * - Removed all projects except those needed for DirExplorerN.
 * ver 1.3 : 19 Aug 2018
 * - Removed some options to make this version simple.  Those are
 *   implemented in the more advanced navigators, presented here.
 * ver 1.2 : 17 Aug 2018
 * - Moved method definitions to inlines, below the class declaration.
 * ver 1.1 : 16 Aug 2018
 * - Made no recursion default, added option /s for recursion.
 * ver 1.0 : 11 Aug 2018
 * - first release
 *
*/
#include <vector>
#include <iostream>
#include<regex>
#include "../FileSystem/FileSystem.h"

namespace FileSystem
{
  class DirExplorerN
  {
  public:
    using patterns = std::vector<std::string>;
	using files = std::vector<std::string>;

    static std::string version() { return "ver 1.3"; }

    DirExplorerN(const std::string& path);

    // set options for analysis

    void addPattern(const std::string& patt);
    void recurse(bool doRecurse = true); 

    // conduct depth first search

    void search();
    void find(const std::string& path);

	// filter out the files that match the given regex in the command line
	void searchFiles(const std::vector<std::string> reg);
	void finalfind(const std::vector<std::string> files, const std::vector<std::string> reg);

	files mainFunction(const std::vector<std::string> patt, const std::vector<std::string> reg);

    // define what happens when a file or dir is encountered

    void doFile(const std::string& filename);
    void doDir(const std::string& dirname);

    // extract traversal statistics 

    size_t fileCount();
    size_t dirCount();
    void showStats();

	patterns& providedPattern();
	const files& filestoProcess();
	const files& matchedFiles();

  private:
    std::string path_;
    patterns patterns_;
    size_t dirCount_ = 0;
    size_t fileCount_ = 0;
    bool recurse_ = false;
	files filestoProcess_;
	files matchedFiles_;
  };

  //----< construct DirExplorerN instance with default pattern >-----

  inline DirExplorerN::DirExplorerN(const std::string& path) : path_(path)
  {
    patterns_.push_back("*.*");
  }
  //----< add specified patterns for selecting file names >----------

  inline void DirExplorerN::addPattern(const std::string& patt)
  {
    if (patterns_.size() == 1 && patterns_[0] == "*.*")
      patterns_.pop_back();
    patterns_.push_back(patt);
  }
  //----< set option to recusively walk dir tree >-------------------

  inline void DirExplorerN::recurse(bool doRecurse)
  {
    recurse_ = doRecurse;
  }
  //----< start Depth First Search at path held in path_ >-----------

  inline void DirExplorerN::search()
  {
    find(path_);
  }
  //----< search for directories and their files >-------------------
  /*
    Recursively finds all the dirs and files on the specified path,
    executing doDir when entering a directory and doFile when finding a file
  */
  inline void DirExplorerN::find(const std::string& path)
  {
    // show current directory

    std::string fpath = FileSystem::Path::getFullFileSpec(path);
    doDir(fpath);

    for (auto patt : patterns_)
    {
      std::vector<std::string> files = FileSystem::Directory::getFiles(fpath, patt);
      for (auto f : files)
      {
        doFile(f);  // show each file in current directory
		filestoProcess_.push_back(fpath + "\\" + f);
      }
    }

    std::vector<std::string> dirs = FileSystem::Directory::getDirectories(fpath);
    for (auto d : dirs)
    {
      if (d == "." || d == "..")
        continue;
      std::string dpath = fpath + "\\" + d;
      if (recurse_)
      {
        find(dpath);   // recurse into subdirectories
      }
      else
      {
        doDir(dpath);  // show subdirectories
      }
    }
  }
  //----< an application changes to enable specific file ops >-------

  inline void DirExplorerN::doFile(const std::string& filename)
  {
    ++fileCount_;
    //std::cout << "\n  --   " << filename;
  }
  //----< an application changes to enable specific dir ops >--------

  inline void DirExplorerN::doDir(const std::string& dirname)
  {
    ++dirCount_;
   // std::cout << "\n  ++ " << dirname;
  }
  //----< return number of files processed >-------------------------

  inline size_t DirExplorerN::fileCount()
  {
    return fileCount_;
  }
  //----< return number of directories processed >-------------------

  inline size_t DirExplorerN::dirCount()
  {
    return dirCount_;
  }
  //----< show final counts for files and dirs >---------------------

  inline void DirExplorerN::showStats()
  {
    std::cout << "\n\n  processed " << fileCount_ << " files in " << dirCount_ << " directories";
  }

  inline DirExplorerN::patterns & DirExplorerN::providedPattern()
  {
	  return patterns_;
  }

  inline const DirExplorerN::files & DirExplorerN::filestoProcess()
  {
	  return filestoProcess_;
  }

  inline void DirExplorerN::searchFiles(const std::vector<std::string> reg)
  {
	  finalfind(filestoProcess_, reg);
  }

  inline void DirExplorerN::finalfind(const std::vector<std::string> files, const std::vector<std::string> reg)
  {
	  // show current directory

	  //std::string fpath = FileSystem::Path::getFullFileSpec(path);

	  for (auto regex_str : reg) {
		  std::regex r(regex_str);
		  for (auto file : files) {
			  //std::string filespec = FileSystem::Path::getFullFileSpec(file);
			  std::string filename = FileSystem::Path::getName(file);
			  if (std::regex_match(filename, r)) {
				  matchedFiles_.push_back(file);
			  }
		  }
	  }
  }

  //----< return error if no matched files >-------------------
  inline DirExplorerN::files DirExplorerN::mainFunction(const std::vector<std::string> patt, const std::vector<std::string> reg)
  {
	  std::vector<std::string> finalFilestoProcess;
	  if (reg.empty()) {
		  finalFilestoProcess = DirExplorerN::filestoProcess();
	  }
	  else {
		  DirExplorerN::searchFiles(reg);
		  finalFilestoProcess = DirExplorerN::matchedFiles();
	  }

	  if (!finalFilestoProcess.empty()) {
		  std::cout << "\tThere are matched files";
		  return finalFilestoProcess;
	  }
	  else {
		  std::cout << "\tNo matched files";
		  return std::vector<std::string>();
	  }
  }
  //----< return final matched files >-------------------
  inline const DirExplorerN::files & DirExplorerN::matchedFiles() {
	  return matchedFiles_;
  }

}