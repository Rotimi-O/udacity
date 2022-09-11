#include "process_data_parsers.h"

std::vector<int> ProcessData::PidsFilesParser::parsePidsFiles() {
	const std::filesystem::path proc_dir { topdir };
	std::vector<int> pids;
	for (auto const &dir_entry : std::filesystem::directory_iterator { proc_dir }) {
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

int ProcessData::PidsFilesParser::Processes(std::string token) {
	std::string line { "" };
	std::string processes { "0" };
	std::ifstream filestream(filepath);
	if (filestream.is_open()) {
		while (std::getline(filestream, line)) {
			std::istringstream linestream(line);

			std::string word;
			linestream >> word;
			if (word.compare(token) == 0) {

				linestream.seekg(0);
				linestream >> word >> processes;

			}
		}
	}
	return std::stoi(processes);
}

std::string ProcessData::PidsFilesParser::ProcessCommand(int pid) {
	std::string processCommand { "" };

	if (PidDirectoryExists(pid)) {
		std::string line { "" };
		int idx = 0;
		std::ifstream filestream(filepath);

		if (filestream.is_open()) {
			int pid;
			std::string processCommandP { "" };

			while (std::getline(filestream, line)) {
				std::istringstream linestream(line);
				linestream.seekg(idx);
				linestream >> pid >> processCommandP;
				processCommand = processCommandP.substr(1,
						processCommandP.length() - 1);
				break;
			}
		}
	}
	return processCommand;
}
