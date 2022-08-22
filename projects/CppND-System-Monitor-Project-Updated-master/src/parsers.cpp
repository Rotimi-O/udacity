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
 for (auto const& dir_entry : std::filesystem::directory_iterator{proc_dir}) 
    {
      if(dir_entry.is_directory()) {
      std::filesystem::path p = dir_entry.path();
      std::string filename = p.filename();
      if (std::all_of( filename.begin(),  filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
      }
    }
    return pids;
}
