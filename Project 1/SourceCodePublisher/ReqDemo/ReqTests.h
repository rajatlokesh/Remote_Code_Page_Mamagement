#pragma once
#include"../TestHarness/TestHarness.h"
#include"../DirExplorer/DirExplorerN.h"
#include <iostream>
#include<vector>
using namespace TestHarness;
using namespace FileSystem;
namespace Converter {
	class Ut_function
	{
	public:
		Ut_function();
		~Ut_function();

		static std::string SplitFilename(const std::string & str);

		static std::vector<std::string> DirExplorerSetup(std::string path, std::vector<std::string> pattern);

	private:

	};
	class TestReq1:public ITest
	{
	public:
		TestReq1(std::string name);
		bool dotest();
		std::string name();
		bool result();
		void setresult(bool result);
		~TestReq1();


	private:
		std::string name_;
		bool result_;
	};
	class TestReq2 :public ITest
	{
	public:
		TestReq2(std::string name);
		bool dotest();
		std::string name();
		bool result();
		void setresult(bool result);
		~TestReq2();


	private:
		std::string name_;
		bool result_;
	};

	class TestReq3 :public ITest
	{
	public:
		TestReq3(std::string name);
		bool dotest();
		void Package1(std::string & body, std::string & path, std::vector<std::string>& files, std::vector<std::string>& patterns);
		void Package2(std::string & body, std::string & path, std::vector<std::string>& files, std::vector<std::string>& patterns);
		void Package3(std::string & body, std::string & path, std::vector<std::string>& files, std::vector<std::string>& patterns);
		void Package4(std::string & body, std::string & path, std::vector<std::string>& files, std::vector<std::string>& patterns);
		void Package5(std::string & body, std::string & path, std::vector<std::string>& files, std::vector<std::string>& patterns);
		void Package6(std::string & body, std::string & path, std::vector<std::string>& files, std::vector<std::string>& patterns);
		void Package7(std::string & body, std::string & path, std::vector<std::string>& files, std::vector<std::string>& patterns);
		void Package8(std::string & body, std::string & path, std::vector<std::string>& files, std::vector<std::string>& patterns);
		std::string name();
		bool result();
		void setresult(bool result);
		~TestReq3();


	private:
		std::string name_;
		bool result_;
	};
}