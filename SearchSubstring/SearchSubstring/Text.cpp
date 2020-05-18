#include "Text.h"

CText::CText(const std::wstring& fileName)
{
	std::wifstream input(fileName);
	input.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));
	std::wstring line;
	int pos = 1;

	while (std::getline(input, line))
	{
		if (!m_value.empty())
		{
			m_value += ' ';
		}

		m_value += line;

		int secondPos = pos + line.length();
		m_positionTable.push_back(std::make_pair(pos, secondPos));
		pos = secondPos + 1;
	}
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

const std::wstring& CText::GetValue() const
{
	return m_value;
}
