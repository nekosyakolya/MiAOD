#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <codecvt>


class CText
{
public:
	CText(const std::wstring& fileName);
	std::pair<int, int> GetPosition(int pos) const;
	const std::wstring& GetValue() const;

private:
	std::wstring m_value;
	std::vector<std::pair<int, int>> m_positionTable;
};
