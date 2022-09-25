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
	std::string processCommand { " " };

	if (PidDirectoryExists(pid)) {
		std::string line { "" };

		std::ifstream filestream(filepath);

		if (filestream.is_open()) {
			std::getline(filestream, line);
			if (!line.empty() && line.compare(" ") != 0) {
				processCommand = line;
			}

		}
	}
	return processCommand;
}

std::string ProcessData::PidsFilesParser::Ram(int pid) {
	std::string ram { "0" };

	if (PidDirectoryExists(pid)) {
		std::string line { "" };
		std::ifstream filestream(filepath);

		if (filestream.is_open()) {

			while (std::getline(filestream, line)) {
				std::replace(line.begin(), line.end(), ':', ' ');
				std::istringstream linestream(line);

				std::string word { "" };
				std::string memunit { "" };
				int wordlen = 0;
				int idx = 0;
				int len = line.length();
				while (wordlen < len) {
					linestream.seekg(idx); //always start from the start of the line
					linestream >> word;
					if (word.compare("VmRSS") == 0) {

						linestream.seekg(0); //rewind
						linestream >> word >> ram >> memunit;
						break;
					}
					wordlen = wordlen + word.length() + 1;
					idx = wordlen + 1;
				}
			}
		}
	}
	ram = std::to_string(roundToLong((std::stof(ram)) / 1024.0f)); //convert to MB
	return ram;
}

std::string ProcessData::PidsFilesParser::Uid(int pid) {
	std::string uid { " " };

	if (PidDirectoryExists(pid)) {
		std::string line { "" };
		std::ifstream filestream(filepath);

		if (filestream.is_open()) {

			while (std::getline(filestream, line)) {
				std::replace(line.begin(), line.end(), ':', ' ');
				std::istringstream linestream(line);

				std::string word { "" };
				int wordlen = 0;
				int idx = 0;
				int len = line.length();
				while (wordlen < len) {
					linestream.seekg(idx); //always start from the start of the line
					linestream >> word;
					if (word.compare("Uid") == 0) {

						linestream.seekg(0); //rewind
						linestream >> word >> uid;
						break;
					}
					wordlen = wordlen + word.length() + 1;
					idx = wordlen + 1;
				}
			}
		}
	}
	return uid;
}

std::string ProcessData::PidsFilesParser::User(std::string uid) {
	std::string user { " " };

	std::string line { "" };

	std::ifstream filestream(filepath);

	if (filestream.is_open()) {

		while (std::getline(filestream, line)) {
			std::replace(line.begin(), line.end(), ':', ' ');

			std::istringstream linestream(line);

			std::string throwaway { "" };
			std::string userid { "" };

			int wordlen = 0;
			int idx = 0;
			int len = line.length();
			while (wordlen < len) {
				linestream.seekg(idx); //always start from the start of the line
				linestream >> user >> throwaway >> userid;
				if (userid.compare(uid) == 0) {
					return user;
				}
				wordlen = wordlen + userid.length() + 1;
				idx = wordlen + 1;
			}
		}
	}

	return user;
}
