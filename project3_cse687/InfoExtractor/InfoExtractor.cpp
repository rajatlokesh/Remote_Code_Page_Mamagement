// InfoExtractor.cpp : This file contains the test stub and definition of the declared functions in .h
// Required Files ../Loader/Loader.h
// Configparser.h

#include "pch.h"
#include <iostream>
#include"InfoExtractor.h"
#include"../Loader/Loader.h"
#include"../Parser/Parser/ConfigureParser.h"
#ifdef TEST_EXTRACTOR



int main()
{
    std::cout << "Hello World!\n";
	vector<string> filelist = {};
	string file= "../InfoExtractor/InfoExtractor.h";
	filelist.push_back(FileSystem::Path::getFullFileSpec(file));
	InfoExtractor::FileTypeInfo ft(filelist);
	ft.parse();
	TypeInfo* td = ft.getinfo();
	std::vector<Typedata*> ts = td->GetInfo(Utilities::SplitFilename(file));
	for (auto t : ts) {
		t->type_;
	}
}
#endif // TEST_EXTRACTOR
InfoExtractor::FileTypeInfo::FileTypeInfo(vector<string> flst)
{
	filelist_ = flst;
	ti_ = new TypeDetail::TypeInfo();
	dep_ = new TypeDetail::Dependencies();
}
InfoExtractor::FileTypeInfo::~FileTypeInfo()
{
	delete ti_;
	delete dep_;
}

const std::vector<std::string>& InfoExtractor::FileTypeInfo::filelist()
{
	return filelist_;
}
void InfoExtractor::FileTypeInfo::parse() {
	std::string filespec;
	for (auto file : filelist_) {
		filespec = FileSystem::Path::getFullFileSpec(file);
		CodeAnalysis::ConfigParseForCodeAnal configure;
		CodeAnalysis::Parser * pParser = configure.Build();
		std::string name;
		try {
			if (pParser) {
				name = FileSystem::Path::getName(file);
				if (!configure.Attach(filespec)) {
					std::cout << "\n couldnt open file";
					continue;
				}
			}
			else {
				std::cout << "\n\n Parser not built..!!\n\n";
				break;
			}
			CodeAnalysis::Repository* pRepo = CodeAnalysis::Repository::getInstance();
			pRepo->package() = name;
			while (pParser->next()) {
				pParser->parse();
			}
			//std::cout << "\n";
			CodeAnalysis::ASTNode* pGlobalScope = pRepo->getGlobalScope();
			CodeAnalysis::complexityEval(pGlobalScope);
			//CodeAnalysis::TreeWalk(pGlobalScope);
			treeWalk(pGlobalScope, name);
			extractIncludes(pGlobalScope, name);

		}
		catch (std::exception& ex) {
			std::cout << "\n\n    " << ex.what() << "\n\n";
			std::cout << "\n  exception caught at line " << __LINE__ << " ";
			std::cout << "\n  in package \"" << name << "\"";
		}
	}
}

TypeDetail::TypeInfo * InfoExtractor::FileTypeInfo::getinfo()
{
	return ti_;
}

TypeDetail::Dependencies * InfoExtractor::FileTypeInfo::getDepend()
{
	return dep_;
}


