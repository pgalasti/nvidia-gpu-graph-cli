#ifndef G_PROC_UTILS_H
#define G_PROC_UTILS_H

#include <string>
#include "string.h"
namespace GApi::Util {

  static std::string GetExecOutput(const char* cmd) {

    std::string data;
    FILE* pStream;
    char szBuffer[256];
    char szFullCommand[256];
    strncpy(szFullCommand, cmd, 256);
    strcat(szFullCommand, " 2>&1");

    pStream = popen(szFullCommand, "r");

    if(pStream) {
      while(!feof(pStream)) {
        if(fgets(szBuffer, 256, pStream) != nullptr)
	  data.append(szBuffer);
      }
      pclose(pStream);
    }

    return data;
  }

}



#endif //G_PROC_UTILS_H
