// TypeDetail.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include"TypeDetail.h"
using namespace TypeDetail;
#ifdef TEST_TYPEDETAIL
int main()
{
    std::cout << "Hello World!\n"; 
}
#endif // TEST_TYPEDETAIL
TypeDetail::Dependencies::Dependencies()
{
}

Dependencies::~Dependencies()
{
}

std::vector<std::string> Dependencies::getdependencies(const std::string & filename)
{
	return depend_[filename];
}

void Dependencies::adddependency(const std::string & filename, const std::string & dependency)
{
	if (depend_.find(filename) != depend_.end())
		depend_[filename].push_back(dependency);
	else
	{
		std::pair<std::string, std::vector<std::string>> p(filename, { dependency });
		depend_.insert(p);
	}
}

bool Dependencies::haskey(const std::string& filename)
{
	if (depend_.find(filename) != depend_.end())
		return true;
	return false;
}

std::vector<Typedata*> TypeInfo::GetInfo(const std::string& file_name) {
	try {
		if (Info_.find(file_name) != Info_.end()) {
			return Info_[file_name];
		}
	}
	catch(std::exception& ex){
		return std::vector<Typedata*>();
	}
	
}
TypeInfo* TypeDetail::TypeInfo::GetInfo()
{
	return this;
}
TypeDetail::TypeInfo::TypeInfo()
{
}
TypeDetail::TypeInfo::~TypeInfo()
{

}
void TypeInfo::AddInfo(const std::string& name, Typedata * const TI)
{
	if (Info_.find(name) == Info_.end()) {
		std::vector<Typedata*> temp{};
		std::pair<std::string, std::vector<Typedata*>>st(name, temp);
		Info_.insert(st);
	}

	if (TI->type_.find("class") != std::string::npos ||
		TI->type_.find("function") != std::string::npos) {
		Info_[name].push_back(TI);
	}

}