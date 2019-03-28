#include "TestHarness.h"

using namespace TestHarness;
Tester::Tester() :result_(true), tests_()
{
}

void Tester::add(ITest* test)
{
	tests_.push_back(test);
}

void Tester::clear()
{
	tests_.clear();
}

void Tester::execute()
{
	
	for(auto test :tests_)
	{
		Executor::check(Executor::execute(test), test->name());
		if (test->result() == false)
			result_ = false;
	}
}

void Tester::check()
{
	if (result_)
	{
		std::cout << "All test passed!" << std::endl;
	}
	else {
		std::cout << "One or more test failed" << std::endl;
	}
}

Tester::~Tester() {}

bool Executor::execute(ITest* test )
{
	bool result = false;
	try
	{
		result = test->dotest();
		test->setresult(result);
	}
	catch (const std::exception&)
	{
		test->result() ;
	}
	
	return result;
}

void Executor::check(bool result, std::string name)
{
	if (result) {
		std::cout << "\n passed ---" << name << std::endl;
	}
	else {
		std::cout << "\n failed ---" << name << std::endl;
	}

}

Test1::Test1(std::string name) {
	name_ = name;
}

bool Test1::dotest() {
	return true;
}

bool Test1::result() {
	return result_;
}

void TestHarness::Test1::setresult(bool r)
{
	result_ = r;
}

std::string Test1::name() {
	return name_;
}
Test1::~Test1() {}

#include<iostream>
#ifdef TEST_HARNESS



int main() {
	ITest* t1 = new Test1("Test1-- !") ;
	Executor::check(Executor::execute(t1), t1->name());
	Tester* tester = new Tester();
	tester->add(t1);
	tester->execute();
	tester->check();
	std::cin.ignore();
	return 0;
}

#endif //TEST_HARNESS