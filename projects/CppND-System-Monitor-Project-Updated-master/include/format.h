#ifndef FORMAT_H
#define FORMAT_H

#include <string>

namespace Format {
std::string ElapsedTime(long times);

class TimeFormater {
 public:
  std::string FormatedTime();

  TimeFormater() {}
  TimeFormater(long times) { 
    init(times);
  }
 private:
  std::string GetHoursAsHH();
  std::string GetMinutesAsMM();
  std::string GetSecondsAsSS();

  void init(long times);
  long hours{0};
  long minutes{0};
  long seconds{0};
};
};  // namespace Format

#endif