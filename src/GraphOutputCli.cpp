#include "GraphOutputCli.h"

#include <iostream>
#include <sstream>

#include "FontColorCli.h"

using namespace GraphCli;

static unsigned short MAX_WIDTH = 70;

void GraphOutputCli::Output(const char* pszGraphName, const unsigned short utilization) const {

  std::cout << GraphCli::Font::ColorOutput(GraphCli::Font::Color::White);

  std::cout << "******************************" << std::endl;
  std::cout << "* ";
  std::cout << GraphCli::Font::ColorOutput(GraphCli::Font::Color::Cyan);
  std::cout << pszGraphName <<std::endl;
  std::cout << GraphCli::Font::ColorOutput(GraphCli::Font::Color::White);
  std::cout << "******************************" << std::endl;

  std::stringstream ss;  
  ss << GraphCli::Font::ColorOutput(GraphCli::Font::Color::Yellow);
  const float progress = utilization*.01;
  for(int j = 0; j < 3; ++j) {
    ss << "[";
    const unsigned short position = MAX_WIDTH * progress;
    for(int i = 0; i < MAX_WIDTH; ++i) {
      if(i < position)
	  ss << "=";
      else if(i == position)
	  ss << "|";
      else
  	  ss << " ";   
    }
    ss << "] ";
    if(j == 1) {
      if(utilization > 30 && utilization <= 75) {
        ss << GraphCli::Font::ColorOutput(GraphCli::Font::Color::Yellow);
      } else if(utilization > 75) {
	ss << GraphCli::Font::ColorOutput(GraphCli::Font::Color::Red);
      } else {
        ss << GraphCli::Font::ColorOutput(GraphCli::Font::Color::Green);
      }

      ss << utilization << " %";
      ss << GraphCli::Font::ColorOutput(GraphCli::Font::Color::Yellow);
    }
    ss << "\n";
  }
  std::cout << ss.str();
//  std::cout.flush();

  std::cout << GraphCli::Font::ColorOutput(GraphCli::Font::Color::White);
}
