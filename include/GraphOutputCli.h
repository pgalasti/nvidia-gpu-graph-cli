#ifndef G_GRAPH_OUTPUT_CLI_H
#define G_GRAPH_OUTPUT_CLI_H

#include "GDefaults.h"
#include "Metrics.h"

namespace GraphCli {
	
  class OutputCli {

    public:
	DEFAULT_CONSTRUCTOR(OutputCli);
	DEFAULT_DECONSTRUCTOR(OutputCli);

	void OutputHeader(const Metrics& metrics) const;
 	void OutputProgress(const char* pszGraphName, const unsigned short utilization) const;


  };
}

#endif // G_GRAPH_OUTPUT_CLI_H
