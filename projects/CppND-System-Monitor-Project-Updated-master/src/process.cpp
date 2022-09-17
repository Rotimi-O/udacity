#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "linux_parser.h"
#include "process.h"

using std::string;
using std::to_string;
using std::vector;


int Process::Pid() { return this->pid_; }


float Process::CpuUtilization() {
	float up_time = LinuxParser::UpTime(pid_); //conversion from long to float
	float active_jiffies = LinuxParser::ActiveJiffies(pid_); //conversion from long to float

	this->cpu_utilization_ = (active_jiffies / up_time);
	return this->cpu_utilization_;
}

std::string Process::Command() {
	this->command_ = LinuxParser::Command(pid_);
	return this->command_;
}

std::string Process::Ram() {
	this->ram_ =  LinuxParser::Ram(pid_);
	return this->ram_;
}


std::string Process::User() {
	this->user_ = LinuxParser::User(pid_);
	return this->user_;
}


long int Process::UpTime() {
	this->up_time_ = LinuxParser::UpTime(pid_);
	return this->up_time_;
}


bool Process::operator<(Process const& a) const {
	return ((this->up_time_) < (a.up_time_));
}
