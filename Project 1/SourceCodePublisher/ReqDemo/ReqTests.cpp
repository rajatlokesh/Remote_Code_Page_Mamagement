#include "..\Utilities\CodeUtilities\CodeUtilities.h"


#include "ReqTests.h"
#include "../Utilities/CodeUtilities/CodeUtilities.h"


Converter::Ut_function::Ut_function()
{
}

Converter::Ut_function::~Ut_function()
{
}

std::string Converter::Ut_function::SplitFilename(const std::string& str)
{
	/*std::cout << "Splitting: " << str << '\n';*/
	std::size_t found = str.find_last_of("/\\");
	/*std::cout << " path: " << str.substr(0, found) << '\n';
	std::cout << " file: " << str.substr(found + 1) << '\n';*/
	return str.substr(found + 1);
}

Converter::TestReq1::TestReq1(std::string name)
{
	name_ = name;
}

bool Converter::TestReq1::dotest()
{
	std::cout << "This window is open in Console Window and is compiled using VS2017 to compile..!!";
	return true;
}

std::string Converter::TestReq1::name()
{
	return name_;;
}

bool Converter::TestReq1::result()
{
	return result_;
}

void Converter::TestReq1::setresult(bool result)
{
	result_ = result;
}

Converter::TestReq1::~TestReq1()
{
}

Converter::TestReq2::TestReq2(std::string name)
{
	name_ = name;
}

bool Converter::TestReq2::dotest()
{
	std::string path = Path::getFullFileSpec("../");
	std::vector<std::string> files = Converter::Ut_function::DirExplorerSetup(path, {"*.h"});
	std::string file = files[5];
	File f(file);
	f.open(File::in);
	int i = 1;
	do {
		
		std::cout << f.getLine() << std::endl;
	} while (i <10);
	
	return false;
}

std::string Converter::TestReq2::name()
{
	return name_;
}

bool Converter::TestReq2::result()
{
	return result_;
}

void Converter::TestReq2::setresult(bool result)
{
	result_ = result;
}

Converter::TestReq2::~TestReq2()
{
}

Converter::TestReq3::TestReq3(std::string name)
{
	name_ = name;
}

bool Converter::TestReq3::dotest()
{
	bool result = false;
	std::string path = "../../";
	std::vector<std::string> files;
	std::vector<std::string> patterns = {"*.h","*.cpp"};	
	std::string preface;
	std::string body;
	preface += "\n There are total 8 C++ Packages ";
	preface += "\n The files belonging to these Packages are as follows..";
	preface += "\n\n";
	std::cout << preface << std::endl;
	Package1(body, path, files, patterns);
	Package2(body, path, files, patterns);
	Package3(body, path, files, patterns);
	Package4(body, path, files, patterns);
	Package5(body, path, files, patterns);
	Package6(body, path, files, patterns);
	Package7(body, path, files, patterns);
	Package8(body, path, files, patterns);
	body += "\n\n That is all for requirement 3...!!!";
	std::cout << body << std::endl;
	std::cout << "Requrement 3 Passed." << std::endl;
	result = true;
	return result;
}

void Converter::TestReq3::Package1(std::string &body, std::string &path, std::vector<std::string> &files, std::vector<std::string> &patterns)
{
	body += "\n1 -> Utilities => ";
	path = "../Utilities/";
	files = Converter::Ut_function::DirExplorerSetup(path, patterns);
	for (auto file : files) {
		std::string fname = Ut_function::SplitFilename(file);
		if (fname == "TestUtilities.h" || fname == "TestUtilities.cpp")
			continue;
		else
		{
			body += fname + ", ";
		}
			
	}
}

void Converter::TestReq3::Package2(std::string &body, std::string &path, std::vector<std::string> &files, std::vector<std::string> &patterns)
{
	body += "\n2 -> DirExplorer => ";
	path = "../DirExplorer/";
	files = Converter::Ut_function::DirExplorerSetup(path, patterns);
	for (auto file : files) {
		std::string fname = Ut_function::SplitFilename(file);
		body += fname+ ", ";
	}
}

void Converter::TestReq3::Package3(std::string &body, std::string &path, std::vector<std::string> &files, std::vector<std::string> &patterns)
{
	body += "\n3 -> FileSystem => ";
	path = "../FileSystem/";
	files = Converter::Ut_function::DirExplorerSetup(path, patterns);
	for (auto file : files) {
		std::string fname = Ut_function::SplitFilename(file);
		body += fname + ", ";
	}
}





void Converter::TestReq3::Package4(std::string &body, std::string &path, std::vector<std::string> &files, std::vector<std::string> &patterns)
{
	body += "\n5 -> Converter=> ";
	path = "../Converter/";
	files = Converter::Ut_function::DirExplorerSetup(path, patterns);
	for (auto file : files) {
		std::string fname = Ut_function::SplitFilename(file);
		body += fname + ", ";
	}
}

void Converter::TestReq3::Package5(std::string &body, std::string &path, std::vector<std::string> &files, std::vector<std::string> &patterns)
{
	body += "\n6 -> Display => ";
	path = "../Display/";
	files = Converter::Ut_function::DirExplorerSetup(path, patterns);
	for (auto file : files) {
		std::string fname = Ut_function::SplitFilename(file);
		body += fname + ", ";
	}
}

void Converter::TestReq3::Package6(std::string &body, std::string &path, std::vector<std::string> &files, std::vector<std::string> &patterns)
{
	body += "\n7 -> Executive => ";
	path = "../Executive/";
	files = Converter::Ut_function::DirExplorerSetup(path, patterns);
	for (auto file : files) {
		std::string fname = Ut_function::SplitFilename(file);
		body += fname + ", ";
	}
}

void Converter::TestReq3::Package7(std::string &body, std::string &path, std::vector<std::string> &files, std::vector<std::string> &patterns)
{
	body += "\n8 -> Requirements Demo => ";
	path = "../ReqDemo/";
	files = Converter::Ut_function::DirExplorerSetup(path, patterns);
	for (auto file : files) {
		std::string fname = Ut_function::SplitFilename(file);
		body += fname + ", ";
	}
}

void Converter::TestReq3::Package8(std::string &body, std::string &path, std::vector<std::string> &files, std::vector<std::string> &patterns)
{
	body += "\n9 -> Test Harness => ";
	path = "../TestHarness/";
	files = Converter::Ut_function::DirExplorerSetup(path, patterns);
	for (auto file : files) {
		std::string fname = Ut_function::SplitFilename(file);
		body += fname + ", ";
	}
}

std::string Converter::TestReq3::name()
{
	return name_;
}

bool Converter::TestReq3::result()
{
	return result_;
}

void Converter::TestReq3::setresult(bool result)
{
	result_ = result;
}

std::vector<std::string> Converter::Ut_function::DirExplorerSetup(std::string path, std::vector<std::string> pattern)
{
	DirExplorerN de(path);
	for (auto patt : pattern) {
		de.addPattern(patt);
	}
	de.recurse();
	de.search();
	
	return de.getfilelist();
}

Converter::TestReq3::~TestReq3()
{
}
