#pragma once

#include<iostream>
#include<string>
#include<list>


namespace TestHarness {
	class ITest
	{
	public:
		ITest() {};
		virtual std::string name() = 0;
		virtual bool dotest() = 0;
		virtual bool result() = 0;
		virtual void setresult(bool r) = 0;
		virtual ~ITest() {};



	};
	class Tester
	{
	public:
		Tester();
		void add(ITest* test);
		void clear();
		void execute();
		void check();
		~Tester();

	private:
		std::list<ITest*> tests_;
		bool result_;
	}; 
	class Executor 
	{
	public:
		static bool execute(ITest* test);
		static void check(bool result, std::string name);

	};
	class Test1 :public ITest
	{
	public:
		Test1(std::string );
		~Test1();
		bool dotest();
		bool result();
		void setresult(bool r);
		std::string name();
	private:
		std::string name_;
		bool result_;
	};
	class Test2 :public ITest
	{
	public:
		Test2(std::string);
		~Test2();
		bool dotest();
		bool result();
		void setresult(bool r);
		std::string name();
	private:
		std::string name_;
		bool result_;
	};
}

