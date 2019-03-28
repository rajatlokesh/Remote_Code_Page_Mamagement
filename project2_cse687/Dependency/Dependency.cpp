//////////////////////////////////////////////////////////////////////////////////////////////////////////
// Dependency.cpp : This file contains the function body for header file.								//
//					Also has tester function.															//
//////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include "Dependency.h"
#ifdef TEST_DEPEND
int main()
{
    std::cout << "Hello World!\n"; 
}
#endif


Dependency::Dependencies::~Dependencies()
{
}

std::vector<std::string> Dependency::Dependencies::getdependencies(const std::string & filename)
{
	return dependencies_[filename];
}

void Dependency::Dependencies::adddependency(const std::string & filename, const std::string & dependency)
{
	if (dependencies_.find(filename) != dependencies_.end())
		dependencies_[filename].push_back(dependency);
	else
	{
		std::pair<std::string, std::vector<std::string>> p(filename, { dependency });
		dependencies_.insert(p);
	}
}

bool Dependency::Dependencies::haskey(std::string filename)
{
	if (dependencies_.find(filename) !=dependencies_.end())
		return true;
	return false;
}

