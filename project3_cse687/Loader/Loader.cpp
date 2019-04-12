/////////////////////////////////////////////////////////////////////
// Loader.cpp - directory explorer using events			           //
// ver 1.0                                                         //
// RAJAT Vyas, CSE687 - Object Oriented Design, Spring 2019        //
/////////////////////////////////////////////////////////////////////

#include "Loader.h"
#include"../Utility/CodeUtilities/CodeUtilities.h"
using namespace Loader;
Loader::LoadFiles::LoadFiles(const std::string &pth)
{
	path_ = pth;
	std::string path = FileSystem::Path::getFullFileSpec(pth);
	de_ = new DirExplorerE(path);
	fh_ = new FileHandler();
	dh_ = new DirHandler();
	de_->fileSubScribe(fh_);
	de_->dirSubScribe(dh_);
}

Loader::LoadFiles::~LoadFiles()
{
	delete de_;
}
void Loader::LoadFiles::search()
{
	de_->search();
}
List Loader::LoadFiles::getfiles()
{
//	List files = match();
	return fh_->getfilelist();
}
List Loader::LoadFiles::getselectedfiles()
{
	List files;
	try {
		std::regex re(regex_);
		for (auto file:fh_->getfilelist()) {
			bool res = std::regex_match(Utilities::SplitFilename(file), re);
			if (res) {
				files.push_back(file);
			}
		}
		return files;
	}
	catch (std::exception ex) {
		return files;
	}
}
void Loader::LoadFiles::setpatterns(List patterns)
{
	patterns_ = patterns;
}
void Loader::LoadFiles::setregex(const std::string & regex)
{
	regex_ = regex;
}
void Loader::LoadFiles::load()
{
	if (patterns_.empty()) {
		patterns_.push_back("*.cpp");
		patterns_.push_back("*.h");
	}
	for (auto patt : patterns_) {
		de_->addPattern(patt);
	}
	de_->recurse();
	de_->search();
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
	LoadFiles lf(path);
	lf.setregex(patterns[0]);
	lf.load();
	for (auto file : lf.getselectedfiles()) {
		std::cout << "Files name :" << file << "\n";
	}

}
#endif // TEST_LOADER