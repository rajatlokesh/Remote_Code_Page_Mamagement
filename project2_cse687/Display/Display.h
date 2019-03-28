#pragma once
/////////////////////////////////////////////////////////////////////
// DirExplorerN.h - Naive directory explorer                       //
// ver 1.3														   //
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
 * Process.h, Process.cpp
 * FileSystem.h, FileSystem.cpp      // Directory and Path classes
 * CodeUtilities.h                   // ProcessCmdLine class
 *
 * Maintenance History:
 * --------------------
 * ver 1.0 : 13 Feb 2019
 * - first release
 *
*/
#include<iostream>
#include<vector>
namespace Display {
//------------<Show class just a wrapper around showpages to show converted files with application>------------------
	class Show
	{
	public:
		Show();
		~Show();
//-------------<accpts application path and list of files to show on the browser>------------------------------------
		static void Showpages(std::string &application_path, std::vector<std::string> &con_filelist);

	};

	
}