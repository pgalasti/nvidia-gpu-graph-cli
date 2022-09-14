#ifndef G_METRICS_H
#define G_METRICS_H

#include <cstring>
namespace GraphCli {
  
  struct Metrics {
    Metrics() {
      memset(this, 0, sizeof(Metrics));
    }
    unsigned short gpuUtilization;
    unsigned short memoryUtilization;
    unsigned int totalMemory;
    unsigned int freeMemory;
    unsigned int usedMemory;
  };
}	


#endif //G_METRIX_H
