
/////////////////////////////////////////////////////////////////////
// Executive.cpp - Entry point for Project 1					   //
// ver 1.0                                                         //
// RAJAT Vyas, CSE687 - Object Oriented Design, Spring 2019        //
/////////////////////////////////////////////////////////////////////




#include "Executive.h"
#include"../Display/Display.h"


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


	Executive::execute(path,app_path,patterns,0);
	return 0;
}
#endif // TEST_EXECUTIVE

Executive::Executive()
{
}

Executive::~Executive()
{
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
		result = exe.showcoverterwork();
	}
	if (!sfiles.empty() && app == 1)
	{
		result = exe.convertwork(convertedpages, sfiles);
		Loader::LoadFiles convertedfiles(Path::getFullFileSpec(convertedpages));
		std::vector<std::string> cfiles = convertedfiles.getfiles();
		Display::Show::Showpages(application_path,cfiles);
	}
	if (app == -1) {
		result = exe.DemoLoader(loadfiles, sfiles);
	}
	return true;
}

bool HtmlConverter::Executive::convertwork(std::string &convertedpages, std::vector<std::string> &sfiles)
{
	std::cout << "Converted Files:\n";
	HtmlGenerator html(Path::getFullFileSpec(convertedpages));
	html.setspecial();
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

bool HtmlConverter::Executive::showcoverterwork()
{
	bool result = false;
	//Loader::LoadFiles conf(Path::getFullFileSpec("../testconverter"));
	FileSystem::File cppfile(Path::getFullFileSpec("../testconverter/test.cpp"));
	cppfile.open(FileSystem::File::in, FileSystem::File::text);
	int count = 1;
	bool t = true;
	std::cout << "\n File " << cppfile.name() << " before conversion:\n";
	while (cppfile.isGood()) {
		std::string temp = cppfile.getLine();
		count++;
		if (temp.find("<") != temp.npos || temp.find(">") != temp.npos)
			std::cout << "line " << count << " -> " << temp << "\n";
		if (count > 10)
		{
			count = 0;
			break;
		}
	}
	cppfile.close();
	HtmlGenerator html(Path::getFullFileSpec("../testconverter"));
	result = html.convert(Path::getFullFileSpec("../testconverter/test.cpp"));
	Loader::LoadFiles lf(Path::getFullFileSpec("../testconverter"));
	std::cout << "\n\n File " << cppfile.name() << " converted into ";
	FileSystem::File htmlfile(Path::getFullFileSpec("../testconverter/test.cpp.html"));
	result = htmlfile.open(FileSystem::File::in, FileSystem::File::text);
	std::string temp = "";
	std::cout << Utilities::SplitFilename(htmlfile.name()) << "\nAfter Conversion:\n";
	while (htmlfile.isGood()) {
		temp = htmlfile.getLine();
		if ((temp.find("&lt;") != temp.npos || temp.find("&gt;") != temp.npos) && count<50)
			std::cout << "line " << count << " -> " << temp << "\n";
		if (temp.find("body") != temp.npos) {
			std::cout << temp << "\n";
			t = 1-t;
		}
		if (t == true && temp.find("/body") == temp.npos) {
			std::cout << temp << "\n";
		}
		count++;
	}
	return result;
}
//std::vector<std::string> converter::FileHandler::getfilelist()
//{
//	return filelist_;
//}
//
//void converter::FileHandler::execute(const std::string & filename)
//{
//	filelist_.push_back(filename);
//}
//
//std::vector<std::string> converter::DirSetup(std::string & path,std::vector<std::string>& patterns)
//{
//	DirBrowser db(path);
//	FileHandler fh;
//	db.fileSubScribe(&fh);
//	for (auto patt:patterns)
//	{
//		db.addPattern(patt);
//	}
//	db.recurse();
//	db.search();
//	std::vector<std::string> flst = fh.getfilelist();
//	return flst;
//}
