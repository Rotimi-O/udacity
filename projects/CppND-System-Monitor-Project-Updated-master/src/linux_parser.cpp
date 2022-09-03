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
	SystemData::OperatingSystemFileParser operatingSystemFileParser{kOSPath};
  return operatingSystemFileParser.parseOperatingSystemFile();
}

string LinuxParser::Kernel() {
	SystemData::KernelFileParser kernelFileParser{kProcDirectory + kVersionFilename};
  return kernelFileParser.parseKernelFile();
}

vector<int> Pids() {
  ProcessData::PidsFilesParser pidsFilesParser{LinuxParser::kProcDirectory.c_str()};
  return pidsFilesParser.parsePidsFiles();
}

float LinuxParser::MemoryUtilization() {
  SystemData::MemInfoFilesParser memInfoFilesParser{kProcDirectory + kMeminfoFilename};
  return memInfoFilesParser.parseMemInfoFile();
}

  long LinuxParser::UpTime() {
	  SystemData::SystemUptimeFileParser systemUptimeFileParser{kProcDirectory + kUptimeFilename};
    return systemUptimeFileParser.parseSystemUptimeFile();
  }

  long LinuxParser::Jiffies() {
	  SystemData::SystemJiffiesReader systemJiffiesReader{kProcDirectory + kStatFilename};
    return systemJiffiesReader.getSystemJiffies();
  }

  // TODO: Read and return the number of active jiffies for a PID
  // REMOVE: [[maybe_unused]] once you define the function
  long LinuxParser::ActiveJiffies(int pid [[maybe_unused]]) { 
    return 0; }

  // TODO: Read and return the number of active jiffies for the system
  long LinuxParser::ActiveJiffies() { return 0; }

  // TODO: Read and return the number of idle jiffies for the system
  long LinuxParser::IdleJiffies() { return 0; }

  // TODO: Read and return CPU utilization
  vector<string> LinuxParser::CpuUtilization() { return {}; }

  // TODO: Read and return the total number of processes
  int LinuxParser::TotalProcesses() { return 0; }

  // TODO: Read and return the number of running processes
  int LinuxParser::RunningProcesses() { return 0; }

  // TODO: Read and return the command associated with a process
  // REMOVE: [[maybe_unused]] once you define the function
  string LinuxParser::Command(int pid [[maybe_unused]]) { return string(); }

  // TODO: Read and return the memory used by a process
  // REMOVE: [[maybe_unused]] once you define the function
  string LinuxParser::Ram(int pid [[maybe_unused]]) { return string(); }

  // TODO: Read and return the user ID associated with a process
  // REMOVE: [[maybe_unused]] once you define the function
  string LinuxParser::Uid(int pid [[maybe_unused]]) { return string(); }

  // TODO: Read and return the user associated with a process
  // REMOVE: [[maybe_unused]] once you define the function
  string LinuxParser::User(int pid [[maybe_unused]]) { return string(); }

  // TODO: Read and return the uptime of a process
  // REMOVE: [[maybe_unused]] once you define the function
  long LinuxParser::UpTime(int pid [[maybe_unused]]) { return 0; }
