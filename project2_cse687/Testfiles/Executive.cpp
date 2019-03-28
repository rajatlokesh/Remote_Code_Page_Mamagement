/////////////////////////////////////////////////////////////////////
// Executive.cpp - Entry point for Project 1					   //
// ver 1.0                                                         //
// RAJAT Vyas, CSE687 - Object Oriented Design, Spring 2019        //
/////////////////////////////////////////////////////////////////////



#include"../DirExplorer/DirExplorerN.h"
#include"../Utilities/CodeUtilities/CodeUtilities.h"
#include"../Converter/htmlgenerator.h"
#include "Executive.h"
#include"../Display/Display.h"


using namespace Utilities;
using namespace FileSystem;
using namespace converter;
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


	Implement::execute(path,app_path,patterns);
	return 0;
}
#endif // TEST_EXECUTIVE

converter::Executive::Executive()
{
}

converter::Executive::~Executive()
{
}

bool converter::Executive::execute(std::string f_path, std::string app_path, std::vector<std::string> patterns, int app)
{
	std::vector<std::string> flst;
	std::vector<std::string> sfiles;
	std::string application_path = app_path;
	flst = DirExplorerSetup(f_path,1);
	std::string convertedpages = "../Convertedpages";
	sfiles = Fileselector(flst, patterns);
	bool result = false;
	//std::cout << "Path :" << FileSystem::Path::getFullFileSpec(f_path); std::cout << "\nRegex :";
	std::cout << "\n";
	if (!sfiles.empty())
	{
		std::cout << "\n Converted Files:\n";
		for (auto file : sfiles) {
			//std::cout << file << "\n" << std::endl;
			HtmlGenerator html(Path::getFullFileSpec(convertedpages));
			html.convert(file);
			if (app == 0) {
				std::cout << html.f_path()<<"\\"<<Utilities::SplitFilename(file)<<".html" << std::endl;
			}
		}

		std::vector<std::string> con_filelist = converter::DirExplorerSetup(Path::getFullFileSpec(convertedpages),0);

		if (app == 1) {
			Show::Showpages(application_path, con_filelist);
		}
		result = true;
	}
	else
	{
		std::cout << "Based on the regex provided, 0 files matched out of " << flst.size() << "!!" << std::endl;

		result = false;
	}
	return result;
}
