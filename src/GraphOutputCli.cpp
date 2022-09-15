#include "GraphOutputCli.h"

#include <iostream>
#include <sstream>
#include <algorithm>
#include <iomanip>

#include <string.h>

#include "FontColorCli.h"

using namespace GraphCli;

static unsigned short DEFAULT_MAX_WIDTH = 45;
static unsigned short DEFAULT_MAX_GRAPH_SIZE = 60;

OutputCli::OutputCli() : gpuUtilizationStates(DEFAULT_MAX_GRAPH_SIZE, 0) {
}

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
  std::cout << "* Temperature: ";
    if(metrics.temperature < 50) {
      std::cout << GraphCli::Font::ColorOutput(GraphCli::Font::Color::Green);
    } else if(metrics.temperature > 50 && metrics.temperature < 70) {
      std::cout << GraphCli::Font::ColorOutput(GraphCli::Font::Color::Yellow);
    } else if(metrics.temperature > 70) {
      std::cout << GraphCli::Font::ColorOutput(GraphCli::Font::Color::Red);
    }
    std::cout << metrics.temperature << " C" << std::endl;
    std::cout << GraphCli::Font::ColorOutput(GraphCli::Font::Color::Default);
  std::cout << "************************" << std::endl;
  std::cout << GraphCli::Font::ColorOutput(GraphCli::Font::Color::Default);
}

void OutputCli::RecordInterval(const Metrics& metrics) {
  if(this->gpuUtilizationStates.size() > DEFAULT_MAX_GRAPH_SIZE) {
    this->gpuUtilizationStates.erase(this->gpuUtilizationStates.begin());
  }
  this->gpuUtilizationStates.push_back(metrics.gpuUtilization);
}

void OutputCli::OutputGraphCurrentState() const {
  std::stringstream ss;

  const char pszGraphName[] = "GPU Utilization";
  const unsigned short maxWidth = DEFAULT_MAX_GRAPH_SIZE+6;
  ss << GraphCli::Font::ColorOutput(GraphCli::Font::Color::White);
  const unsigned short maxBoxLength = maxWidth+2;
  ss << std::string(maxBoxLength, '*') << std::endl;
  ss << "* ";
  ss << GraphCli::Font::ColorOutput(GraphCli::Font::Color::Cyan);
  ss << pszGraphName;
  ss << std::string(maxWidth - strlen(pszGraphName) -2, ' ');
  ss << GraphCli::Font::ColorOutput(GraphCli::Font::Color::White);
  ss << " *" << std::endl;
  ss << std::string(maxBoxLength, '*') << std::endl;


  for(unsigned short level = 10; level > 0; --level) {
    std::string levelPct = std::to_string(level*10);
    ss << levelPct << "%" << std::setw(6-levelPct.length()) << "|";
    ss << RenderGraphLevel(level);
    ss << std::endl;
  } 
  ss << "       -------------------------------------------------------------" << std::endl;

  ss << std::endl;
  std::cout << ss.str();
}

const std::string OutputCli::RenderGraphLevel(const unsigned short level) const {

  const size_t stateSize = this->gpuUtilizationStates.size();
  const unsigned short checkValue = level*10; // Can make this user configurable later.
  std::stringstream levelLineSS;
  
  GraphCli::Font::Color colorToUse = GraphCli::Font::Color::BackgroundGre;
  if(level > 4 && level < 8) {
    colorToUse = GraphCli::Font::Color::BackgroundYel;
  } else if(level > 7) {
    colorToUse = GraphCli::Font::Color:: BackgroundRed;
  }

  for(unsigned short i = 0; i < stateSize; ++i) {
    if(this->gpuUtilizationStates[i] >= checkValue) {
      levelLineSS << GraphCli::Font::ColorOutput(colorToUse);
    }
    levelLineSS << " " << GraphCli::Font::ColorOutput(GraphCli::Font::Color::BackgroundDft);
  }
  return levelLineSS.str();
}
