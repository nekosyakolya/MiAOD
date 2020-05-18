#include "Text.h"

CText::CText(const std::string & fileName)
{
	int pos = 1;
	std::wstring s;
	std::wifstream input(fileName);
	while (std::getline(input, s))
	{
		if (!m_value.empty())
		{
			m_value += ' ';
		}

		m_value += s;

		int secondPos = pos + s.length();
		m_positionTable.push_back(std::make_pair(pos, secondPos));
		pos = secondPos + 1;
	}
}

std::wstring CText::GetValue() const
{
	return m_value;
}

std::pair<int, int> CText::GetPosition(int pos) const
{
	int x;
	int y;
	for (int i = 0; i < m_positionTable.size(); i++)
	{
		if (pos >= m_positionTable[i].first && pos <= m_positionTable[i].second)
		{
			x = pos - m_positionTable[i].first + 1;
			y = i + 1;
			break;
		}
	}

	return std::make_pair(x, y);
}
