#include "StringUtils.h"

using namespace GApi::Util;

StringParser::StringParser()
{
	Init();
}

StringParser::StringParser(std::string stringToParse, std::string strToken)
{
	Init();
	Parse(stringToParse, strToken);
}

void StringParser::Init()
{
	m_OriginalString.clear();
	m_CurrentToken.clear();
	m_TokenList.clear();
	m_TokenListItr = m_TokenList.begin();
}

void StringParser::Parse(std::string stringToParse, std::string strToken)
{
	Init();
	if (stringToParse.empty())
		return;

	size_t startPosition = 0, currentPosition = 0;

	while ((currentPosition = stringToParse.find_first_of(strToken, currentPosition)) != std::string::npos)
	{
		m_CurrentToken = stringToParse.substr(startPosition, currentPosition - startPosition);
		m_TokenList.push_back(m_CurrentToken);
		startPosition = ++currentPosition;
	}

	m_CurrentToken = stringToParse.substr(startPosition, currentPosition - startPosition);
	m_TokenList.push_back(m_CurrentToken);
}

const std::string StringParser::getToken() const
{
	return m_CurrentToken;
}

const unsigned int StringParser::getSize() const
{
	return (unsigned int)m_TokenList.size();
}

const bool StringParser::isFirst() const
{
	return m_TokenListItr == m_TokenList.begin();
}

const bool StringParser::isLast() const
{
	auto endIter = m_TokenList.end();
	return m_TokenListItr == --endIter;
}

const bool StringParser::getNext()
{
	if (++m_TokenListItr == m_TokenList.end())
	{
		m_CurrentToken.clear();
		return false;
	}

	m_CurrentToken = *m_TokenListItr;
	return true;
}

const bool StringParser::getBack()
{
	if (this->isFirst())
	{
		m_CurrentToken.clear();
		return false;
	}

	--m_TokenListItr;
	m_CurrentToken = *m_TokenListItr;
	return true;
}

const bool StringParser::getFirst()
{
	if (m_TokenList.empty())
	{
		m_CurrentToken.clear();
		return false;
	}

	m_TokenListItr = m_TokenList.begin();
	m_CurrentToken = *m_TokenListItr;
	return true;
}

const bool StringParser::getLast()
{
	if (m_TokenList.empty())
	{
		m_CurrentToken.clear();
		return false;
	}

	m_TokenListItr = m_TokenList.end();
	--m_TokenListItr;
	m_CurrentToken = *m_TokenListItr;
	return true;
}

const bool StringParser::operator++(int)
{
	return getNext();
}

const bool StringParser::operator--(int)
{
	return getBack();
}
