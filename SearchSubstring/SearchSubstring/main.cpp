#include "Bohr.h"
#include "Text.h"
#include <iostream>

void Check(int v, int i, std::wofstream &output, CBohr &bohr, const CText &text)
{
	for (int u = v; u != 0; u = bohr.GetGoodSuffLink(u))
	{
		if (bohr.IsPattern(u))
		{
			std::pair<int, int> position = text.GetPosition(i - bohr.GetPatternLength(u) + 1);
			output << L"Line: " << position.second << ", position " << position.first << ": " << bohr.GetPattern(u) << std::endl;
		}
	}
}

void FindAllPositions(const CText &text, CBohr &bohr)
{
	std::wofstream output("OUTPUT.TXT");
	output.imbue(std::locale(std::locale(), new std::codecvt_utf8<wchar_t>()));

	const std::wstring& str = text.GetValue();
	int u = 0;

	for (int i = 0; i < str.length(); i++)
	{
		wchar_t ch = std::tolower(str[i], std::locale::empty());
		u = bohr.GetAutoMove(u, ch);
		Check(u, i + 1, output, bohr, text);
	}
}

void runApp()
{
	CBohr bohr;
	std::wifstream input("INPUT.TXT");
	input.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));

	std::wstring line;
	std::getline(input, line);
	unsigned count = std::stoi(line);

	for (unsigned i = 0; i != count; ++i)
	{
		getline(input, line);
		bohr.Add(line);
	}

	std::wstring fileName;
	std::getline(input, fileName);

	CText text(fileName);
	FindAllPositions(text, bohr);
}

int main()
{
	try
	{
		runApp();
		std::cout << ":)" << std::endl;
	}
	catch (...)
	{
		std::cerr << ":(" << std::endl;
		return 1;
	}
}
