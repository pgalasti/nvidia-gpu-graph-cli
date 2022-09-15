#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>

#include <unistd.h>
#include <termios.h>

#include "StringUtils.h"
#include "ProcUtils.h"
#include "NvidiaSmiParser.h"
#include "Metrics.h"
#include "GraphOutputCli.h"
#include "FontColorCli.h"

const char CLEAR_SCREEN[] = "\033[2J\033[H";

void displayMetrics();
bool initCheck();
char captureInput();
std::atomic_bool stopThread = false;

int main(int argc, char** argv) {

  if(!initCheck())
    return 1;

  std::thread displayThread(displayMetrics);
  while(captureInput() != 'q');

  stopThread = true;
  displayThread.join();
  return 0;
}

void displayMetrics() {
  
  GraphCli::NvidiaSmiParser parser;
  GraphCli::Metrics metrics;
  GraphCli::OutputCli cliOutput;  
  
  for(;;) {
    
    if(stopThread)
      return;

    metrics = parser.Parse();
  
    std::cout << CLEAR_SCREEN;
 
    std::cout << GraphCli::Font::ColorOutput(GraphCli::Font::Color::Cyan);  
    std::cout << metrics.szProductName << " - ";
    std::cout << GraphCli::Font::ColorOutput(GraphCli::Font::Color::Green);
    std::cout << "Driver " << metrics.szDriver;
    std::cout << GraphCli::Font::ColorOutput(GraphCli::Font::Color::Default);
    cliOutput.OutputHeader(metrics);

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

    cliOutput.OutputProgress("GPU Utilization", metrics.gpuUtilization);
//    std::cout << std::endl;
    cliOutput.OutputProgress("GPU Memory Utilization", metrics.memoryUtilization);

    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
}

bool initCheck() {
  std::string execOutput = GApi::Util::GetExecOutput("which nvidia-smi");
  const std::string formattedOutput = GApi::Util::ltrim(execOutput);
  if(formattedOutput.empty()) {
    std::cerr << "Unable to find 'nvidia-smi' tool. Is it in your path or are your nvidia drivers missing?" << std::endl;
    return false;
  }

  return true;
}

char captureInput() {

  char buf = 0;
  struct termios old = {0};
  fflush(stdout);
  if(tcgetattr(0, &old) < 0)
    perror("tcsetattr()");
  old.c_lflag &= ~ICANON;
  old.c_lflag &= ~ECHO;
  old.c_cc[VMIN] = 1;
  old.c_cc[VTIME] = 0;
  if(tcsetattr(0, TCSANOW, &old) < 0)
    perror("tcsetattr ICANON");
  if(read(0, &buf, 1) < 0)
    perror("read()");
  old.c_lflag |= ICANON;
  old.c_lflag |= ECHO;
  if(tcsetattr(0, TCSADRAIN, &old) < 0)
    perror("tcsetattr ~ICANON");
  return buf;
}
