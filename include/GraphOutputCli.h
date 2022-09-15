#ifndef G_GRAPH_OUTPUT_CLI_H
#define G_GRAPH_OUTPUT_CLI_H

#include <vector>
#include <string>

#include "GDefaults.h"
#include "Metrics.h"



namespace GraphCli {
	
  class OutputCli {

    public:
	OutputCli();
	DEFAULT_DECONSTRUCTOR(OutputCli);

	void OutputHeader(const Metrics& metrics) const;
 	void OutputProgress(const char* pszGraphName, const unsigned short utilization) const;
	void RecordInterval(const Metrics& metrics);
	void OutputGraphCurrentState() const;

    private:
        std::vector<unsigned short> gpuUtilizationStates;

	const std::string RenderGraphLevel(const unsigned short level) const;
  };
}

#endif // G_GRAPH_OUTPUT_CLI_H
