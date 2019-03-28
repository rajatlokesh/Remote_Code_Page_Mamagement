/////////////////////////////////////////////////////////////////////
// Loader.cpp - directory explorer using events			           //
// ver 1.0                                                         //
// RAJAT Vyas, CSE687 - Object Oriented Design, Spring 2019        //
/////////////////////////////////////////////////////////////////////

#include "Loader.h"
#include"../Utility/CodeUtilities/CodeUtilities.h"
using namespace Loader;
Loader::LoadFiles::LoadFiles(std::string pth, List regex)
{
	std::string path = FileSystem::Path::getFullFileSpec(pth);
	de_ = new DirExplorerE(path);
	fh_ = new FileHandler();
	dh_ = new DirHandler();
	de_->fileSubScribe(fh_);
	de_->dirSubScribe(dh_);
	if (pth.find("Convertedpages") == pth.npos)
	{
		de_->addPattern("*.h");
		de_->addPattern("*.cpp");
	}
	else {
		de_->addPattern("*.html");
	}
	if (!regex.empty()) {
		regex_ = regex;
	}

	de_->recurse();
	de_->search();

}

Loader::LoadFiles::~LoadFiles()
{
}

List Loader::LoadFiles::match(List files, List regex)
{
	std::vector<std::string> flist;

	if (!regex.empty()) {

		for (auto file : files) {
			std::string fname = Utilities::SplitFilename(file);
			for (auto re : regex)
			{
				std::regex reg(re);
				bool st = std::regex_match(fname, reg);
				if (st)
				{
					flist.push_back(file);
				}
			}
		}
	}
	else
		flist = files;
	return flist;
}

void Loader::LoadFiles::search()
{
	de_->search();
}

List Loader::LoadFiles::match()
{
	std::vector<std::string> flist;

	if (!regex_.empty()) {

		for (auto file : fh_->getfilelist()) {
			std::string fname = Utilities::SplitFilename(file);
			for (auto re : regex_)
			{
				std::regex reg(re);
				bool st = std::regex_match(fname, reg);
				if (st)
				{
					flist.push_back(file);
				}
			}
		}
	}
	else
		flist = fh_->getfilelist();
	return flist;
}

List Loader::LoadFiles::getfiles()
{
//	List files = match();
	return fh_->getfilelist();
}
List Loader::FileHandler::getfilelist()
{
	return filelist_;
}
void FileHandler::execute(const std::string & filename) {
	filelist_.push_back(filename);
}

void Loader::DirHandler::execute(const std::string & dirname)
{
}
#ifdef TEST_LOADER



int main() {
	std::string path = "../Display";
	List patterns = {"[a-fA-F](.*)"};
	LoadFiles lf(path,patterns);
	for (auto file : lf.getfiles()) {
		std::cout << "Files name :" << file << "\n";
	}
	LoadFiles fl(path);
	for (auto file : fl.getfiles()) {
		std::cout << "Files name :" << file << "\n";
	}
}
#endif // TEST_LOADER