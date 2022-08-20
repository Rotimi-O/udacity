#include <string>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) { 
    Format::TimeFormater timeFormater{seconds};
    return timeFormater.FormatedTime(); 
    }

     std::string Format::TimeFormater::GetHoursAsHH() {
       std::string hh = "00";
       if (hours >= 10) {
            hh = std::to_string(hours);
        } else if(hours >= 0 && hours < 10) {
           hh = "0" + std::to_string(hours);
        }
        return hh;
    }

     std::string Format::TimeFormater::GetMinutesAsMM() {
       std::string mm = "00";
       if(minutes >= 10) {
        mm = std::to_string(minutes);
       }else if(minutes >= 0 && minutes < 10) {
           mm = "0" + std::to_string(minutes);
        }
       return mm;
     }

     std::string Format::TimeFormater::GetSecondsAsSS() {
       std::string ss = "00";
       if(seconds >= 10) {
        ss = std::to_string(seconds);
       }else if(seconds >= 0 && seconds < 10) {
           ss = "0" + std::to_string(seconds);
        }
       return ss;
     }

     void Format::TimeFormater::init(long seconds) {
       long seconds_in_one_hour = 3600;
       hours = seconds / seconds_in_one_hour;
       long remainder = seconds % seconds_in_one_hour;
       minutes = remainder / 60;
       seconds = remainder % 60;
     }

     std::string Format::TimeFormater::FormatedTime() {
        std::string hh = GetHoursAsHH();
        std::string mm = GetMinutesAsMM();
        std::string ss = GetSecondsAsSS();

        return hh + ":" + mm + ":" + ss;
     }
     