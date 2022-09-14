#ifndef G_STRING_UTIL_H
#define G_STRING_UTIL_H

#include <string>
#include <list>

namespace GApi::Util {

  class StringParser {

    public:
	StringParser();
	StringParser(std::string stringToParse, std::string strToken);
	~StringParser() {}

	void Parse(std::string stringToParse, std::string strToken);
	const std::string getToken() const;
	const unsigned int getSize() const;
	const bool isFirst() const;
	const bool isLast() const;
	const bool getNext();
	const bool getBack();
	const bool getFirst();
	const bool getLast();
	const bool operator++(int);
	const bool operator--(int);

    protected:
	std::string m_OriginalString;
	std::list<std::string> m_TokenList;
	std::list<std::string>::iterator m_TokenListItr;
	std::string m_CurrentToken;

    private:
	void Init();
  };


  inline std::string& ltrim(std::string& s, const char* t = " \t\n\r\f\v")
  {
    s.erase(0, s.find_first_not_of(t));
    return s;
  }
}


#endif //G_STRING_UTIL_H
