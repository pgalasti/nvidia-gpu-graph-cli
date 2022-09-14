#include "NvidiaSmiParser.h"
using namespace GraphCli;

NvidiaSmiParser::NvidiaSmiParser() {}
NvidiaSmiParser::~NvidiaSmiParser() {}

const Metrics NvidiaSmiParser::Parse() {

  const std::string execOutput = GApi::Util::GetExecOutput("nvidia-smi --query-gpu=utilization.gpu,utilization.memory,memory.total,memory.free,memory.used --format=csv,noheader");

  this->stringParser.Parse(execOutput, ",");
  this->stringParser.getFirst();

  std::string strGpuUtilization = this->stringParser.getToken();
  this->stringParser++;
  std::string strMemoryUtilization = this->stringParser.getToken();
  this->stringParser++;
  std::string strTotalMemory = this->stringParser.getToken();
  this->stringParser++;
  std::string strFreeMemory = this->stringParser.getToken();
  this->stringParser++;
  std::string strUsedMemory = this->stringParser.getToken();

  strGpuUtilization = GApi::Util::ltrim(strGpuUtilization);
  strMemoryUtilization = GApi::Util::ltrim(strMemoryUtilization);
  strTotalMemory = GApi::Util::ltrim(strTotalMemory);
  strFreeMemory = GApi::Util::ltrim(strFreeMemory);
  strUsedMemory = GApi::Util::ltrim(strUsedMemory);

  Metrics metrics;

  /** GPU Utilization **/
  this->stringParser.Parse(strGpuUtilization, " "); 
  this->stringParser.getFirst();
  metrics.gpuUtilization = std::stoi(this->stringParser.getToken());

  /** Memory Utilization **/
  this->stringParser.Parse(strMemoryUtilization, " ");
  this->stringParser.getFirst();
  metrics.memoryUtilization = std::stoi(this->stringParser.getToken());

  /** Total Memory **/
  this->stringParser.Parse(strTotalMemory, " ");
  this->stringParser.getFirst();
  metrics.totalMemory = std::stoi(this->stringParser.getToken());
  
  /** Free Memory**/
  this->stringParser.Parse(strFreeMemory, " ");
  this->stringParser.getFirst();
  metrics.freeMemory = std::stoi(this->stringParser.getToken());

  /** Used Memory**/
  this->stringParser.Parse(strUsedMemory, " ");
  this->stringParser.getFirst();
  metrics.usedMemory = std::stoi(this->stringParser.getToken());

  return metrics;
}

