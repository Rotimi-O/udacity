#include <cmath>
#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include<iostream>

#include "linux_parser.h"
#include "process.h"

using std::string;
using std::to_string;
using std::vector;

int Process::Pid() {
	return this->pid_;
}

float Process::CpuUtilization() {
	return this->cpu_utilization_;
}

std::string Process::Command() {
	return this->command_;
}

std::string Process::Ram() {
	return this->ram_;
}

std::string Process::User() {
	return this->user_;
}

long int Process::UpTime() {
	return this->up_time_;
}

void Process::cpuUtilization() {
	float active_jiffies = (float) (LinuxParser::ActiveJiffies(pid_));
	this->cpu_utilization_ = (active_jiffies / (LinuxParser::UpTime(pid_)));
}

void Process::compareMeasure() {
	this->compare_measure_= LinuxParser::timemeasure(pid_);
}

void Process::command() {
	this->command_ = LinuxParser::Command(pid_);
}

void Process::ram() {
	this->ram_ = LinuxParser::Ram(pid_);
}

void Process::user() {
	this->user_ = LinuxParser::User(pid_);
}

void Process::upTime() {
	this->up_time_ = LinuxParser::UpTime(pid_);
}

bool Process::operator<(Process const &a) const {
	if(this->compare_measure_ > a.compare_measure_) {
		return true;
	}
	return false;
}
