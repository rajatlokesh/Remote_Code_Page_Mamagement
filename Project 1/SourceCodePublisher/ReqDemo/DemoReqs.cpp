#include "DemoReqs.h"


int main(int argc, char * argv[]) {
	/*ProcessCmdLine pcl(argc, argv);*/
	Tester* test = new Tester();
	TestReq1* tr1 = new TestReq1("Req 1");
	test->add(tr1);
	TestReq2* tr2 = new TestReq2("Req 2");
	test->add(tr2);
	TestReq3* tr3 = new TestReq3("Req 3");
	test->add(tr3);
	test->execute();
	return 0;
}