/////////////////////////////////////////////////////////////////////
// htmlgenerator.cpp - Holds function for header file,			   //	 
//					   also have a test suite.					   //
// ver 1.1                                                         //
// RAJAT Vyas, CSE687 - Object Oriented Design, Spring 2019        //
/////////////////////////////////////////////////////////////////////
#include <iostream>
#include "htmlgenerator.h"
#include"../Utility/StringUtilities/StringUtilities.h"
#include"../InfoExtractor/InfoExtractor.h"
#include"../Utility/CodeUtilities/CodeUtilities.h"
using namespace HtmlConverter;
#ifdef TEST_CONVERTER
int main()
{
	HtmlConverter::HtmlGenerator ge("../Convertedpages");
    std::cout << "Hello World!\n"; 
	InfoExtractor::FileTypeInfo fti(std::vector<std::string>{ FileSystem::Path::getFullFileSpec("../Parser/Parser/Parser.h") });
	fti.parse();
	HtmlConverter::HtmlGenerator ge2("../Convertedpages", fti.getinfo(), fti.getDepend());
	ge.convert(std::vector<std::string>{ FileSystem::Path::getFullFileSpec("../Parser/Parser/Parser.h") });
	ge2.convert(fti.filelist());
}
#endif // TEST_CONVERTER
HtmlConverter::HtmlGenerator::HtmlGenerator(const std::string& path, TypeInfo * const ti, Dependencies * const dp)
{
	std::string pth_ = FileSystem::Path::getFullFileSpec(path);
	if (!FileSystem::Directory::exists(pth_)) {
		FileSystem::Directory::create(pth_);
	}
	path_ = pth_;
	Info_ = ti;
	dep_ = dp;
	special_ = true;
}
//-----------------<Constructer sets the converter to an folder>----------------------------------
HtmlGenerator::HtmlGenerator(const std::string& path)
{
	std::string pth_ = FileSystem::Path::getFullFileSpec(path);
	if (!FileSystem::Directory::exists(pth_)) {
		FileSystem::Directory::create(pth_);
	}
	
	path_ = pth_;
	Info_ = nullptr;
	dep_ = nullptr;
	special_ = false;
}
std::string HtmlGenerator::f_path() {
	return path_;
}
HtmlGenerator::~HtmlGenerator()
{

}
//---------------------<takes a file and save its html file to the path>---------------------------
bool HtmlGenerator::convert(const std::string& file)
{
	std::string filename = Utilities::SplitFilename(file);
	std::string path = path_+"\\"+filename+".html";
	std::string temp,header;
	if (FileSystem::Directory::exists(path)) {
		FileSystem::Directory::remove(path);
	}
	FileSystem::File fwrite(path);
	FileSystem::File fread(file);
	FileSystem::File fhead(FileSystem::Path::getFullFileSpec("../../../Header/header.html"));
	fhead.open(FileSystem::File::in, FileSystem::File::text);
	if (fhead.isGood()){
		header = fhead.readAll(true);
	}
	else
		header = "Error in header read file..!!";
	fhead.close();
	fread.open(FileSystem::File::in, FileSystem::File::text);
	int linecount = 0;
	std::string tem;
	std::vector<Typedata*> ti;
	if(special_)
		ti = Info_->GetInfo(filename);
	while (fread.isGood()) {
		temp = fread.getLine();
		linecount++;
		temp = tegset(temp);
		if (special_ == true) {
			temp = Specialcases(temp, ti, linecount);
		}
		tem.append(temp).append("\n");
	}
	header.replace(header.find("PageHeader"),10,filename);
	fwrite.open(FileSystem::File::out, FileSystem::File::text);
	if (fwrite.isGood() && !header.empty()) {
		fwrite.putLine(header);
		if(special_==true)
			fwrite.putLine(depend_add(filename));
		fwrite.putLine(tem);
		fwrite.putLine("</pre>\n</body>\n</html>");
	}
	else {
		std::cout << "Error in writing file..!!"<<std::endl;
		return false;
	}
	fwrite.close();
	writejs();
	writecss();
	convertedfiles_.push_back(path);
	return true;
}
bool  HtmlGenerator::convert(std::vector<std::string> filelist)
{
	bool result = true;
	for (auto file : filelist) {
		result = convert(file);
			if(!result)
				break;
	}
	return result;
}
std::string HtmlConverter::HtmlGenerator::Specialcases(std::string temp,std::vector<Typedata*>ti, int linecount)
{
	for (auto t : ti) {
		if (temp.find(Utilities::split(t->type_name, '_').back()) != std::string::npos) {
			if (t->startline_ == linecount) {
				if (temp.find('{') != temp.npos) {
					std::string rep = "<span class= \"" + t->type_ + "_div\">{";
					temp.replace(temp.find('{'), 1, rep);
				}
			}
			if (t->startline_ == linecount + 1)
			{
				std::string rep = "<span class= \"" + t->type_ + "_div\">";
				temp.append(rep);
			}
		}
		if (t->endline_ == linecount || t->endline_ == linecount + 1 && t->type_ != "namespace")
		{
			if(temp.find("}")!= temp.npos)
				temp.replace(temp.find("}"),1,"}</span>");
				//temp.replace(temp.find("}"),1,"}</span>");
		}
	}
	temp = comment(temp);
	return temp;
}

std::string HtmlConverter::HtmlGenerator::depend_add(std::string& filename)
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
			temp.replace(temp.find("//"),1,"<span class=\"SLC_Div\">/");
			temp.append("</span>");
		}
		if (temp[temp.find('/')+1] == '*') {
			temp.replace(temp.find("/*"), 1, "<span class=\"SLC_Div\">/");
		}
	}
	if (temp.find("*/") != temp.npos) {
			temp.replace(temp.find_last_of("/"),1,"/</span>");
	}
	return temp;
}
bool HtmlConverter::HtmlGenerator::writejs()
{
	FileSystem::File fhead(FileSystem::Path::getFullFileSpec("../../../Header/script.js"));
	fhead.open(FileSystem::File::in, FileSystem::File::text);
	std::string filecontent;
	if (fhead.isGood()) {
		filecontent = fhead.readAll(true);
	}
	else
		filecontent = "Error in header read file..!!";
	fhead.close();
	std::string path = path_ + "\\script.js";
	FileSystem::File fwrite(FileSystem::Path::getFullFileSpec(path));
	fwrite.open(FileSystem::File::out,FileSystem::File::text);
	if (fwrite.isGood()) {
		fwrite.putLine(filecontent);
	}
	fwrite.close();
	return true;
}
bool HtmlConverter::HtmlGenerator::writecss()
{
	FileSystem::File fhead(FileSystem::Path::getFullFileSpec("../../../Header/style.css"));
	fhead.open(FileSystem::File::in, FileSystem::File::text);
	std::string filecontent;
	if (fhead.isGood()) {
		filecontent = fhead.readAll(true);
	}
	else
		filecontent = "Error in header read file..!!";
	fhead.close();
	std::string path = path_ + "\\style.css";
	FileSystem::File fwrite(FileSystem::Path::getFullFileSpec(path));
	fwrite.open(FileSystem::File::out, FileSystem::File::text);
	if (fwrite.isGood()) {
		fwrite.putLine(filecontent);
	}
	fwrite.close();
	return true;
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
std::vector<std::string> HtmlConverter::HtmlGenerator::getconvertedfiles() {
	return convertedfiles_;
}

