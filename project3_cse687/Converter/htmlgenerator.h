#pragma once
///////////////////////////////////////////////////////////////////////
// htmlgenerator.h - Converts code files .h or .cpp to html files    //
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
* - HtmlGenerator     Converts code files .h or .cpp to html files   
* Build Process:
* --------------
* Required Files:
*   FileSystem.h
*	Loader.h
*   CodeUtilities.h
*	Dependency.h
*   ConfigureParser.h
* Maintenance History:
* --------------------
* ver 1.1 : 22 Mar 2019
* - enhanced functionality of detecting class, function and comment
* - wraps them with <div> and impart required styling
* - makes a call to parser to parse the code and all information.
*
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
#include"../Loader/Loader.h"

#include"../TypeDetail/TypeDetail.h"
#include<vector>
#include<regex>
using namespace TypeDetail;
namespace HtmlConverter {

	/*struct Type_Info
	{
		std::string type_name;
		std::string type_;
		int startline_;
		int endline_;
	};*/
	//--------------<Accepts path of the final converted page>---------------
	class HtmlGenerator
	{
	public:
		HtmlGenerator(const std::string& path,TypeInfo* const,Dependencies* const); //Constructor with special cases
		HtmlGenerator(const std::string& path);				//Constructor for basic conversion
		~HtmlGenerator();									//destructor
		std::string f_path();								//Getter for the Directory containing files to be converted
		bool convert(const std::string&);					//Converts Single file
		bool convert(std::vector<std::string>);				// Converts List of files
		std::string Specialcases(std::string f,std::vector<Typedata*> ti, int linecount); // Extracts Class Function and comment information
		std::string tegset(std::string);					// Converts < and > to "&lt;" and "&gt;" respectively
		void setspecial(bool v = true);						// set whether special cases like class and function to be handled or not
		bool getspecial();									// gets the current setup of special cases
		std::string depend_add(std::string&);				// adds dependencies in coverted files
		std::string comment(std::string&);					// adds comments class to the converted files
		bool writejs();
		bool writecss();
		std::vector<std::string> getconvertedfiles();
	private:
		std::string path_;
		TypeInfo* Info_;
		bool special_;
		Dependencies* dep_;
		std::vector<std::string> convertedfiles_;
	};



}