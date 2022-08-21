#include "format.h"

#include <string>

using std::string;

namespace {
class TimeFormater {
 public:
  TimeFormater() {}
  TimeFormater(long times) { init(times); }

  std::string FormatedTime() {
    std::string hh = GetHoursAsHH();
    std::string mm = GetMinutesAsMM();
    std::string ss = GetSecondsAsSS();

    return hh + ":" + mm + ":" + ss;
  }

 private:
  std::string GetHoursAsHH() {
    std::string hh = "00";
    if (hours >= 10) {
      hh = std::to_string(hours);
    } else if (hours >= 0 && hours < 10) {
      hh = "0" + std::to_string(hours);
    }
    return hh;
  }

  std::string GetMinutesAsMM() {
    std::string mm = "00";
    if (minutes >= 10) {
      mm = std::to_string(minutes);
    } else if (minutes >= 0 && minutes < 10) {
      mm = "0" + std::to_string(minutes);
    }
    return mm;
  }

  std::string GetSecondsAsSS() {
    std::string ss = "00";
    if (seconds >= 10) {
      ss = std::to_string(seconds);
    } else if (seconds >= 0 && seconds < 10) {
      ss = "0" + std::to_string(seconds);
    }
    return ss;
  }

  void init(long seconds) {
    long seconds_in_one_hour = 3600;
    hours = seconds / seconds_in_one_hour;
    long remainder = seconds % seconds_in_one_hour;
    minutes = remainder / 60;
    seconds = remainder % 60;
  }

  long hours{0};
  long minutes{0};
  long seconds{0};
};
};  // namespace
// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) {
  TimeFormater timeFormater{seconds};
  return timeFormater.FormatedTime();
}
