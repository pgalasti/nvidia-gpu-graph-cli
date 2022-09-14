#ifndef G_NVIDIA_SMI_PARSER_H
#define G_NVIDIA_SMI_PARSER_H

#include "StringUtils.h"
#include "Metrics.h"
#include "ProcUtils.h"

namespace GraphCli {

  class NvidiaSmiParser {

    public:
	NvidiaSmiParser();
	~NvidiaSmiParser();

	const Metrics Parse();
	//void setOptions();

    private:
  	GApi::Util::StringParser stringParser;

  };	  
}	

#endif //G_NVIDIA_SMI_PARSER_H
