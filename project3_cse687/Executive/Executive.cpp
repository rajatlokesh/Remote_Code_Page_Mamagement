
/////////////////////////////////////////////////////////////////////
// Executive.cpp - Entry point for Project 1					   //
// ver 1.0                                                         //
// RAJAT Vyas, CSE687 - Object Oriented Design, Spring 2019        //
/////////////////////////////////////////////////////////////////////




#include "Executive.h"
#include"../Display/Display.h"
#include"../InfoExtractor/InfoExtractor.h"
#include"../Utility/CodeUtilities/CodeUtilities.h"
using namespace Utilities;
using namespace FileSystem;
using namespace HtmlConverter;
using namespace Display;



#ifdef TEST_EXECUTIVE

int main(int argc, char * argv[]) 
{
	ProcessCmdLine pcl(argc, argv);
	std::string path = pcl.path();
	std::string app_path;
	std::vector<std::string> patterns = pcl.patterns();
	std::string pat;
	std::string chrome;
	Executive exe();
	exe.setdir(path);
	for (auto patt : patterns) {
		try
		{
			if (patt.find(".exe") != patt.npos) {
				chrome = patt;
			}
			else {
				std::regex re(patt);
				exe.setregex(patt);
			}
		}
		catch (const std::exception&)
		{
			
		}
	}
	exe.execute();
	return 0;
}
#endif // TEST_EXECUTIVE

HtmlConverter::Executive::Executive()
{
}

HtmlConverter::Executive::~Executive()
{
}

bool HtmlConverter::Executive::execute()
{
	bool result = false;
	Loader::LoadFiles lf(dir_);
	lf.setregex(regex_);
	lf.load();
	std::vector<std::string> selectedfiles = lf.getselectedfiles();
	result = convertfiles(selectedfiles);
	return result;
}

vector<string> HtmlConverter::Executive::convertedfiles()
{
	return convertedfiles_;
}

string HtmlConverter::Executive::getdir()
{
	return dir_;
}

void HtmlConverter::Executive::setdir(const string & dir)
{
	dir_ = dir;
}

string HtmlConverter::Executive::getregex()
{
	return regex_;
}

void HtmlConverter::Executive::setregex(const string & regex)
{
	regex_ = regex;
}

void HtmlConverter::Executive::openbrowser(const string & filename)
{
	std::string browserpath = "C:\\Program Files (x86)\\Google\\Chrome\\Application\\chrome.exe";
	std::vector<std::string> flst = { filename };
	Display::Show::Showpages(browserpath, flst);
}

bool HtmlConverter::Executive::convertfiles(const vector<string> & selectedfiles)
{
	bool result = false;
	std::string convertedpagepath = "../../../Convertedpages";
	InfoExtractor::FileTypeInfo fti(selectedfiles);
	fti.parse();
	HtmlGenerator genrate(Path::getFullFileSpec(convertedpagepath),fti.getinfo(),fti.getDepend());
	result = genrate.convert(selectedfiles);
	convertedfiles_ = genrate.getconvertedfiles();
	return result;
}

void HtmlConverter::Executive::setconvertedfiles(const vector<string>& files)
{
	convertedfiles_ = files;
}
