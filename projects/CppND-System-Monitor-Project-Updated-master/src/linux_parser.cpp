#include "linux_parser.h"

#include <dirent.h>
#include <unistd.h>

#include <string>
#include <vector>

#include "parsers.h"
#include "system_data_parsers.h"
#include "process_data_parsers.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

string LinuxParser::OperatingSystem() {
	SystemData::OperatingSystemFileParser operatingSystemFileParser;
	operatingSystemFileParser.buildfilepath(kOSPath);
	return operatingSystemFileParser.parseOperatingSystemFile();
}

string LinuxParser::Kernel() {
	SystemData::KernelFileParser kernelFileParser;
	kernelFileParser.buildfilepath(kProcDirectory, kVersionFilename);
	return kernelFileParser.parseKernelFile();
}

vector<int> LinuxParser::Pids() {
	ProcessData::PidsFilesParser pidsFilesParser;
	pidsFilesParser.buildfilepath(LinuxParser::kProcDirectory.c_str());
	return pidsFilesParser.parsePidsFiles();
}

float LinuxParser::MemoryUtilization() {
	SystemData::MemInfoFilesParser memInfoFilesParser;
	memInfoFilesParser.buildfilepath(kProcDirectory, kMeminfoFilename);
	return memInfoFilesParser.parseMemInfoFile();
}

long LinuxParser::UpTime() {
	SystemData::SystemUptimeFileParser systemUptimeFileParser;
	systemUptimeFileParser.buildfilepath(kProcDirectory, kUptimeFilename);
	return systemUptimeFileParser.parseSystemUptimeFile();
}

long LinuxParser::Jiffies() {
	SystemData::SystemJiffiesReader systemJiffiesReader;
	systemJiffiesReader.buildfilepath(kProcDirectory, kStatFilename);
	return systemJiffiesReader.SystemJiffies();
}

long LinuxParser::ActiveJiffies(int pid) {
	SystemData::SystemJiffiesReader systemJiffiesReader;
	systemJiffiesReader.buildfilepath(kProcDirectory, std::to_string(pid),
			LinuxParser::kStatFilename);
	return systemJiffiesReader.ActiveJiffies(pid);
}

long LinuxParser::ActiveJiffies() {
	SystemData::SystemJiffiesReader systemJiffiesReader;
	systemJiffiesReader.buildfilepath(kProcDirectory, kStatFilename);
	return systemJiffiesReader.ActiveJiffies();
}

long LinuxParser::IdleJiffies() {
	SystemData::SystemJiffiesReader systemJiffiesReader;
	systemJiffiesReader.buildfilepath(kProcDirectory, kStatFilename);
	return systemJiffiesReader.IdleJiffies();
}

vector<string> LinuxParser::CpuUtilization() {
	float jiffies = (float) (ActiveJiffies() + IdleJiffies());
	float activejiffies = (float) (ActiveJiffies());
	vector<std::string> utilization;
	float cpuutilization = activejiffies / jiffies;
	utilization.push_back(std::to_string(cpuutilization));
	return utilization;
}

int LinuxParser::TotalProcesses() {
	ProcessData::PidsFilesParser pidsFilesParser;
	pidsFilesParser.buildfilepath(LinuxParser::kProcDirectory,
			LinuxParser::kStatFilename);
	return pidsFilesParser.Processes("processes");
}

int LinuxParser::RunningProcesses() {
	ProcessData::PidsFilesParser pidsFilesParser;
	pidsFilesParser.buildfilepath(LinuxParser::kProcDirectory,
			LinuxParser::kStatFilename);
	return pidsFilesParser.Processes("procs_running");
}

string LinuxParser::Command(int pid) {
	ProcessData::PidsFilesParser pidsFilesParser;
	pidsFilesParser.buildfilepath(LinuxParser::kProcDirectory,
			std::to_string(pid), LinuxParser::kCmdlineFilename);
	return pidsFilesParser.ProcessCommand(pid);
}

string LinuxParser::Ram(int pid) {
	ProcessData::PidsFilesParser pidsFilesParser;
	pidsFilesParser.buildfilepath(LinuxParser::kProcDirectory,
			std::to_string(pid), LinuxParser::kStatusFilename);
	return pidsFilesParser.Ram(pid);
}

string LinuxParser::Uid(int pid) {
	ProcessData::PidsFilesParser pidsFilesParser;
	pidsFilesParser.buildfilepath(LinuxParser::kProcDirectory,
			std::to_string(pid), LinuxParser::kStatusFilename);
	return pidsFilesParser.Uid(pid);
}

string LinuxParser::User(int pid) {
	ProcessData::PidsFilesParser pidsFilesParser;
	pidsFilesParser.buildfilepath(LinuxParser::kProcDirectory,
			std::to_string(pid), LinuxParser::kStatusFilename);
	std::string uid = pidsFilesParser.Uid(pid);

	pidsFilesParser.buildfilepath(LinuxParser::kPasswordPath);

	return pidsFilesParser.User(uid);;
}

long LinuxParser::UpTime(int pid) {
	SystemData::SystemJiffiesReader systemJiffiesReader;
	systemJiffiesReader.buildfilepath(LinuxParser::kProcDirectory,
			std::to_string(pid), LinuxParser::kStatFilename);

	long piduptime = systemJiffiesReader.UpTime(pid);
	long uptime = UpTime() - (piduptime / sysconf(_SC_CLK_TCK));


	return  uptime; //(UpTime());//  / sysconf(_SC_CLK_TCK)); //uptime;
}
