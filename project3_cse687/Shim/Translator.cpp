// Hold the Translator Class which talks with Publisher 
// needed files are Executive.h and Itranslator.h
// Implements Interface Itranslator for c# client to use

#include"../Executive/Executive.h"
#include "ITranslator.h"
using namespace System;
using namespace System::Text;
using namespace System::IO;
using namespace HtmlConverter;
public ref class Translator:ITranslator
{
public:
	Translator();
	~Translator();
	bool execute() override;									// Executes Publisher
	List<String^>^ getfiles() override;							// Gets converted files
	void setdirpath(String^) override;							// Sets Publisher's working directory  
	void setregex(String^) override;							// Sets Regex for Loader to filter files
	bool chrome(String^) override;								// Opens a file using Display Module
private:
	IPublisher* ipub_ = nullptr;
	String^ Dir_path_;
	String^ regex_;
	List<String^>^ files_;
	List<String^>^ convertNtoM(const std::vector<std::string> &);		// Converts a Native list to Managed
	std::vector<std::string> convertMtoN(List<String^>^);				// Converts a Managed list to Native
	std::string convertMtoN(String^ );									// Converts a Managed string to Native
	String^ convertNtoM(std::string);									// Converts a native string to Managed
};
Translator::Translator()
{
	ipub_ = PublishFactory::create();									// constructor
}



Translator::~Translator()
{
}
bool Translator::execute()
{
	bool result = false;
	std::cout << "Executing...";
	result = ipub_->execute();
	std::cout << "Executed";
	files_ = convertNtoM(ipub_->convertedfiles());
	return result;
}
List<String^>^ Translator::getfiles()
{
	return files_;
}
void Translator::setdirpath(String ^ dirpath)
{
	Dir_path_ = dirpath;
	ipub_->setdir(convertMtoN(Dir_path_));
}
void Translator::setregex(String ^ rex)
{
	regex_ = rex;
	ipub_->setregex(convertMtoN(regex_));
}
bool Translator::chrome(String ^ file)
{
	ipub_->openbrowser(convertMtoN(file));
	return false;
}
List<String^>^ Translator::convertNtoM(const std::vector<std::string> & files)
{
	List<String^>^ temp = gcnew List<String^>();
	for (size_t i = 0; i < files.size(); ++i) {
		String^ str = convertNtoM(files[i]);
		temp->Add(str);
	}
	return temp;
}

std::vector<std::string> Translator::convertMtoN(List<String^>^ flst)
{
	std::vector<std::string> filelist;
	for (size_t i = 0; i < flst->Count; ++i) {
		std::string temp = convertMtoN(flst[i]);
		filelist.push_back(temp);
	}
	return filelist;
}

std::string Translator::convertMtoN(String ^ Dir_path)
{
	std::string dirpath = "";
	for (int i = 0; i < Dir_path->Length; ++i) {
		dirpath += Dir_path[i];
	}
	return dirpath;
}

String ^ Translator::convertNtoM(std::string str)
{
	StringBuilder^ temp = gcnew StringBuilder();
	for (size_t i = 0; i < str.size(); ++i) {
		temp->Append((wchar_t)str[i]);
	}
	return temp->ToString();
}
ITranslator^ TranslatorFactory::CreateFactory()
{
	return gcnew Translator();
}
#include <iostream>
#ifdef TEST_SHIM


int main() {
	String^ str = "D:\\Projects\\Cse_687\\project3_cse687";
	String^ pattern = "[a - fA - F](.*)";
	List<String^>^ pattr = gcnew List<String^>();	
	ITranslator^ t= gcnew Translator();
	t->setdirpath(str);
	t->setregex(pattern);
	t->execute();
	t->getfiles();
}
#endif // TEST_SHIM
