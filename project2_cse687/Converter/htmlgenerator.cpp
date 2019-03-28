/////////////////////////////////////////////////////////////////////
// htmlgenerator.cpp - Holds function for header file,			   //	 
//					   also have a test suite.					   //
// ver 1.1                                                         //
// RAJAT Vyas, CSE687 - Object Oriented Design, Spring 2019        //
/////////////////////////////////////////////////////////////////////
#include <iostream>
#include "htmlgenerator.h"
#include"../Utility/StringUtilities/StringUtilities.h"
using namespace HtmlConverter;
#ifdef TEST_CONVERTER
int main()
{
	HtmlConverter::HtmlGenerator ge("../Convertedpages");
    std::cout << "Hello World!\n"; 
	ge.convert(std::vector<std::string>{ FileSystem::Path::getFullFileSpec("../Parser/Parser/Parser.h") });
}
#endif // TEST_CONVERTER
//-----------------<Constructer sets the converter to an folder>----------------------------------
HtmlGenerator::HtmlGenerator(std::string path)
{
	std::string pth_ = FileSystem::Path::getFullFileSpec(path);
	if (!FileSystem::Directory::exists(pth_)) {
		FileSystem::Directory::create(pth_);
	}
	path_ = pth_;
	special_ = false;
	dep_ = new Dependency::Dependencies();
}
std::string HtmlGenerator::f_path() {
	return path_;
}
HtmlGenerator::~HtmlGenerator()
{
}
//---------------------<takes a file and save its html file to the path>---------------------------
bool HtmlGenerator::convert(std::string file)
{
	std::string filename = Utilities::SplitFilename(file);
	std::string path = path_+"\\"+filename+".html";
	std::string temp;
	std::string header;
	std::vector<Type_Info*> ti = Info_[filename];
	if (FileSystem::Directory::exists(path)) {
		FileSystem::Directory::remove(path);
	}
	FileSystem::File fwrite(path);
	FileSystem::File fread(file);
	FileSystem::File fhead(FileSystem::Path::getFullFileSpec("../Header/header.html"));
	fhead.open(FileSystem::File::in, FileSystem::File::text);
	if (fhead.isGood())
	{
		header = fhead.readAll(true);
	}
	else
	{
		header = "Error in header read file..!!";
	}
	fhead.close();
	fread.open(FileSystem::File::in, FileSystem::File::text);
	int linecount = 0;
	std::string tem;
	while (fread.isGood()) {
		temp = fread.getLine();
		linecount++;
		temp = tegset(temp);
		if (special_ == true)
			temp = Specialcases(temp,ti,linecount);
		tem.append(temp).append("\n");
	}
	header.replace(header.find("PageHeader"),10,Utilities::SplitFilename(file));
	fwrite.open(FileSystem::File::out, FileSystem::File::text);
	if (fwrite.isGood() && temp != "Error reading file!!" && !header.empty()) {
		fwrite.putLine(header);
		fwrite.putLine(depend_add(Utilities::SplitFilename(file)));
		fwrite.putLine(tem);
		fwrite.putLine("</pre>\n</body>\n</html>");
	}
	else {
		std::cout << "Error in writing file..!!"<<std::endl;
		return false;
	}
	fwrite.close();
	return true;
}
bool  HtmlGenerator::convert(std::vector<std::string> filelist)
{
	bool result = true;
	parse(filelist);
	
	for (auto file : filelist) {
		result = convert(file);
			if(!result)
				break;
	}
	return result;
}
void  HtmlGenerator::parse(std::vector<std::string> filelist)
{
	std::string filespec;
	for (auto file : filelist) {
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
			std::cout << "\n";
			CodeAnalysis::ASTNode* pGlobalScope = pRepo->getGlobalScope();
			CodeAnalysis::complexityEval(pGlobalScope);
			//CodeAnalysis::TreeWalk(pGlobalScope);
			InfoExtract(pGlobalScope,name);
			DependencyExtractor(pGlobalScope, name);
			
		}
		catch (std::exception& ex) {
			std::cout << "\n\n    " << ex.what() << "\n\n";
			std::cout << "\n  exception caught at line " << __LINE__ << " ";
			std::cout << "\n  in package \"" << name << "\"";
		}
	}
}
void HtmlConverter::HtmlGenerator::InfoExtract(CodeAnalysis::ASTNode * pGlobalScope,std::string name)
{
	Type_Info* ti = new Type_Info();
	ti->type_name = name+"_"+pGlobalScope->name_;
	ti->startline_ = pGlobalScope->startLineCount_;
	ti->endline_ = pGlobalScope->endLineCount_;
	ti->type_ = pGlobalScope->type_;
	setInfo(name, ti);
	
	auto iter = pGlobalScope->children_.begin();
	while (iter != pGlobalScope->children_.end()) {
		InfoExtract(*iter,name);
		++iter;
	}
}
std::vector<std::string> HtmlConverter::HtmlGenerator::DependencyExtractor(CodeAnalysis::ASTNode * pGlobalScope, const std::string& filename)
{
	std::vector<std::string> dependencies;
	auto temp = pGlobalScope->statements_;
	if (temp.size() != 0) {
		for (auto t : temp)
		{
			std::string tp = t->ToString();
			if (t->hasSequence({ "#","include" }) && tp.find("\"") != tp.npos) {
				dep_->adddependency(filename,tp.substr(tp.find("\"") + 1, tp.rfind("\"") - tp.find("\"") - 1));
			}
		}
	}
	return dependencies;
}
std::vector<Type_Info*> HtmlGenerator::getInfo(std::string type_name) {
	if (Info_.find(type_name) != Info_.end()) {
		return Info_[type_name];
	}
	return std::vector<Type_Info*>();
}
void HtmlConverter::HtmlGenerator::setInfo(std::string name, Type_Info * TI)
{
	if (Info_.find(name) == Info_.end()) {
		std::vector<Type_Info*> temp{};
		std::pair<std::string, std::vector<Type_Info*>>st(name, temp);
		Info_.insert(st);
	}

	if (TI->type_.find("class") != std::string::npos|| 
		TI->type_.find("function") != std::string::npos) {
			Info_[name].push_back(TI);			
	}

}
std::string HtmlConverter::HtmlGenerator::Specialcases(std::string temp, std::vector<Type_Info*> ti, int linecount)
{
	for (auto t : ti) {
		if (temp.find(Utilities::split(t->type_name, '_').back()) != std::string::npos) {
			if (t->startline_ == linecount) {
				if (temp.find('{') != temp.npos) {
					std::string rep = "<div class= \"" + t->type_ + "_div\">{";
					temp.replace(temp.find('{'), 1, rep);
				}
			}
			if (t->startline_ == linecount + 1)
			{
				std::string rep = "<div class= \"" + t->type_ + "_div\">";
				temp.append(rep);
			}
		}
		if (t->endline_ == linecount || t->endline_ == linecount + 1 && t->type_ != "namespace")
		{
			if(temp.find("}")!= temp.npos)
				temp.replace(temp.find("}"),1,"}</div>");
		}
	}
	temp = comment(temp);
	return temp;
}
//std::string HtmlConverter::HtmlGenerator::Specialcases(FileSystem::File f,std::vector<Type_Info*> ti)
//{
//	std::string temp,fstr;
//	int lineno=0;
//	f.open(FileSystem::File::in, FileSystem::File::text);
//	while (f.isGood()) {
//		temp = f.getLine();
//		
//		++lineno;
//		for (auto t : ti) {
//			std::string tname = Utilities::split(t->type_name,'_').back();
//			if ((t->startline_ == lineno || t->startline_ == lineno+1)&& temp.find(tname) != std::string::npos )
//			{
//				size_t pos1 = temp.find('{');
//				size_t pos2 = temp.find(';');
//				bool s(pos2 == std::string::npos);
//				if (t->startline_ == lineno)
//				{
//					std::string rep = "<div class= \"" + t->type_ + "_div\">{";
//					temp.replace(pos1, 1, rep);
//				}
//				else if (t->startline_ == lineno+1) {
//					std::string rep = "<div class= \"" + t->type_ + "_div\">";
//					temp.append(rep);
//				}
//			}
//			if (lineno == t->endline_)
//				EndingDiv(temp,lineno,t);
//		}
//		temp = comment(temp);
//		fstr.append(temp+"\n");
//	}
//	f.close();
//	return fstr;
//}
std::string HtmlConverter::HtmlGenerator::depend_add(std::string filename)
{
	std::string temp = "<p>Dependencies:</p>";
	for (auto dep : dep_->getdependencies(Utilities::SplitFilename(filename))) {
			std::string d = Utilities::SplitFilename(dep);
			if (dep_->haskey(dep))
				temp += "<a href = \"" + d + ".html\">" + d + "</a>\n";
			else
				temp += d + "\n";
	}
	return temp;
}
std::string HtmlConverter::HtmlGenerator::comment(std::string &temp){
	int len = temp.size();
	if (len == 1 || len == 0)
		return temp;
	if (temp.find('/')!=temp.npos) {
		if (temp[temp.find('/')+1] == '/')
		{
			temp.replace(temp.find("//"),1,"<div class=\"SLC_Div\">/");
			temp.append("</div>");
		}
		if (temp[temp.find('/')+1] == '*') {
			temp.replace(temp.find("/*"), 1, "<div class=\"SLC_Div\">/");
		}
	}
	if (temp.find("*/") != temp.npos) {
			temp.replace(temp.find_last_of("/"),1,"</div>");
	}
	return temp;
}
std::string HtmlGenerator::tegset(std::string temp) {
	
		while (temp.find("<") != temp.npos) {
			temp = temp.replace(temp.find("<"), 1, "&lt;");
		}
		while (temp.find(">") != temp.npos) {
			temp = temp.replace(temp.find(">"), 1, "&gt;");
		}
	return temp;
}

void HtmlConverter::HtmlGenerator::setspecial(bool v)
{
	special_ = v;
}

bool HtmlConverter::HtmlGenerator::getspecial()
{
	return special_;
}

