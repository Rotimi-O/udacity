#include "parsers.h"

using std::string;
using std::to_string;

std::string Parsers::OperatingSystemFileParser::parseOperatingSystemFile() {
  std::string line{""};
  std::string key{""};
  std::string value{""};
  std::ifstream filestream(path);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

std::string Parsers::KernelFileParser::parseKernelFile() {
  std::string os{""}, version{""}, kernel{""};
  std::string line{""};
  std::ifstream stream(path);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

std::vector<int> Parsers::PidsFilesParser::parsePidsFiles() {
  const std::filesystem::path proc_dir{path};
  std::vector<int> pids;
  for (auto const& dir_entry : std::filesystem::directory_iterator{proc_dir}) {
    if (dir_entry.is_directory()) {
      std::filesystem::path p = dir_entry.path();
      std::string filename = p.filename();
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  return pids;
}

double Parsers::MemInfoFilesParser::parseMemInfoFile() {
  std::string path = "/proc/meminfo";
  std::string entryName{""}, unit{""};
  std::string quantity{""};
  double totalMemory{0.0};
  double freeMemory{0.0};
  std::string line{""};
  std::ifstream filestream(path);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      linestream >> entryName >> quantity >> unit;
      if (entryName.compare("MemTotal:") == 0) {
        std::cout << entryName << quantity << unit << std::endl;
        totalMemory = std::stod(quantity);
        std::cout << totalMemory << std::endl;
      } else if (entryName.compare("MemFree:") == 0) {
        std::cout << entryName << quantity << unit << std::endl;
        freeMemory = std::stod(quantity);
        std::cout << freeMemory << std::endl;
      }
    }
  }
  double usedMemory = (totalMemory - freeMemory) * 100.0 / totalMemory;
  std::cout << usedMemory << std::endl;
  return usedMemory;
}
