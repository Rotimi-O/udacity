#include<iostream>
#include "processor.h"
#include "linux_parser.h"

float Processor::Utilization() {
	return this->utilization();
}

float Processor::utilization() {
	float cpu_utilization{0.0f};
	std::vector<std::string> utilization = LinuxParser::CpuUtilization();

	for(std::string const &utilization_loc : utilization) {
		cpu_utilization = cpu_utilization + std::stof(utilization_loc);
	}

	float up_time = (float)LinuxParser::UpTime();

	this->utilization_ = cpu_utilization / up_time;

	return this->utilization_;
}
