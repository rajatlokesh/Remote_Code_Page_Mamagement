#pragma once
/////////////////////////////////////////////////////////////////////
// InfoExtracor.h - Extracts Information from given set of files   //
// ver 1.0														   //
// Author: Rajat Vyas											   //
//  CSE687 - Object Oriented Design,Fall 2019	             	   //
/////////////////////////////////////////////////////////////////////
/*
 * Package Operations:
 * -------------------
 * Uses Parser to Extract information from a list of files and store in Type Details.
 *
 * Required Files:
 * ---------------
 * TypeDetail.h, TypeDetail.cpp
 * Public Interface:
 * -----------------
 * parse() - Parse the list of files
 * filelist() - returns the list of convertedfiles
 * getinfo() - returns a pointer to the stored data in TypeInfo
 * getdepend() - returns a pointer to dependency table
 * Maintenance History:
 * --------------------
 * ver 1.1 : 22 mar 2019
 * - modified execute function to show additional functionality
 * - removed dirE()
 * ver 1.0 : 13 Feb 2019
 * - first release
 *
*/
#include<iostream>
#include<string>
#include"../TypeDetail/TypeDetail.h"
using namespace std;
using namespace TypeDetail;
namespace InfoExtractor {
	class FileTypeInfo
	{
	public:
		FileTypeInfo(vector<string> flst);
		~FileTypeInfo();
		const std::vector<std::string>& filelist();      //parse() - Parse the list of files
		void parse();									// filelist() - returns the list of convertedfiles
		TypeDetail::TypeInfo* getinfo();				//returns a pointer to the stored data in TypeInfo
		TypeDetail::Dependencies* getDepend();			//returns a pointer to dependency table
	private:
		TypeDetail::TypeInfo* ti_;
		TypeDetail::Dependencies* dep_;
		std::vector<std::string> filelist_;

		template<typename T> void extractIncludes(T t, std::string file);  //extracts dependencies
		template<typename T> void treeWalk(T t, std::string file);		   // extract class and function start and end points
	};

//--------------<Takes AST node and look for statesments_ only and only last token as well for dependencies>--------
	template<typename T>
	inline void FileTypeInfo::extractIncludes(T t, std::string file)
	{
		std::vector<std::string> dependencies;
		auto temp = t->statements_;
		if (temp.size() != 0) {
			for (auto t : temp)
			{
				std::string tp = t->last();
				if (tp[0] == '\"') {
					dep_->adddependency(file, tp.substr(tp.find("\"") + 1, tp.rfind("\"") - tp.find("\"") - 1));
				}
			}
		}
	}
	//--------------<Takes root AST node and recurese through the whole tree to find suitable information>--------
	template<typename T>
	inline void FileTypeInfo::treeWalk(T t, std::string file)
	{
		TypeDetail::Typedata* const td = new Typedata();
		td->type_name = file + "_" + t->name_;
		td->startline_ = t->startLineCount_;
		td->endline_ = t->endLineCount_;
		td->type_ = t->type_;
		ti_->AddInfo(file, td);
		auto iter = t->children_.begin();
		while (iter != t->children_.end()) {
			treeWalk(*iter, file);
			++iter;
		}
	}
}