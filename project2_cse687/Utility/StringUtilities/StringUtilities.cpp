///////////////////////////////////////////////////////////////////////
// StringUtilities.cpp - small, generally useful, helper classes     //
// ver 1.0                                                           //
// Language:    C++, Visual Studio 2017                              //
// Application: Most Projects, CSE687 - Object Oriented Design       //
// Author:      Jim Fawcett, Syracuse University, CST 4-187          //
//              jfawcett@twcny.rr.com                                //
///////////////////////////////////////////////////////////////////////

#include <cctype>
#include <iostream>
#include <iomanip>
#include <locale>
#include <clocale>
#include "StringUtilities.h"
#include "../CodeUtilities/CodeUtilities.h"
using namespace Utilities;
/*
*  Note:
*  The std::string src argument must be pass by value so that we can pass
*  std::ostringstream.out() to the first argument and std::ostringstream out
*  to the last argument, e.g., the same std::ostringstream object for both
*  arguments.  Otherwise we attempt to insert out's string into itself.
*/
void StringHelper::Title(std::string src, std::ostream& out)
{
	out << "\n  " << src;
	out << "\n " << std::string(src.size() + 2, '=');
}

void StringHelper::Title(std::string src, std::ostringstream& out)
{
	out.str("");
	out << "\n  " << src;
	out << "\n " << std::string(src.size() + 2, '=');
}

void StringHelper::title(std::string src, std::ostream& out)
{
	out << "\n  " << src;
	out << "\n " << std::string(src.size() + 2, '-');
}

void StringHelper::title(std::string src, std::ostringstream& out)
{
	out.str("");
	out << "\n  " << src;
	out << "\n " << std::string(src.size() + 2, '-');
}

void StringHelper::sTitle(std::string src, size_t offset, size_t width, std::ostream& out, char underline)
{
	if (width < src.size())
		width = src.size();
	size_t lwidth = (width - src.size()) / 2;
	out << "\n  " << std::setw(offset) << "" << std::setw(lwidth) << " " << src;
	out << "\n " << std::setw(offset) << "" << std::string(width + 2, underline);
}

void StringHelper::sTitle(std::string src, size_t offset, size_t width, std::ostringstream& out, char underline)
{
	out.str("");
	if (width < src.size())
		width = src.size();
	size_t lwidth = (width - src.size()) / 2;
	out << "\n  " << std::setw(offset) << "" << std::setw(lwidth) << " " << src;
	out << "\n " << std::setw(offset) << "" << std::string(width + 2, underline);
}

std::vector<std::string> StringHelper::split(const std::string& src)
{
	std::vector<std::string> accum;
	std::string temp;
	std::locale loc;
	size_t index = 0;
	do
	{
		while ((isspace(src[index], loc) || src[index] == ',') && src[index] != '\n')
		{
			++index;
			if (temp.size() > 0)
			{
				accum.push_back(temp);
				temp.clear();
			}
		}
		if (src[index] != '\0')
			temp += src[index];
	} while (index++ < src.size());
	if (temp.size() > 0)
		accum.push_back(temp);
	return accum;
}



#ifdef TEST_STRINGUTILITY

using namespace Utilities;

int main()
{
  Title("Testing Utilities Package");
  putline();

  title("test split(std::string, ',')");

  std::string test = "a, \n, bc, de, efg, i, j k lm nopq rst";
  std::cout << "\n  test string = " << test;

  std::vector<std::string> result = split(test);
  showSplits(result);

  title("test split(std::string, ' ')");

  std::cout << "\n  test string = " << test;

  result = split(test, ' ');
  showSplits(result);

  putline(2);
  return 0;
}
#endif
