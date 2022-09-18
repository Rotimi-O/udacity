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

				totalMemory = std::stod(quantity);

			} else if (entryName.compare("MemFree:") == 0) {

				freeMemory = std::stod(quantity);

				break;
			}
		}
	}
	float usedMemory = (totalMemory - freeMemory) * 100.0 / totalMemory;

	return usedMemory;
}

long SystemData::SystemJiffiesReader::SystemJiffies() {

	long jiffies { 0l };

	std::ifstream filestream(filepath);
	if (filestream.is_open()) {
		jiffies = GetJiffies(1, 10, "cpu");
	}
	return jiffies;
}

long SystemData::SystemJiffiesReader::ActiveJiffies() {

	long jiffies { 0l };

	std::ifstream filestream(filepath);
	if (filestream.is_open()) {
		jiffies = (GetJiffies(1, 3, "cpu") + GetJiffies(6, 7, "cpu"));
	}
	return jiffies;
}

long SystemData::SystemJiffiesReader::IdleJiffies() {

	long jiffies { 0l };

	std::ifstream filestream(filepath);
	if (filestream.is_open()) {
		jiffies = GetJiffies(4, 5, "cpu");
	}
	return jiffies;
}

std::vector<string> SystemData::SystemJiffiesReader::Jiffies() {
	std::ifstream filestream(filepath);
	std::vector<std::string> v;
	if (filestream.is_open()) {
		int cnt = 0;
		for(std::string &word : GetJiffies("cpu")) {
			if(cnt >= 1) {
				v.push_back(word);
			}
			cnt++;
		}
	}
	return v;
}

long SystemData::SystemJiffiesReader::ActiveJiffies(int pid) {
	long jiffies = 0;

	if (PidDirectoryExists(pid)) {

		std::ifstream filestream(filepath);
		if (filestream.is_open()) {
			jiffies = GetJiffies(13, 16);
		}
	}

	return jiffies;
}

long SystemData::SystemJiffiesReader::GetJiffies(int rangeStart, int rangeEnd) {
	long jiffies = 0;
	std::vector<std::string> v = GetJiffies();
	int cnt = 0;
	for (std::string &word : v) {
		if (cnt >= rangeStart && cnt <= rangeEnd) {
			jiffies = jiffies + std::stol(word);
		}
		cnt++;
	}
	return jiffies;
}

long SystemData::SystemJiffiesReader::GetJiffies(int rangeStart, int rangeEnd,
		const std::string &token) {
	long jiffies = 0;

	std::vector<std::string> v = GetJiffies(token);
	int cnt = 0;
	for (std::string &word : v) {
		if (cnt >= rangeStart && cnt <= rangeEnd) {
			jiffies = jiffies + std::stol(word);
		}
		cnt++;
	}

	return jiffies;
}

std::vector<std::string> SystemData::SystemJiffiesReader::GetJiffies() {

	std::ifstream filestream(filepath);
	std::vector<std::string> v;
	std::string line { "" };
	int idx = 0;
	if (filestream.is_open()) {
		std::string word;
		while (std::getline(filestream, line)) {
			std::istringstream linestream(line);
			int len = line.length();
			int wordlen = 0;
			int cnt = 0;

			std::string first;
			linestream >> first;

			while (wordlen < len) {
				linestream.seekg(idx);
				linestream >> word;

				v.push_back(word);
				wordlen = wordlen + word.length() + 1;
				idx = wordlen + 1;
				cnt++;
			}
			break;
		}
	}
	return v;
}
std::vector<std::string> SystemData::SystemJiffiesReader::GetJiffies(
		const std::string &token) {

	std::string line { "" };
	int idx = 0;
	std::ifstream filestream(filepath);
	std::vector<std::string> v;
	if (filestream.is_open()) {
		std::string word;
		while (std::getline(filestream, line)) {
			std::istringstream linestream(line);
			int len = line.length();
			int wordlen = 0;
			int cnt = 0;

			std::string first;
			linestream >> first;

			if (first.compare(token) == 0) {
				while (wordlen < len) {
					linestream.seekg(idx);
					linestream >> word;

					v.push_back(word);
					wordlen = wordlen + word.length() + 1;
					idx = wordlen + 1;
					cnt++;
				}
				break;
			}
		}
	}
	return v;
}

long SystemData::SystemJiffiesReader::UpTime(int pid) {
	long uptime = 0;

	if (PidDirectoryExists(pid)) {

		std::ifstream filestream(filepath);
		if (filestream.is_open()) {
			uptime = GetJiffies(22, 22);
		}
	}

	return uptime;
}

