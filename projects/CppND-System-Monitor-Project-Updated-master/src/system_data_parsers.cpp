#include <sstream>

#include "system_data_parsers.h"

std::string SystemData::OperatingSystemFileParser::parseOperatingSystemFile() {
	std::string line { "" };
	std::string key { "" };
	std::string value { "" };
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

std::string SystemData::KernelFileParser::parseKernelFile() {
	std::string os { "" }, version { "" }, kernel { "" };
	std::string line { "" };
	std::ifstream stream(path);
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
	std::ifstream filestream(path);
	if (filestream.is_open()) {
		while (std::getline(filestream, line)) {
			std::istringstream linestream(line);
			linestream >> totalUptime >> totalCoreIdletime;
			totalSystemUptime = std::stol(totalUptime);
		}
	}
	return roundFloatToLong(totalSystemUptime);
}

long SystemData::SystemJiffiesReader::getSystemJiffies() {

	std::string line { "" };
	long jiffies { 0l };

	std::ifstream filestream(path);
	if (filestream.is_open()) {
		int idx = 0;
		std::string word;
		while (std::getline(filestream, line)) {
			std::istringstream linestream(line);
			int len = line.length();
			int wordlen = 0;
			int cnt = 0;

			std::string first;
			linestream >> first;
			std::cout << "first -: " << first << std::endl;
			if (first.compare("cpu") == 0) {
				while (wordlen < len) {
					linestream.seekg(idx);
					linestream >> word;
					std::cout << cnt << " " << idx << " " << word << " " << len
							<< std::endl;

					jiffies = jiffies + std::stol(word);

					wordlen = wordlen + word.length() + 1;
					idx = wordlen + 1;
					cnt++;
				}
				break;
			}
		}
	}
	return jiffies;
}

