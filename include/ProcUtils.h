#ifndef G_PROC_UTILS_H
#define G_PROC_UTILS_H

#include <string>
#include <algorithm>
#include "string.h"
namespace GApi::Util {

  static std::string ltrim(const std::string& s) {
    std::string result = s;
    result.erase(result.begin(), std::find_if(result.begin(), result.end(), [](unsigned char c) {
      return !std::isspace(c);
    }));
    return result;
  }

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
