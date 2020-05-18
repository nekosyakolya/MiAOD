

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>



#include <locale>
#include <algorithm>
#include <cctype>

#include <codecvt>
#include "Bohr.h"
#include "Text.h"




/*bool is_string_in_bohr(const std::wstring& s) {
	int num = 0;
	for (int i = 0; i < s.length(); i++) {
		//char ch = s[i] - 'a';
		if (bohr[num].nextItems.find(s[i]) == bohr[num].nextItems.end()) {
			return false;
		}
		num = bohr[num].nextItems.find(s[i])->second;
	}
	return true;
}
*/

void check(int v, int i, std::wofstream &output, CBohr &bohr, const CText &text) {
	for (int u = v; u != 0; u = bohr.GetGoodSuffLink(u)) {
		if (bohr.IsPattern(u))
		{

			std::pair<int, int> res = text.GetPosition(i - bohr.GetPatternLength(u) + 1);
			output << L"Line: " << res.second << ", position " << res.first << ": " << bohr.GetPattern(u) << std::endl;
		}
	}
}



void find_all_pos(const CText &text, CBohr &bohr) {
	const std::locale utf8_locale = std::locale(std::locale(), new std::codecvt_utf8<wchar_t>());
	std::wofstream output("out.txt");
	output.imbue(utf8_locale);

	int u = 0;
	std::wstring s = text.GetValue();
	for (int i = 0; i < s.length(); i++) {
		u = bohr.GetAutoMove(u, (s[i]));
		check(u, i + 1, output, bohr, text);
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
	find_all_pos(text, bohr);
}
