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
 * Maintenance History:
 * --------------------
 * ver 1.1 : 22 mar 2019
 * - modified execute function to show additional functionality
 * - removed dirE()
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
using namespace std;
namespace HtmlConverter{
		//static std::string SplitFilename(const std::string & str);
		//--------< Interface to Source Code Publisher>----------------------------------------
	struct IPublisher
	{
		virtual ~IPublisher() {}
		virtual bool execute() = 0;
		virtual vector<string> convertedfiles() = 0;
	};
	//--------<Wrapper for execute function which takes a>--------------------------------- 
	//--------<path and execution path and patterns from >---------------------------------
	//--------<cmd line and execute converter>---------------------------------------------
	class Executive : public IPublisher
	{
	public:
		Executive(string f_path, vector<string> patterns, string app_path, int sw);
		Executive();
		~Executive();
		bool execute();
		vector<string> convertedfiles();
		static bool execute(string f_path, string app_path, vector<string> patterns,int); //implements all the functionality
	private:
		bool convertwork(string &convertedpages, vector<string> &sfiles);			//does the work 
		bool DemoLoader(Loader::LoadFiles &loadfiles, vector<string> &sfiles);		//Shows Loader Functionality
		bool showcoverterwork(vector<string>&);
	private:
		string directorypath_;
		string convertedfolderpath_;
		vector<string> patterns_;
		string chromepath_;
		int switch_;
		//vector<string> convertedfiles_;

	};



	class PublishFactory
	{
	public:
		static IPublisher* create(string f_path, 
								  string patterns, string app_path = "C:\Program Files (x86)\Google\Chrome\Application\chrome.exe", int sw = 1)
		{
			Executive * rtn = new Executive(f_path, vector<string> {patterns}, app_path, sw);
			return rtn;
		}
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