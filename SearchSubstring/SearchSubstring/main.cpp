#include "Bohr.h"
#include "Text.h"
#include <iostream>

void Check(int v, int i, std::wofstream &output, CBohr &bohr, const CText &text)
{
	for (int u = v; u != 0; u = bohr.GetGoodSuffLink(u))
	{
		if (bohr.IsPattern(u))
		{
			int patternNumber = bohr.GetPatternNumber(u);

			bohr.SetFoundPattern(patternNumber);

			std::pair<int, int> position = text.GetPosition(i - bohr.GetPatternLength(patternNumber) + 1);
			output << L"Line: " << position.second << ", position " << position.first << ": " << bohr.GetPattern(patternNumber) << std::endl;
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

	for (int i = 0; i < bohr.GetPatternsSize(); ++i)
	{
		if (!bohr.IsFoundPattern(i))
		{
			output << L"No: " << bohr.GetPattern(i) << std::endl;
		}

	}
}

void RunApp()
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
		if (line.empty() || line.length() > 30)
		{
			throw std::invalid_argument("Incorrect input size of line\n");
		}
		bohr.Add(line);
	}

	std::wstring fileName;
	std::getline(input, fileName);

	if (fileName.empty())
	{
		throw std::invalid_argument("Incorrect file name\n");
	}

	CText text(fileName);
	FindAllPositions(text, bohr);
}

int main()
{
	try
	{
		RunApp();
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
	return 0;
}
