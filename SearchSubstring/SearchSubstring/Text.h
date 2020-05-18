#pragma once
#include <string>
#include <vector>
#include <fstream>

class CText
{
public:
		CText(const std::string & fileName);
		std::wstring GetValue() const;
		std::pair<int, int> GetPosition(int pos) const;
private:
	std::wstring m_value;
	std::vector<std::pair<int, int>> m_positionTable;
};
