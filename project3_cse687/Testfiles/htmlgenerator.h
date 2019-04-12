#pragma once
///////////////////////////////////////////////////////////////////////
// htmlgenerator.h - Converts code files .h or .cpp to html files    //
// ver 1.0                                                           //
// Language:    C++, Visual Studio 2017                              //
// Application: Source Code Publisher, CSE687 - Project 1	         //
// Author:      Rajat Vyas, Syracuse University,					 //
//              ravyas@syr.edu										 //
///////////////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
* This package provides classes:
* - HtmlGenerator     Converts code files .h or .cpp to html files   
* Build Process:
* --------------
* Required Files:
*   FileSystem.h
*	DirExplorerN.h
*   CodeUtilities.h
*
* Maintenance History:
* --------------------
* ver 1.0 : 13 Feb 2019
* - first release
* - Generated for project 1
*
* Notes:
* ------
* - Designed to converter code files to html files.
* 
*
* Planned Additions and Changes:
* ------------------------------
* - Interfacing is the next step to do.
*/
#include<iostream>
#include"../FileSystem/FileSystem.h"
#include"../DirExplorer/DirExplorerN.h"
#include"../Utilities/CodeUtilities/CodeUtilities.h"
#include<vector>
#include<regex>

namespace converter {

	//--------------<Accepts path of the final converted page>---------------
	class HtmlGenerator
	{
	public:
		HtmlGenerator(std::string path);
		~HtmlGenerator();
		std::string f_path();
		bool convert(std::string);
	private:
		std::string path_;
		/*std::vector<std::string> cppath_;*/
	};
}