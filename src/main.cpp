#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
#include <iomanip>

#include <unistd.h>
#include <termios.h>

#include "StringUtils.h"
#include "ProcUtils.h"
#include "NvidiaSmiParser.h"
#include "Metrics.h"
#include "GraphOutputCli.h"
#include "FontColorCli.h"

const char CLEAR_SCREEN[] = "\033[2J\033[H";

void displayHeader(const GraphCli::Metrics& metrics);
void displayProgressMetrics();
void displayGraphMetrics();
bool stopThread(std::atomic_bool& stop, std::thread& theThread);
bool initCheck();
char captureInput();

std::atomic_bool progressThread = false;
std::atomic_bool graphThread = false;

GraphCli::OutputCli cliOutput;

int main(int argc, char** argv) {

  if(!initCheck())
    return 1;

  graphThread = true;
  std::thread currentDisplayThread(displayGraphMetrics);
  char userInput;
  do {
    userInput = captureInput();
    
    if(userInput == 'g' || userInput == 'G') {
      userInput = ' ';
      if(!stopThread(progressThread, currentDisplayThread))
        continue;

      graphThread = true;
      currentDisplayThread = std::thread(displayGraphMetrics);

    } else if(userInput == 'p' || userInput == 'P') {
      userInput = ' ';

      if(!stopThread(graphThread, currentDisplayThread))
        continue;

      progressThread = true;
      currentDisplayThread = std::thread(displayProgressMetrics);
    }


  } while(userInput != 'q');

  /** Shutdown threads **/
  stopThread(progressThread, currentDisplayThread);
  stopThread(graphThread, currentDisplayThread);
  return 0;
}

void displayHeader(const GraphCli::Metrics& metrics) {

  std::stringstream ss;
  
  /** Product and driver version**/
  ss << GraphCli::Font::ColorOutput(GraphCli::Font::Color::Cyan);
  ss << metrics.szProductName << " - ";
  ss << GraphCli::Font::ColorOutput(GraphCli::Font::Color::Green);
  ss << "Driver " << metrics.szDriver;
  ss << GraphCli::Font::ColorOutput(GraphCli::Font::Color::Default);
  std::cout << ss.str();

  /** Default header **/
  cliOutput.OutputHeader(metrics);

  /** User Options **/
  std::cout 
	  << "[" << GraphCli::Font::ColorOutput(GraphCli::Font::Color::Cyan) 
	  << " G " << GraphCli::Font::ColorOutput(GraphCli::Font::Color::Default) 
	  << "] - " << GraphCli::Font::ColorOutput(GraphCli::Font::Color::Cyan)
	  << "Graph Mode" << std::setw(8) << GraphCli::Font::ColorOutput(GraphCli::Font::Color::Default)
	  << "[" << GraphCli::Font::ColorOutput(GraphCli::Font::Color::Cyan)
          << " P " << GraphCli::Font::ColorOutput(GraphCli::Font::Color::Default)
          << "] - " << GraphCli::Font::ColorOutput(GraphCli::Font::Color::Cyan)
	  << "Current Usage Mode" << std::setw(8) << GraphCli::Font::ColorOutput(GraphCli::Font::Color::Default)
	  << "[" << GraphCli::Font::ColorOutput(GraphCli::Font::Color::Red)
	  << " Q " << GraphCli::Font::ColorOutput(GraphCli::Font::Color::Default)
	  << "] - " << GraphCli::Font::ColorOutput(GraphCli::Font::Color::Red)
	  << "Quit" << GraphCli::Font::ColorOutput(GraphCli::Font::Color::Default)
	  << std::endl;

}

void displayProgressMetrics() {
  
  GraphCli::NvidiaSmiParser parser;
  GraphCli::Metrics metrics;
  
  auto now = std::chrono::system_clock::now(); 
  auto lastTimeMs = std::chrono::time_point_cast<std::chrono::milliseconds>(now).time_since_epoch().count(); 
  for(;;) {
    
    if(!progressThread)
      return;

    metrics = parser.Parse();
    cliOutput.RecordInterval(metrics);

    std::cout << CLEAR_SCREEN;

    displayHeader(metrics); 
    std::cout << std::endl;
    cliOutput.OutputProgress("GPU Utilization", metrics.gpuUtilization);
    cliOutput.OutputProgress("GPU Memory Utilization", metrics.memoryUtilization);
    
    now = std::chrono::system_clock::now();
    auto deltaTime = std::chrono::time_point_cast<std::chrono::milliseconds>(now).time_since_epoch().count() - lastTimeMs;
    if(1000 - deltaTime > 0) {
      std::this_thread::sleep_for(std::chrono::milliseconds(1000-deltaTime));
    }
    
    now = std::chrono::system_clock::now();     
    lastTimeMs = std::chrono::time_point_cast<std::chrono::milliseconds>(now).time_since_epoch().count();
  }
}

void displayGraphMetrics() {
  GraphCli::NvidiaSmiParser parser;
  GraphCli::Metrics metrics;

  auto now = std::chrono::system_clock::now();
  auto lastTimeMs = std::chrono::time_point_cast<std::chrono::milliseconds>(now).time_since_epoch().count();
  for(;;) {

    if(!graphThread)
      return;

    metrics = parser.Parse();
    cliOutput.RecordInterval(metrics);

    std::cout << CLEAR_SCREEN;

    displayHeader(metrics);
    cliOutput.OutputGraphCurrentState();

    now = std::chrono::system_clock::now();
    auto deltaTime = std::chrono::time_point_cast<std::chrono::milliseconds>(now).time_since_epoch().count() - lastTimeMs;
    if(1000 - deltaTime > 0) {
      std::this_thread::sleep_for(std::chrono::milliseconds(1000-deltaTime));
    }

    now = std::chrono::system_clock::now();
    lastTimeMs = std::chrono::time_point_cast<std::chrono::milliseconds>(now).time_since_epoch().count();
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

bool stopThread(std::atomic_bool& stop, std::thread& theThread) {
  
  if(!stop) 
    return false;

  stop = false;
  theThread.join();
  return true;
}
