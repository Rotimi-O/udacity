#ifndef PROCESS_H
#define PROCESS_H

#include <string>

class Process {
 public:
  int Pid();
  std::string User();
  std::string Command();
  float CpuUtilization();
  std::string Ram();
  long int UpTime();
  bool operator<(Process const& a) const;

  Process(): pid_{0} , cpu_utilization_{0.0f}, user_{""}, command_{""}, ram_{""}, up_time_{0l} {}

  Process(int pid): pid_{pid} {
	  this->cpuUtilization();
	  this->user();
	  this->command();
	  this->ram();
	  this->upTime();
  }

 private:
  int pid_;
  float cpu_utilization_;
  std::string user_;
  std::string command_;
  std::string ram_;
  long int up_time_;

  void user();
  void command();
  void cpuUtilization();
  void ram();
  void upTime();
};

#endif
