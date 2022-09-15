#ifndef G_FONT_COLOR_CLI_H
#define G_FONT_COLOR_CLI_H

#include <string>

namespace GraphCli::Font {
  
  enum Color {
    Bold	  = 1,
    BoldOnOff	  = 21,
    Red 	  = 31,
    Green 	  = 32,
    Yellow	  = 33,
    Blue	  = 34,
    Magenta	  = 35,
    Cyan	  = 36,
    White	  = 37,
    Default	  = 39,
    BackgroundRed = 41,
    BackgroundGre = 42,
    BackgroundYel = 43,
    BackgroundBlu = 44,
    BackgroundMag = 45,
    BackgroundCya = 46,
    BackgroundWhi = 47,
    BackgroundDft = 49
  };

  static std::string ColorOutput(const Color& color)
  {
    return std::string("\033[").append(std::to_string(color)).append("m");
  } 
}

#endif // G_FONT_COLOR_CLI_H
