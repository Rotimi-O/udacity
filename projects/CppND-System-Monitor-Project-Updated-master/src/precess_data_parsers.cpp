#include "process_data_parsers.h"

std::vector<int> ProcessData::PidsFilesParser::parsePidsFiles() {
  const std::filesystem::path proc_dir{filepath};
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
