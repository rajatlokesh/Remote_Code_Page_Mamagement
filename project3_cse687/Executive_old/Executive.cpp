
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
	std::string path = Path::getFullFileSpec(pcl.path());
	std::string app_path;
	std::vector<std::string> patterns = pcl.patterns();
	int i = 0;
	for (auto patt : patterns) {
		if (std::regex_match(patt, std::regex(".*.exe$"))) {
			app_path = patt;
			patterns.erase(patterns.begin()+i);
		}
		i++;
	}
	Executive exe(path,app_path,patterns,0);
	exe.execute();
	Executive::execute(path,app_path,patterns,0);
	return 0;
}
#endif // TEST_EXECUTIVE

HtmlConverter::Executive::Executive(string f_path, vector<string> patterns, string app_path = "C:/Program Files (x86)/Google/Chrome/Application/chrome.exe", int sw = 1)
{
	directorypath_ = f_path;
	convertedfolderpath_ = "";
	patterns_ = patterns;
	switch_ = sw;
	chromepath_ = app_path;
}

Executive::Executive()
{
}

Executive::~Executive()
{
}

bool HtmlConverter::Executive::execute()
{
	return Executive::execute(directorypath_,chromepath_,patterns_,switch_);
}

vector<string> HtmlConverter::Executive::convertedfiles()
{
	string path = Path::getFullFileSpec(convertedfolderpath_);
	vector<string> patterns = { "*.html" };
	Loader::LoadFiles cf(path, patterns);
	return cf.getfiles();
}

bool Executive::execute(std::string f_path, std::string app_path, std::vector<std::string> patterns, int app)
{
	Executive exe;
	std::vector<std::string> flst,temp, sfiles;
	std::string convertedpages = "../Convertedpages";
	std::string application_path = app_path;
	Loader::LoadFiles loadfiles(f_path);
	temp = loadfiles.getfiles();

	for (auto fie : temp) 
		flst.push_back(fie);
	
	bool result = false;
	sfiles = loadfiles.match(flst,patterns);
	if (app == 0) {
		result = exe.showcoverterwork(sfiles);
	}
	if (!sfiles.empty() && app == 1)
	{
		result = exe.convertwork(convertedpages, sfiles);
		Loader::LoadFiles convertedfiles(Path::getFullFileSpec(convertedpages));
		std::vector<std::string> cfiles = convertedfiles.getfiles();
		//convertedfiles_ = cfiles;
		//Display::Show::Showpages(application_path,cfiles);
	}
	if (app == -1) {
		result = exe.DemoLoader(loadfiles, sfiles);
	}
	return true;
}

bool HtmlConverter::Executive::convertwork(std::string &convertedpages, std::vector<std::string> &sfiles)
{
	std::cout << "Converted Files:\n";
	InfoExtractor::FileTypeInfo Fti(sfiles);
	Fti.parse();
	HtmlGenerator html(Path::getFullFileSpec(convertedpages),Fti.getinfo(),Fti.getDepend());
	return html.convert(sfiles);
}

bool HtmlConverter::Executive::DemoLoader(Loader::LoadFiles &loadfiles, std::vector<std::string> &sfiles)
{
	std::cout << "Demonstrating loader Package:" << "\n" << std::string(50, '-') << "\n"
		<< "Files found at the given path by Loader are :\n" << std::string(50, '-') << std::endl;
	for (auto file : loadfiles.getfiles()) {
		std::cout << Utilities::SplitFilename(file) << "\n";
	}
	std::cout << std::string(50, '-') << "\nFiles matching given regex are:\n" << std::string(50, '-') << std::endl;
	for (auto mf : sfiles) {
		std::cout << Utilities::SplitFilename(mf) << "\n";
	}
	return true;
}

bool HtmlConverter::Executive::showcoverterwork(vector<string> &sfiles)
{
	bool result = false;
	HtmlConverter::HtmlGenerator ht("../Convertedpages/simplepages");
	
	return result;
}
