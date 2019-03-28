#include "TestHarness.h"

using namespace TestHarness;
#include<iostream>
#ifdef TEST_HARNESS
class Test1 :public ITest
{
public:
	Test1(std::string);
	~Test1();
	bool dotest();
	bool result();
	void setresult(bool r);
	std::string name();
private:
	std::string name_;
	bool result_;
};

Test1::Test1(std::string name) {
	name_ = name;
}

bool Test1::dotest() {
	return true;
}

bool Test1::result() {
	return result_;
}

void Test1::setresult(bool r)
{
	result_ = r;
}

std::string Test1::name() {
	return name_;
}
Test1::~Test1() {}





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