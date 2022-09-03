#include <sstream>

#include "system_data_parsers.h"

using std::string;
using std::to_string;
using std::istringstream;

std::string SystemData::OperatingSystemFileParser::parseOperatingSystemFile() {
	std::string line { "" };
	std::string key { "" };
	std::string value { "" };
	std::ifstream filestream(filepath);
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

std::string SystemData::KernelFileParser::parseKernelFile() {
	std::string os { "" }, version { "" }, kernel { "" };
	std::string line { "" };
	std::ifstream stream(filepath);
	if (stream.is_open()) {
		std::getline(stream, line);
		std::istringstream linestream(line);
		linestream >> os >> version >> kernel;
	}
	return kernel;
}

long SystemData::SystemUptimeFileParser::parseSystemUptimeFile() {
	std::string totalUptime { "" }, totalCoreIdletime { "" };
	long totalSystemUptime { 0l };
	std::string line { "" };
	std::ifstream filestream(filepath);
	if (filestream.is_open()) {
		while (std::getline(filestream, line)) {
			std::istringstream linestream(line);
			linestream >> totalUptime >> totalCoreIdletime;
			totalSystemUptime = std::stol(totalUptime);
		}
	}
	return roundFloatToLong(totalSystemUptime);
}

float SystemData::MemInfoFilesParser::parseMemInfoFile() {
	std::string entryName { "" }, unit { "" };
	std::string quantity { "" };
	float totalMemory { 0.0 };
	float freeMemory { 0.0 };
	std::string line { "" };
	std::ifstream filestream(filepath);
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
				break;
			}
		}
	}
	float usedMemory = (totalMemory - freeMemory) * 100.0 / totalMemory;
	std::cout << usedMemory << std::endl;
	return usedMemory;
}

long SystemData::SystemJiffiesReader::SystemJiffies() {

	long jiffies { 0l };

	std::ifstream filestream(filepath);
	if (filestream.is_open()) {
		jiffies = GetJiffies(filestream, 1, 7, "cpu");
	}
	return jiffies;
}

long SystemData::SystemJiffiesReader::ActiveJiffies() {

	long jiffies { 0l };

	std::ifstream filestream(filepath);
	if (filestream.is_open()) {
		jiffies = GetJiffies(filestream, 1, 3, "cpu");
	}
	return jiffies;
}

long SystemData::SystemJiffiesReader::IdleJiffies() {

	long jiffies { 0l };

	std::ifstream filestream(filepath);
	if (filestream.is_open()) {
		jiffies = GetJiffies(filestream, 4, 7, "cpu");
	}
	return jiffies;
}

long SystemData::SystemJiffiesReader::ActiveJiffies(int pid) {
	const std::filesystem::path proc_dir { filepath };
	long jiffies = 0;
	for (auto const &dir_entry : std::filesystem::directory_iterator { proc_dir }) {
		if (dir_entry.is_directory()) {
			std::filesystem::path p = dir_entry.path();
			std::string filename = p.filename();

			if (std::all_of(filename.begin(), filename.end(), isdigit)) {
				int pidloc = stoi(filename);
				if (pidloc == pid) {
					std::string path1 = filepath + filename + "/stat";
					std::cout << "file -: " << path1 << std::endl;
					std::ifstream filestream(path1);
					if (filestream.is_open()) {
						jiffies = GetJiffies(filestream, 13, 16);
						break;
					}
				}
			}
		}
	}
	return jiffies;
}

long SystemData::SystemJiffiesReader::GetJiffies(std::ifstream &filestream,
		int rangeStart, int rangeEnd) {

	long jiffies = 0;
	std::string word;
	std::string line { "" };
	int idx = 0;
	while (std::getline(filestream, line)) {
		std::istringstream linestream(line);
		int len = line.length();
		int wordlen = 0;
		int cnt = 0;
		std::string first;
		linestream >> first;
		std::cout << "first -: " << first << std::endl;
		while (wordlen < len) {
			linestream.seekg(idx);
			linestream >> word;
			std::cout << cnt << " " << idx << " " << word << " " << len
					<< std::endl;
			if (cnt >= rangeStart && cnt <= rangeEnd) {
				jiffies = jiffies + std::stol(word);
			}
			wordlen = wordlen + word.length() + 1;
			idx = wordlen + 1;
			cnt++;
		}
		std::cout << std::endl;
		std::cout << line << std::endl;
	}
	return jiffies;
}

long SystemData::SystemJiffiesReader::GetJiffies(std::ifstream &filestream,
		int rangeStart, int rangeEnd, const std::string &token) {

	std::string line { "" };
	int idx = 0;
	long jiffies = 0;
	std::string word;
	while (std::getline(filestream, line)) {
		std::istringstream linestream(line);
		int len = line.length();
		int wordlen = 0;
		int cnt = 0;

		std::string first;
		linestream >> first;
		std::cout << "first -: " << first << std::endl;
		if (first.compare(token) == 0) {
			while (wordlen < len) {
				linestream.seekg(idx);
				linestream >> word;
				std::cout << cnt << " " << idx << " " << word << " " << len
						<< std::endl;

				if (cnt >= rangeStart && cnt <= rangeEnd) {
					jiffies = jiffies + std::stol(word);
				}

				wordlen = wordlen + word.length() + 1;
				idx = wordlen + 1;
				cnt++;
			}
			break;
		}
	}
	return jiffies;
}

