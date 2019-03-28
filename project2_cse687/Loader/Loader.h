#pragma once
///////////////////////////////////////////////////////////////////////
// Loader.h -   Encapsulates Directory Explorer and Provide list of  //
//			    files at a particular path.							 //
// ver 1.1                                                           //
// Language:    C++, Visual Studio 2017                              //
// Application: Source Code Publisher, CSE687 - Project 2	         //
// Author:      Rajat Vyas, Syracuse University,					 //
//              ravyas@syr.edu										 //
///////////////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
* This package provides classes:
* - Loader     Loades file from a particular address
* Build Process:
* --------------
* Required Files:
*   FileSystem.h
*   CodeUtilities.h
*	DirectoryExporerE.h
* Maintenance History:
* --------------------
* ver 1.0 : 22 March 2019
* - first release
* - Generated for project 2
*
* Notes:
* ------
* 
*
* Planned Additions and Changes:
* ------------------------------
* - Interfacing is the next step to do.
*/
#include "../DirExplorer-Events/DirExplorerE.h"
#include<regex>
using namespace FileSystem;

namespace Loader {
	using List = std::vector<std::string>;
	//subsriber class to iFileEvent any file that comes across pas through here
	class FileHandler : public IFileEvent {
	public:
		void execute(const std::string & filename);		//overridden function- handle for file
		List getfilelist();								//returns list of filename encountered
	private:
		List filelist_;
	};
	//subscriber class to IDir Event any dir encountered drops back here from DirExp
	class DirHandler : public IDirEvent {
		void execute(const std::string& dirname);		//overridden function - handle for directory
	};
	//Dir explorer encapsulation class provide application specific functionality
	class LoadFiles
	{
	public:
		LoadFiles(std::string path, List regex = {});
		~LoadFiles();
		List match(List files,List regex);				//Matches regex on files
		List getfiles();								// encapsulation on file handler
		void getdir();
	private:
		void search();									//DFS search encapsulates DirE
		List match();									//matches regex instace to FileInstance
	private:
		DirExplorerE* de_;
		FileHandler* fh_;
		DirHandler* dh_;
		List regex_;
	};

}