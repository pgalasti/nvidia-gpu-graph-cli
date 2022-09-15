#include "NvidiaSmiParser.h"
using namespace GraphCli;

NvidiaSmiParser::NvidiaSmiParser() {}
NvidiaSmiParser::~NvidiaSmiParser() {}

const Metrics NvidiaSmiParser::Parse() {

  const std::string execOutput = GApi::Util::GetExecOutput("nvidia-smi --query-gpu=utilization.gpu,utilization.memory,memory.total,memory.free,memory.used,temperature.gpu,name,driver_version --format=csv,noheader");

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
  this->stringParser++;
  std::string strTemperature = this->stringParser.getToken();
  this->stringParser++;
  std::string strName = this->stringParser.getToken();
  this->stringParser++;
  std::string strDriver = this->stringParser.getToken();
  
  strGpuUtilization = GApi::Util::ltrim(strGpuUtilization);
  strMemoryUtilization = GApi::Util::ltrim(strMemoryUtilization);
  strTotalMemory = GApi::Util::ltrim(strTotalMemory);
  strFreeMemory = GApi::Util::ltrim(strFreeMemory);
  strUsedMemory = GApi::Util::ltrim(strUsedMemory);
  strTemperature = GApi::Util::ltrim(strTemperature);
  strName = GApi::Util::ltrim(strName);
  strDriver = GApi::Util::ltrim(strDriver);

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

  /** Temperature **/
  metrics.temperature = std::stoi(strTemperature);

  /** Product Name **/
  strncpy(metrics.szProductName, strName.c_str(), 255);

  /** Driver Information **/
  strncpy(metrics.szDriver, strDriver.c_str(), 255);

  return metrics;
}


