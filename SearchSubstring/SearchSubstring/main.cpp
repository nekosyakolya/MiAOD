#include "Bohr.h"
#include "Text.h"

void Check(int v, int i, std::wofstream &output, CBohr &bohr, const CText &text) {
	for (int u = v; u != 0; u = bohr.GetGoodSuffLink(u)) {
		if (bohr.IsPattern(u))
		{
			std::pair<int, int> position = text.GetPosition(i - bohr.GetPatternLength(u) + 1);
			output << L"Line: " << position.second << ", position " << position.first << ": " << bohr.GetPattern(u) << std::endl;
		}
	}
}

void FindAllPositions(const CText &text, CBohr &bohr) {
	const std::locale utf8_locale = std::locale(std::locale(), new std::codecvt_utf8<wchar_t>());
	std::wofstream output("out.txt");
	output.imbue(utf8_locale);

	int u = 0;
	std::wstring s = text.GetValue();
	for (int i = 0; i < s.length(); i++) {
		u = bohr.GetAutoMove(u, (s[i]));
		Check(u, i + 1, output, bohr, text);
	}
}

int main()
{
	CBohr bohr;

	std::wifstream inputData("input.txt");

	std::wstring strCount;
	std::getline(inputData, strCount);
	int count = std::stoi(strCount);

	for (int i = 0; i != count; i++)
	{
		std::wstring pattern;
		std::getline(inputData, pattern);
		bohr.Add(pattern);
	}

	CText text("test.txt");
	FindAllPositions(text, bohr);
}
