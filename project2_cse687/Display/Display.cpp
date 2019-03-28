/////////////////////////////////////////////////////////////////////
// Display.cpp - Display package used for displaying converted page//
// ver 1.0                                                         //
// RAJAT Vyas, CSE687 - Object Oriented Design, Spring 2019        //
/////////////////////////////////////////////////////////////////////



#include "../Process/Process.h"
#include "../FileSystem/FileSystem.h"
#include "Display.h"
using namespace FileSystem;
#ifdef DISPLAY
int main()
{
    std::cout << "Hello World!\n"; 
}
#endif

Display::Show::Show()
{
}

Display::Show::~Show()
{
}

//-------------<accpts application path and list of files to show on the browser>------------------------------------
void Display::Show::Showpages(std::string &application_path, std::vector<std::string> &con_filelist)
{
	Process process;
	process.title("Browser Launcher");
	process.application(application_path);
	std::cout << "\n  Press key to open browser with required converted files to satisfy Requirement...!!";
	char ch;
	std::cin.read(&ch, 1);
	for (auto file : con_filelist) {
		std::cout << "file name: "<<file << std::endl;
		process.commandLine("/A " + file);
		process.create();
		CBP callback = []() { std::cout << "\n  --- child process exited with this message ---\n"; };
		process.setCallBackProcessing(callback);
		process.registerCallback();

		WaitForSingleObject(process.getProcessHandle(), INFINITE);  // wait for created process to terminate
	}
	std::cout << "\n  after OnExit";
	std::cout.flush();
	std::cin.read(&ch, 1);
}
