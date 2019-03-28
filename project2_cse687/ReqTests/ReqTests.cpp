///////////////////////////////////////////////////////////////////////
// ReqTests.cpp - Functional Requirements one by one                 //
// ver 1.0                                                           //
// Author - Rajat Vyas												 //
// Provided by - Jim Fawcett, CSE687								 //
///////////////////////////////////////////////////////////////////////

#include "ReqTests.h"
using namespace HtmlConverter;
using namespace TestHarness;
using namespace FileSystem;
using namespace Utilities;
using namespace Demo_Request;

std::string Demo_Request::SplitFilename(const std::string & str)
{
	std::size_t found = str.find_last_of("/\\");
	return str.substr(found + 1);
}

std::vector<std::string> Demo_Request::DirExplorerSetup(std::string path, std::vector<std::string> pattern)
{
	Loader::LoadFiles loadfiles(path);
	std::vector<std::string> flst = loadfiles.getfiles();
	return flst;
}


 TestReq1::TestReq1(std::string name)
{
	name_ = name;
}

bool  TestReq1::dotest()
{
	std::cout << std::string(100, '-') ;
	std::cout<<"\n"<<name() << "\n";
	std::cout << std::string(100, '-') << "\n";
	std::cout << "This window is open in Console Window and is compiled using VS2017 to compile..!!";
	return true;
}

std::string  TestReq1::name()
{
	return name_;;
}

bool  TestReq1::result()
{
	return result_;
}

void  TestReq1::setresult(bool result)
{
	result_ = result;
}

 TestReq1::~TestReq1()
{
}

 TestReq2::TestReq2(std::string name)
{
	name_ = name;
}

bool  TestReq2::dotest()
{
	
	std::cout << std::string(100,'-') ;
	std::cout <<"\n"<< name() << "\n";
	std::cout << std::string(100, '-') << "\n";
	std::cout << "Header files included in one of the files is:\n";
	std::string path = Path::getFullFileSpec("../FileSystem");
	std::vector<std::string> files =  DirExplorerSetup(path);
	std::string file ;
	for (auto fi : files) {
		std::string temp = Demo_Request::SplitFilename(fi);
		if (temp == "FileSystem.cpp")
			file = fi;
	}
	File f(file);
	f.open(File::in);
	for (int i = 1; i < 22;++i){
		if (i > 15)
			std::cout << f.getLine() << std::endl;
		else
			f.getLine();
	} ;
	std::cout << "This satisfy requirement 2";
	setresult(true);
	return result();
}

std::string  TestReq2::name()
{
	return name_;
}

bool  TestReq2::result()
{
	return result_;
}

void  TestReq2::setresult(bool result)
{
	result_ = result;
}

 TestReq2::~TestReq2()
{
}

 TestReq4::TestReq4(std::string name)
{
	name_ = name;
}

bool  TestReq4::dotest()
{

	bool result = false;
	std::string path = "../../";
	std::vector<std::string> files;	
	std::string preface;
	std::string body;
	std::cout << std::string(100,'-') << "\n";
	std::cout <<"\n"<< name()<<"   packages" << "\n";
	std::cout << std::string(100, '-');
	preface += "\n There are total 9 C++ Packages ";
	preface += "\n The files belonging to these Packages are as follows..";
	preface += "\n";
	std::cout << preface << std::endl;
	Package1(body, path, files);
	Package2(body, path, files);
	Package3(body, path, files);
	Package4(body, path, files);
	Package5(body, path, files);
	Package6(body, path, files);
	Package7(body, path, files);
	Package8(body, path, files);
	Package9(body, path, files);
	Package10(body, path, files);
	Package11(body, path, files);
	body += "\n\n That is all for requirement 4...!!!";
	std::cout << body << std::endl;
	std::cout << "Requrement 4 Passed." << std::endl;
	result = true;
	return result;
}

void  TestReq4::Package1(std::string &body, std::string &path, std::vector<std::string> &files)
{
	body += "\n1 -> Utilities => ";
	path = "../Utility/";
	files = DirExplorerSetup(path);
	files = DirExplorerSetup(path);
	for (auto file : files) {
		std::string fname = SplitFilename(file);
		if (fname == "TestUtilities.h" || fname == "TestUtilities.cpp")
			continue;
		else
		{
			body += fname + ", ";
		}
			
	}
}

void  TestReq4::Package9(std::string &body, std::string &path, std::vector<std::string> &files)
{
	body += "\n9 -> Process => ";
	path = "../Process/";
	files = DirExplorerSetup(path);
	for (auto file : files) {
		std::string fname = SplitFilename(file);
		body += fname + ", ";

	}
}

void  TestReq4::Package2(std::string &body, std::string &path, std::vector<std::string> &files)
{
	body += "\n2 -> DirExplorer => ";
	path = "../DirExplorer-Events/";
	files =  DirExplorerSetup(path);
	for (auto file : files) {
		std::string fname = SplitFilename(file);
		body += fname+ ", ";
	}
}

void  TestReq4::Package3(std::string &body, std::string &path, std::vector<std::string> &files)
{
	body += "\n3 -> FileSystem => ";
	path = "../FileSystem/";
	files =  DirExplorerSetup(path);
	for (auto file : files) {
		std::string fname = SplitFilename(file);
		body += fname + ", ";
	}
}

void  TestReq4::Package4(std::string &body, std::string &path, std::vector<std::string> &files)
{
	body += "\n4 -> Converter=> ";
	path = "../Converter/";
	files = DirExplorerSetup(path);
	for (auto file : files) {
		std::string fname = SplitFilename(file);
		body += fname + ", ";
	}
}

void  TestReq4::Package5(std::string &body, std::string &path, std::vector<std::string> &files)
{
	body += "\n5 -> Display => ";
	path = "../Display/";
	files = DirExplorerSetup(path);
	for (auto file : files) {
		std::string fname = SplitFilename(file);
		body += fname + ", ";
	}
}

void  TestReq4::Package6(std::string &body, std::string &path, std::vector<std::string> &files)
{
	body += "\n6 -> Executive => ";
	path = "../Executive/";
	files = DirExplorerSetup(path);
	for (auto file : files) {
		std::string fname = SplitFilename(file);
		body += fname + ", ";
	}
}

void  TestReq4::Package7(std::string &body, std::string &path, std::vector<std::string> &files)
{
	body += "\n7 -> Requirements Demo => ";
	path = "../ReqTests/";
	files = DirExplorerSetup(path);
	for (auto file : files) {
		std::string fname = SplitFilename(file);
		body += fname + ", ";
	}
}

void  TestReq4::Package8(std::string &body, std::string &path, std::vector<std::string> &files)
{
	body += "\n8 -> Test Harness => ";
	path = "../TestHarness/";
	files = DirExplorerSetup(path);
	for (auto file : files) {
		std::string fname = SplitFilename(file);
		body += fname + ", ";
	}
}

void  TestReq4::Package10(std::string &body, std::string &path, std::vector<std::string> &files)
{
	body += "\n10 -> Loader => ";
	path = "../Loader/";
	files = DirExplorerSetup(path);
	for (auto file : files) {
		std::string fname = SplitFilename(file);
		body += fname + ", ";
	}
}
void  TestReq4::Package11(std::string &body, std::string &path, std::vector<std::string> &files)
{
	body += "\n11 -> Parser => ";
	path = "../Parser/";
	files = DirExplorerSetup(path);
	for (auto file : files) {
		std::string fname = SplitFilename(file);
		body += fname + ", ";
	}
}

std::string  TestReq4::name()
{
	return name_;
}

bool  TestReq4::result()
{
	return result_;
}
 
void  TestReq4::setresult(bool result)
{
	result_ = result;
}


 TestReq4::~TestReq4()
{
}

 TestReq3::TestReq3(std::string name)
{
	name_ = name;
}

bool  TestReq3::dotest()
{
	std::cout << std::string(100, '-') << "\n";
	std::cout << "\n"<<name()<<"    Exectuive pacage accepting path and regex as c.l.a. " << "\n";
	std::cout << std::string(100, '-') << "\n";
	std::cout << " The Command Line Arguments are as follows:-\n";
	std::cout<<" Path : "<< Path::getFullFileSpec(pcl_->path());
	for (auto patt : pcl_->patterns()) {
		bool st = std::regex_match(patt, std::regex(".*.exe"));
		if (!st) {
			std::cout << "\n Regex: "<< patt;
		}
		else
			std::cout<<"\n App Path: "<< patt;
	}
	std::cout << "\n";
	setresult(true);
	std::cout << "Requrement 3 Passed." << std::endl;
	return result();
}

std::string  TestReq3::name()
{
	return name_;
}

bool  TestReq3::result()
{
	return result_;
}

void  TestReq3::setresult(bool result)
{
	result_ = result;
}

 TestReq3::~TestReq3()
{
}

void  TestReq3::addcmd(Utilities::ProcessCmdLine* pcl)
{
	pcl_ = pcl;
}

TestReq5::TestReq5(std::string name)
{
	name_ = name;
}

bool TestReq5::dotest()
{
	std::string path = "../Testfiles";
	std::string app_path;
	std::vector<std::string> patterns = pcl_->patterns();
	int i = 0;
	std::cout << std::string(100, '-') << "\n";
	std::cout << "\n" << name() <<"    Loader Package functionality"<< "\n";
	std::cout << std::string(100, '-') << "\n";
	std::cout << "Command Line Arguments passed to executive are :\n";
	std::cout << " Path : " << Path::getFullFileSpec(path);
	for (auto patt : pcl_->patterns()) {
		bool st = std::regex_match(patt, std::regex(".*.exe"));
		if (!st) {
			std::cout << "\n Regex: " << patt;
		}
		else
			std::cout << "\n App Path: " << patt;
	};
	std::cout << "\n";
	for (auto patt : patterns) {
		if (std::regex_match(patt, std::regex(".*.exe$"))) {
			app_path = patt;
			patterns.erase(patterns.begin() + i);
		}
		i++;

	}
	std::cout << "\ncall made to executive to initiate loader package using function:" <<
		"Executive::execute(path, app_path, patterns, -1)" <<"\n";
	Executive::execute(path,app_path,patterns,-1);
	return true;
}


std::string TestReq6::name()
{
	return std::string(name_);
}

bool TestReq6::result()
{
	return result_;
}

void TestReq6::setresult(bool result)
{
	result_ = result;
}
void  TestReq6::addcmd(Utilities::ProcessCmdLine* pcl)
{
	pcl_ = pcl;
}
TestReq6::~TestReq6()
{
}

TestReq6::TestReq6(std::string name)
{
	name_ = name;
}

bool TestReq6::dotest()
{
	std::string path = Path::getFullFileSpec("ReqTest.h");
	std::string app_path;
	std::vector<std::string>patterns;
	std::cout << std::string(100, '-') << "\n";
	std::cout << "\n" << name() << "   converting < with &lt; and > with &gt; and adding HTML wrapper"<< "\n";
	std::cout << std::string(100, '-') << "\n";
	Executive::execute(path, app_path, patterns,0);
	return true;
}


std::string TestReq5::name()
{
	return std::string(name_);
}

bool TestReq5::result()
{
	return result_;
}
std::string TestReq7::name()
{
	return std::string(name_);
}

bool TestReq7::result()
{
	return result_;
}

void TestReq7::setresult(bool result)
{
	result_ = result;
}
void  TestReq7::addcmd(Utilities::ProcessCmdLine* pcl)
{
	pcl_ = pcl;
}
TestReq7::~TestReq7()
{
}

TestReq7::TestReq7(std::string name)
{
	name_ = name;
}

bool TestReq7::dotest()
{
	std::string path = Path::getFullFileSpec(pcl_->path());
	std::string app_path;
	std::vector<std::string> patterns = pcl_->patterns();
	int i = 0;
	std::cout << std::string(100, '-') << "\n";
	std::cout << "\n" << name() <<"and Req 8      Adding dependencies and adding class, function and comment wrapper"<< "\n";
	std::cout << std::string(100, '-') << "\n";
	for (auto patt : patterns) {
		if (std::regex_match(patt, std::regex(".*.exe$"))) {
			app_path = patt;
			patterns.erase(patterns.begin() + i);
		}
		i++;
	}
	Executive::execute(path, app_path, patterns, 1);
	return true;
}



void TestReq5::setresult(bool result)
{
	result_ = result;
}
void  TestReq5::addcmd(Utilities::ProcessCmdLine* pcl)
{
	pcl_ = pcl;
}
TestReq5::~TestReq5()
{
}

#ifdef TEST_REQ


int main(int argc, char * argv[]) {
	ProcessCmdLine pcl(argc, argv);
	Tester* test = new Tester();
	TestReq1* tr1 = new TestReq1("Req 1");
	test->add(tr1);
	TestReq2* tr2 = new TestReq2("Req 2");
	test->add(tr2);
	TestReq3* tr3 = new TestReq3("Req 3");
	tr3->addcmd(&pcl);
	test->add(tr3);
	TestReq4* tr4 = new TestReq4("Req 4");
	test->add(tr4);
	TestReq5* tr5 = new TestReq5("Req 5");
	tr5->addcmd(&pcl);
	test->add(tr5);
	TestReq6* tr6 = new TestReq6("Req 6");
	tr6->addcmd(&pcl);
	test->add(tr6);
	TestReq7* tr7 = new TestReq7("Req 7");
	tr7->addcmd(&pcl);
	test->add(tr7);
	test->execute();
	std::cout << std::string(100, '-') << "\n";
	std::cout << "\n" << "Req 9    Automated Test suit." << "\n";
	std::cout << std::string(100, '-') << "\n As all this runs on automated test suit req 8 met..!!\n Passed Req 8";
	std::cin.get();
	return 0;
}
#endif