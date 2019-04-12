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
		//--------< Interface to Source Code Publisher>----------------------------------------
	struct IPublisher
	{
		virtual ~IPublisher() {}
		virtual bool execute() = 0;
		virtual vector<string> convertedfiles() = 0;
		virtual string getdir()=0;
		virtual void setdir(const string&)=0;
		virtual string getregex()=0;
		virtual void setregex(const string &)=0;
		virtual void openbrowser(const string &) = 0;
	};
	//--------<Wrapper for execute function which takes a>--------------------------------- 
	//--------<path and execution path and patterns from >---------------------------------
	//--------<cmd line and execute converter>---------------------------------------------
	class Executive : public IPublisher
	{
	public:
		Executive();
		~Executive();
		bool execute();
		vector<string> convertedfiles();
		string getdir();
		void setdir(const string&);
		string getregex();
		void setregex(const string &);
		void openbrowser(const string &);
		bool convertfiles(const vector<string> &);
		
	private:
		void setconvertedfiles(const vector<string>&);
	private:
		vector<string> convertedfiles_;
		string dir_;
		string regex_;
		string convertfilepath_;
	};

//--------------<Interface Factory to Expose only definition and not implementation>---------------------
	class PublishFactory
	{
	public:
		static IPublisher* create()
		{
			Executive * rtn = new Executive();
			return rtn;
		}
	};
}

#endif // !EXECUTIVE_H