#pragma once
/////////////////////////////////////////////////////////////////////
// ITranslator.h - Holds Interface for Managed c++ for c# client   //
//                 to use                                          //
// ver 1.0														   //
// Author: Rajat Vyas											   //
//  CSE687 - Object Oriented Design,Fall 2019	             	   //
/////////////////////////////////////////////////////////////////////
/*
 * Package Operations:
 * -------------------
 * Provides Interface for c# GUI to talk to c++ publisher
 *
 * Required Files:
 * ---------------
 * 
 * Public Interface:
 * -----------------
 * execute()           - Executes the publisher
 * setdirpath(String^) - Takes a path and sets it as the working directory for the publisher
 * setregex(String^)   - Takes a Regex and sets it for the Loader to filter files  
 * chrome(String^)     - Takes a file and Pass it to Display package to run it on browser
 * List<String^>^ getfiles() - Returns the list of converted files by publisher to GUI to show 
 * Maintenance History:
 * --------------------
 * ver 1.1 : 22 mar 2019
 * - modified execute function to show additional functionality
 * - removed dirE()
 * ver 1.0 : 13 Feb 2019
 * - first release
 *
*/
using namespace System;
using namespace System::Collections::Generic;


public ref class ITranslator abstract
{
public:
	virtual bool execute() = 0;							//- Executes the publisher
	virtual List<String^>^ getfiles() = 0;				//-Returns the list of converted files by publisher to GUI to show
	virtual bool chrome(String^) = 0;					//- Takes a file and Pass it to Display package to run it on browser
	virtual void setdirpath(String^)=0;					//- Takes a path and sets it as the working directory for the publisher
	virtual void setregex(String^)=0;					//- Takes a Regex and sets it for the Loader to filter files
private:
};

// Factory to create a pointer to Translator Interface rendering implementation obscure to the user
public ref class TranslatorFactory
{
public:
	static ITranslator^ CreateFactory();
	
};