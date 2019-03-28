#pragma once
////////////////////////////////////////////////////////////////////////
// ReqTests.h -  class used to start process                          //
// ver 1.0                                                            //
// Author -	    Rajat Vyas		ravyas@syr.edu						  //
// Provided by -Jim Fawcett, CSE687 - OOD, Spring 2019		          //
////////////////////////////////////////////////////////////////////////
/*
*  Package Operations:
*  -------------------
*  This package makes test requests and and satify differtent requirements of the projects.
*  Functional Requirements on by one.
*  This package have TestReq classes which are inheriting interfaces ITest.
*  Classes: TestReq 1 - 8
*
* Functions: bool dotest()
*
*  Required Files:
*  ---------------
*  Execute.h, Execute.cpp
*  TestHarness.h, TestHarness.cpp
*  FileSystem.h, FileSystem.cpp
*  CodeUtilites.h, CodeUtilites.cpp
*  DirExpolrerN.h, DirExpolrerN.cpp
*
*  Maintenance History:
*  --------------------
*  ver 1.0 : 19 Feb 2018
*  - first release
*/
#include"../TestHarness/TestHarness.h"
#include"../Utility/CodeUtilities/CodeUtilities.h"
#include"../Executive/Executive.h"
#include <iostream>
#include<vector>
#include<regex>


namespace Demo_Request {

		static std::string SplitFilename(const std::string & str);
		static std::vector<std::string> DirExplorerSetup(std::string path, std::vector<std::string> pattern = {});	
		//...............<Requirement 1 Testcase>----------------------------------------------------------
		class TestReq1 :public TestHarness::ITest
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
		//...............<Requirement 2 Testcase>----------------------------------------------------------
		class TestReq2 :public TestHarness::ITest
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
		//...............<Requirement 4 Testcase>----------------------------------------------------------
		class TestReq4 :public TestHarness::ITest
		{
		public:
			TestReq4(std::string name);
			bool dotest();
			void Package1(std::string & body, std::string & path, std::vector<std::string>& files);
			void Package2(std::string & body, std::string & path, std::vector<std::string>& files);
			void Package3(std::string & body, std::string & path, std::vector<std::string>& files);
			void Package4(std::string & body, std::string & path, std::vector<std::string>& files);
			void Package5(std::string & body, std::string & path, std::vector<std::string>& files);
			void Package6(std::string & body, std::string & path, std::vector<std::string>& files);
			void Package7(std::string & body, std::string & path, std::vector<std::string>& files);
			void Package8(std::string & body, std::string & path, std::vector<std::string>& files);
			void Package9(std::string & body, std::string & path, std::vector<std::string>& files);
			void Package10(std::string & body, std::string & path, std::vector<std::string>& files);
			void Package11(std::string & body, std::string & path, std::vector<std::string>& files);
			void Package12(std::string & body, std::string & path, std::vector<std::string>& files);
			std::string name();
			bool result();
			void setresult(bool result);
			~TestReq4();


		private:
			std::string name_;
			bool result_;
		};
		//...............<Requirement 3 Testcase>----------------------------------------------------------
		class TestReq3 :public TestHarness::ITest
		{
		public:
			TestReq3(std::string name);
			bool dotest();
			std::string name();
			bool result();
			void setresult(bool result);
			~TestReq3();
			void addcmd(Utilities::ProcessCmdLine* pcl);

		private:
			std::string name_;
			bool result_;
			Utilities::ProcessCmdLine* pcl_;
		};
		//...............<Requirement 5 Testcase>----------------------------------------------------------
		class TestReq5 :public TestHarness::ITest
		{
		public:
			TestReq5(std::string name);
			bool dotest();
			std::string name();
			bool result();
			void setresult(bool result);
			void addcmd(Utilities::ProcessCmdLine* pcl);
			~TestReq5();

		private:
			std::string name_;
			bool result_;
			Utilities::ProcessCmdLine* pcl_;
		};
		//...............<Requirement 6 Testcase>----------------------------------------------------------
		class TestReq6 :public TestHarness::ITest
		{
		public:
			TestReq6(std::string name);
			bool dotest();
			std::string name();
			bool result();
			void setresult(bool result);
			void addcmd(Utilities::ProcessCmdLine* pcl);
			~TestReq6();

		private:
			std::string name_;
			bool result_;
			Utilities::ProcessCmdLine* pcl_;
		};
		//...............<Requirement 7 Testcase>----------------------------------------------------------
		class TestReq7 :public TestHarness::ITest
		{
		public:
			TestReq7(std::string name);
			bool dotest();
			std::string name();
			bool result();
			void setresult(bool result);
			void addcmd(Utilities::ProcessCmdLine* pcl);
			~TestReq7();

		private:
			std::string name_;
			bool result_;
			Utilities::ProcessCmdLine* pcl_;
		};
		//...............<Requirement 8 Testcase>----------------------------------------------------------
}