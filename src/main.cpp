#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>

#include "StringUtils.h"
#include "ProcUtils.h"
#include "NvidiaSmiParser.h"
#include "Metrics.h"
#include "GraphOutputCli.h"
#include "FontColorCli.h"


const char CLEAR_SCREEN[] = "\033[2J\033[H";

void displayMetrics();

std::atomic_bool stopThread = false;

int main(int argc, char** argv) {

  std::thread displayThread(displayMetrics);
  
  std::getchar();

  stopThread = true;
  displayThread.join();
  return 0;
}

void displayMetrics() {
  
  GraphCli::NvidiaSmiParser parser;
  GraphCli::Metrics metrics;
  GraphCli::GraphOutputCli output;  
  
  for(;;) {
    
    if(stopThread)
      return;

    std::cout << CLEAR_SCREEN;

    metrics = parser.Parse();
    
    std::cout << GraphCli::Font::ColorOutput(GraphCli::Font::Color::Bold);
    std::cout << "************************" << std::endl;
    std::cout << "* GPU Utilization: " << metrics.gpuUtilization << "%" << std::endl;
    std::cout << "* Full Memory: " << metrics.totalMemory << "MiBs" << std::endl;
    std::cout << "* Free Memory: " << metrics.freeMemory << "MiBs" << std::endl;
    std::cout << "* Used Memory: " << metrics.usedMemory << "MiBs" << std::endl;
    std::cout << "************************" << std::endl;
    std::cout << GraphCli::Font::ColorOutput(GraphCli::Font::Color::Default);
    std::cout << std::endl;

    std::cout << metrics.szProductName << std::endl;
    std::cout << "Temperature: ";
    if(metrics.temperature < 50) {
      std::cout << GraphCli::Font::ColorOutput(GraphCli::Font::Color::Green);
    } else if(metrics.temperature > 50 && metrics.temperature < 70) {
      std::cout << GraphCli::Font::ColorOutput(GraphCli::Font::Color::Yellow);
    } else if(metrics.temperature > 70) {
      std::cout << GraphCli::Font::ColorOutput(GraphCli::Font::Color::Red);
    }
    std::cout << metrics.temperature << " C" << std::endl;
    std::cout << GraphCli::Font::ColorOutput(GraphCli::Font::Color::Default);

    output.Output("GPU Utilization", metrics.gpuUtilization);
    std::cout << std::endl;
    output.Output("GPU Memory Utilization", metrics.memoryUtilization);

    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
}
