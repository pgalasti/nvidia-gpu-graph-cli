#include "GraphOutputCli.h"

#include <iostream>
#include <sstream>

#include <string.h>

#include "FontColorCli.h"

using namespace GraphCli;

static unsigned short DEFAULT_MAX_WIDTH = 40;

void OutputCli::OutputProgress(const char* pszGraphName, const unsigned short utilization) const {

  const unsigned short maxWidth = DEFAULT_MAX_WIDTH;
  std::cout << GraphCli::Font::ColorOutput(GraphCli::Font::Color::White);
  const unsigned short maxBoxLength = maxWidth+2;
  std::cout << std::string(maxBoxLength, '*') << std::endl;
  std::cout << "* ";
  std::cout << GraphCli::Font::ColorOutput(GraphCli::Font::Color::Cyan);
  std::cout << pszGraphName; 
  std::cout << std::string(maxWidth - strlen(pszGraphName) -2, ' ');
  std::cout << GraphCli::Font::ColorOutput(GraphCli::Font::Color::White);
  std::cout << " *" << std::endl;
  std::cout << std::string(maxBoxLength, '*') << std::endl;

  std::stringstream ss;  
  ss << GraphCli::Font::ColorOutput(GraphCli::Font::Color::Yellow);
  const float progress = utilization*.01;
  for(int j = 0; j < 3; ++j) {
    ss << "[";
    const unsigned short position = maxWidth * progress;
    for(int i = 0; i < maxWidth; ++i) {
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

  std::cout << GraphCli::Font::ColorOutput(GraphCli::Font::Color::White);
}

void OutputCli::OutputHeader(const Metrics& metrics) const {
  std::cout << GraphCli::Font::ColorOutput(GraphCli::Font::Color::Bold);
  std::cout << "************************" << std::endl;
  std::cout << "* GPU Utilization: " << metrics.gpuUtilization << "%" << std::endl;
  std::cout << "* Full Memory: " << metrics.totalMemory << "MiBs" << std::endl;
  std::cout << "* Free Memory: " << metrics.freeMemory << "MiBs" << std::endl;
  std::cout << "* Used Memory: " << metrics.usedMemory << "MiBs" << std::endl;
  std::cout << "************************" << std::endl;
  std::cout << GraphCli::Font::ColorOutput(GraphCli::Font::Color::Default);
  std::cout << std::endl;
}
