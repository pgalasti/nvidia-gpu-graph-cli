#ifndef G_GRAPH_OUTPUT_CLI_H
#define G_GRAPH_OUTPUT_CLI_H

#include "GDefaults.h"
namespace GraphCli {
	
  class GraphOutputCli {

    public:
	DEFAULT_CONSTRUCTOR(GraphOutputCli);
	DEFAULT_DECONSTRUCTOR(GraphOutputCli);

 	void Output(const char* pszGraphName, const unsigned short utilization) const;

  };
}

#endif // G_GRAPH_OUTPUT_CLI_H
