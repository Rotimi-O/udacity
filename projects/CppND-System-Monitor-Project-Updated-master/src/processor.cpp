#include<iostream>
#include "processor.h"
#include "linux_parser.h"

float Processor::Utilization() {
	return this->utilization();
}

float Processor::utilization() {
	float utilization{0.0f};
	const std::vector<std::string> &v = LinuxParser::CpuUtilization();

		for(std::string const &utilization_loc : v) {
			utilization = utilization + std::stof(utilization_loc);
		}

	this->utilization_ = utilization;

	return utilization;
}
