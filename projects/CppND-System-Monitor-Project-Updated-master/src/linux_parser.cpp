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

vector<int> Pids() {
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
	systemJiffiesReader.buildfilepath(kProcDirectory, std::to_string(pid));
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
	SystemData::SystemJiffiesReader systemJiffiesReader;
	systemJiffiesReader.buildfilepath(kProcDirectory, kStatFilename);
	return systemJiffiesReader.Jiffies();
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
			std::to_string(pid), LinuxParser::kStatFilename);
	return pidsFilesParser.ProcessCommand(pid);
}

string LinuxParser::Ram(int pid) {
	ProcessData::PidsFilesParser pidsFilesParser;
	pidsFilesParser.buildfilepath(LinuxParser::kProcDirectory,
			std::to_string(pid), LinuxParser::kStatusFilename);
	return pidsFilesParser.Ram(pid);
}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid [[maybe_unused]]) {
	return string();
}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid [[maybe_unused]]) {
	return string();
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid [[maybe_unused]]) {
	return 0;
}
