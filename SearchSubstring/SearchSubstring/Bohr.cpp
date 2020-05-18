#include "Bohr.h"

CBohr::CBohr()
{
	m_bohr.push_back(MakeBohrItem(0, '$'));
}

void CBohr::Add(const std::wstring & s)
{
	int num = 0;
	for (int i = 0; i < s.length(); i++) {


		if (m_bohr[num].nextItems.find(s[i]) == m_bohr[num].nextItems.end()) {
			m_bohr.push_back(MakeBohrItem(num, s[i]));

			m_bohr[num].nextItems.emplace(s[i], m_bohr.size() - 1);
		}
		num = m_bohr[num].nextItems.find(s[i])->second;
	}
	m_bohr[num].isPattern = true;
	m_patterns.push_back(s);
	m_bohr[num].patternNumber = m_patterns.size() - 1;
}

int CBohr::GetAutoMove(int v, wchar_t ch)
{
	
		if (m_bohr[v].autoMove.find(ch) == m_bohr[v].autoMove.end())
			if (m_bohr[v].nextItems.find(ch) != m_bohr[v].nextItems.end())
				m_bohr[v].autoMove.emplace(ch, m_bohr[v].nextItems.find(ch)->second);
			else
				if (v == 0)
					m_bohr[v].autoMove.emplace(ch, 0);
				else
					m_bohr[v].autoMove.emplace(ch, GetAutoMove(GetSuffLink(v), ch));

		return m_bohr[v].autoMove.find(ch)->second;
}

int CBohr::GetSuffLink(int v)
{
	if (m_bohr[v].suffLink == -1)
		if (v == 0 || m_bohr[v].parent == 0)
			m_bohr[v].suffLink = 0;
		else
			m_bohr[v].suffLink =
			GetAutoMove(GetSuffLink(m_bohr[v].parent), m_bohr[v].symb);

	return m_bohr[v].suffLink;
}

int CBohr::GetGoodSuffLink(int v)
{
	if (m_bohr[v].goodSuffLink == -1) {
		int u = GetSuffLink(v);
		if (u == 0)
			m_bohr[v].goodSuffLink = 0;
		else
			m_bohr[v].goodSuffLink = (m_bohr[u].isPattern) ? u : GetGoodSuffLink(u);
	}

	return m_bohr[v].goodSuffLink;
}

int CBohr::GetPatternLength(int u) const
{
	return m_patterns[m_bohr[u].patternNumber].length();
}

std::wstring CBohr::GetPattern(int u) const
{
	return m_patterns[m_bohr[u].patternNumber];
}

bool CBohr::IsPattern(int u) const
{
	return m_bohr[u].isPattern;
}
