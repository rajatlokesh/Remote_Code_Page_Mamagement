// Converter.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include "htmlgenerator.h"
#ifdef TEST_CONVERTER


int main()
{
	converter::HtmlGenerator ge("../Convertedpages");
    std::cout << "Hello World!\n"; 
	ge.convert(FileSystem::Path::getFullFileSpec( "../Converter/htmlgenerator.h"));
}

#endif // TEST_CONVERTER



//-----------------<Constructer sets the converter to an folder>----------------------------------
converter::HtmlGenerator::HtmlGenerator(std::string path)
{
	std::string pth_ = FileSystem::Path::getFullFileSpec(path);
	if (!FileSystem::Directory::exists(pth_)) {
		FileSystem::Directory::create(pth_);
	}
	path_ = pth_;
}
std::string converter::HtmlGenerator::f_path() {
	return path_;
}
converter::HtmlGenerator::~HtmlGenerator()
{
}
//---------------------<takes a file and save its html file to the path>---------------------------
bool converter::HtmlGenerator::convert(std::string file)
{
	std::string filename = Utilities::SplitFilename(file);
	std::string path = path_+"\\"+filename+".html";
	std::string temp;
	std::string header;
	std::regex reg("[<]");
	std::regex reg2("[>]");
	if (FileSystem::File::exists(path)) {
		FileSystem::File::remove(path);
	}
	FileSystem::File fwrite(path);
	FileSystem::File fread(file);
	FileSystem::File fhead(FileSystem::Path::getFullFileSpec("../Header/html.txt"));

	fhead.open(FileSystem::File::in, FileSystem::File::text);
	if (fhead.isGood())
	{
		header = fhead.readAll();
	}
	else
	{
		header = "Error in header read file..!!";
	}
	fhead.close();
	fread.open(FileSystem::File::in, FileSystem::File::text);
	if (fread.isGood()) {
		temp = fread.readAll(true);
	}
	else {
		temp = "Error reading file!!";
		std::cout << temp << std::endl;
		return false;
	}
	fread.close();
	temp = std::regex_replace(temp, reg, "&lt");
	temp = std::regex_replace(temp, reg2, "&gt");
	header = std::regex_replace(header,std::regex("PageHeader"),Utilities::SplitFilename(file));
	fwrite.open(FileSystem::File::out, FileSystem::File::text);
	if (fwrite.isGood() && temp != "Error reading file!!" && !header.empty()) {
		fwrite.putLine(header);
		fwrite.putLine(temp);
		fwrite.putLine("</pre></body></html>");
	}
	else {
		std::cout << "Error in writing file..!!"<<std::endl;
		return false;
	}
	fwrite.close();


	return true;
}
