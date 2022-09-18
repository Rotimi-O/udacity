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
	return this->cpu_utilization_;
}

std::string Process::Command() {
	return this->command_;
}

std::string Process::Ram() {
	this->ram_ =  LinuxParser::Ram(pid_);
	return this->ram_;
}


std::string Process::User() {
	return this->user_;
}


long int Process::UpTime() {
	return this->up_time_;
}


void Process::cpuUtilization() {
	float up_time = LinuxParser::UpTime(pid_); //conversion from long to float
	float active_jiffies = LinuxParser::ActiveJiffies(pid_); //conversion from long to float

	this->cpu_utilization_ = (active_jiffies / up_time);
}

void Process::command() {
	this->command_ = LinuxParser::Command(pid_);
}

void Process::ram() {
	this->ram_ =  LinuxParser::Ram(pid_);
}

void Process::user() {
	this->user_ = LinuxParser::User(pid_);
}

void Process::upTime() {
	this->up_time_ = LinuxParser::UpTime(pid_);
}

bool Process::operator<(Process const& a) const {
	return ((this->cpu_utilization_) < (a.cpu_utilization_));
}
