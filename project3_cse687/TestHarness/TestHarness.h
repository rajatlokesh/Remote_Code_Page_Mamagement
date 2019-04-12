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
	inline Tester::Tester() :result_(true), tests_()
	{
	}

	inline void Tester::add(ITest* test)
	{
		tests_.push_back(test);
	}

	inline void Tester::clear()
	{
		tests_.clear();
	}

	inline void Tester::execute()
	{

		for (auto test : tests_)
		{
			Executor::check(Executor::execute(test), test->name());
			if (test->result() == false)
				result_ = false;
		}
	}

	inline void Tester::check()
	{
		if (result_)
		{
			std::cout << "All test passed!" << std::endl;
		}
		else {
			std::cout << "One or more test failed" << std::endl;
		}
	}

	inline Tester::~Tester() {}

	inline bool Executor::execute(ITest* test)
	{
		bool result = false;
		try
		{
			result = test->dotest();
			test->setresult(result);
		}
		catch (const std::exception&)
		{
			test->result();
		}

		return result;
	}

	inline void Executor::check(bool result, std::string name)
	{
		if (result) {
			std::cout << "\n passed ---" << name << std::endl;
		}
		else {
			std::cout << "\n failed ---" << name << std::endl;
		}

	}
}

