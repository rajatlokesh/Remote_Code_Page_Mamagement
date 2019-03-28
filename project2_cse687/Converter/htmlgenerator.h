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
#include"../Utility/CodeUtilities/CodeUtilities.h"
#include"../Parser/Parser/ConfigureParser.h"
#include"../Dependency/Dependency.h"
#include<vector>
#include<regex>

namespace HtmlConverter {

	struct Type_Info
	{
		std::string type_name;
		std::string type_;
		int startline_;
		int endline_;
	};
	//--------------<Accepts path of the final converted page>---------------
	class HtmlGenerator
	{
	public:
		HtmlGenerator(std::string path);
		~HtmlGenerator();
		std::string f_path();
		bool convert(std::string);
		bool convert(std::vector<std::string>);
		void parse(std::vector<std::string>);
		void InfoExtract(CodeAnalysis::ASTNode * pGlobalScope,std::string);
		std::vector<std::string> DependencyExtractor(CodeAnalysis::ASTNode * pGlobalScope, const std::string& filename);
		std::vector<Type_Info*> getInfo(std::string file_name);
		void setInfo(std::string type_name, Type_Info * TI);
		std::string Specialcases(std::string f, std::vector<Type_Info*> ti, int linecount);
		std::string tegset(std::string);
		void setspecial(bool v = true);
		bool getspecial();
		std::string depend_add(std::string);
		void EndingDiv(std::string &temp,int line,Type_Info* T);
		std::string comment(std::string&);
		void MultiCommentHandle(std::string &temp);
	private:
		std::string path_;
		/*std::vector<std::string> cppath_;*/
		std::unordered_map<std::string, std::vector<Type_Info*>> Info_;
		bool special_;
		Dependency::Dependencies* dep_;
	};



}