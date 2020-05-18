#pragma once

#include <vector>
#include <map>

class CBohr
{
public:
	CBohr();
	void Add(const std::wstring& s);


	int GetAutoMove(int v, wchar_t ch);
	int GetGoodSuffLink(int v);

	int GetPatternLength(int u) const;
	std::wstring GetPattern(int u) const;

	bool IsPattern(int u) const;

private:

	struct BohrItem {
		std::map<wchar_t, int> nextItems;
		std::map<wchar_t, int> autoMove;
		int suffLink;
		int goodSuffLink;
		int parent;
		bool isPattern;
		int patternNumber;
		wchar_t symb;
	};

	BohrItem MakeBohrItem(int p, wchar_t c) {
		BohrItem item;
		item.isPattern = false;
		item.suffLink = -1;
		item.parent = p;
		item.symb = c;
		item.goodSuffLink = -1;
		return item;
	}

	int GetSuffLink(int v);

	std::vector<BohrItem> m_bohr;
	std::vector<std::wstring> m_patterns;
};

