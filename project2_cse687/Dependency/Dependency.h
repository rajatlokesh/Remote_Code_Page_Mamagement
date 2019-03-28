#pragma once
///////////////////////////////////////////////////////////////////////
// Dependency.h - Holds information about dependency amongst files   //
// ver 1.0                                                           //
// Language:    C++, Visual Studio 2017                              //
// Application: Source Code Publisher, CSE687 - Project 2	         //
// Author:      Rajat Vyas, Syracuse University,					 //
//              ravyas@syr.edu										 //
///////////////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
* This package provides classes:
* - Dependencies     Holds dependent to dependencies info
* Build Process:
* --------------
* Required Files:
*   Dependency.h
*   Dependency.cpp
*
* Maintenance History:
* --------------------
* ver 1.0 : 22 Mar 2019
* - first release
* - Generated for project 2
*
* Notes:
* ------
* - Designed to hold dependency info.
*
*
* Planned Additions and Changes:
* ------------------------------
* - Interfacing is the next step to do.
*/
#include<iostream>
#include<unordered_map>
#include<vector>
using namespace std;
namespace Dependency {
	class Dependencies
	{
	public:
		Dependencies() {};														//constructor	
		~Dependencies();														//Destructor
		std::vector<std::string> getdependencies(const std::string& dependent); //returns dependencies for given filename
		void adddependency(const string& dependent, const string& dependency = NULL); //adds dependency file for given filename
		bool haskey(std::string filename);											// Checks if a file is an entry in table

	private:
		std::unordered_map<std::string, std::vector<std::string>> dependencies_;
	};
}