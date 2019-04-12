#pragma once
/////////////////////////////////////////////////////////////////////
// Executive.h - Entry point for the project                       //
// ver 1.0														   //
// Author: Rajat Vyas											   //
// Provide by - Jim Fawcett, CSE687 - Object Oriented Design,	   //
// Fall 2019													   //
/////////////////////////////////////////////////////////////////////
/*
 * Package Operations:
 * -------------------
 * Open the browser chrome and show pages individually.
 *
 * Required Files:
 * ---------------
 * Display.h, Display.cpp
 * FileSystem.h, FileSystem.cpp      // Directory and Path classes
 * CodeUtilities.h                   
 * Public Interface:
 * -----------------
 * execute() - takes a path and execution path and patterns from cmd line and execute converter
 * DirExplorersetup() - sets up the directory path from which to real files and returs all the files in it.
 * Maintenance History:
 * --------------------
 * ver 1.0 : 13 Feb 2019
 * - first release
 *
*/
#ifndef EXECUTIVE_H
#define EXECUTIVE_H


#include <iostream>
#include<vector>
#include<regex>
#include"../Loader/Loader.h"
#include"../Converter/htmlgenerator.h"
using namespace FileSystem;

namespace HtmlConverter{
		//static std::string SplitFilename(const std::string & str);
	//--------<Wrapper for execute function which takes a path and execution path and patterns from cmd line and execute converter>------------
	class Executive
	{
	public:
		Executive();
		~Executive();
		static bool execute(std::string f_path, std::string app_path, std::vector<std::string> patterns,int);
		void convertwork(std::string &convertedpages, std::vector<std::string> &sfiles);
		void DemoLoader(Loader::LoadFiles &loadfiles, std::vector<std::string> &sfiles);
		bool showcoverterwork(std::vector<std::string> &filelist, bool &retflag);
	private:

	};
	/*class DirBrowser : public DirExplorerE {
	public:
		DirBrowser(const std::string& path) : DirExplorerE(path) {};
	};
	class FileHandler:public IFileEvent
	{
	public:
		void execute(const std::string& filename);
		std::vector<std::string> getfilelist();
	private:
		std::vector<std::string> filelist_;
	};
	static std::vector<std::string> DirSetup(std::string& path, std::vector<std::string>& patterns);*/
}

#endif // !EXECUTIVE_H