#include <sstream>

#include "system_data_parsers.h"

using std::string;
using std::to_string;

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

long SystemData::SystemJiffiesReader::getSystemJiffies() {

	std::string line { "" };
	long jiffies { 0l };

	std::ifstream filestream(filepath);
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

float SystemData::MemInfoFilesParser::parseMemInfoFile() {
  std::string entryName{""}, unit{""};
  std::string quantity{""};
  float totalMemory{0.0};
  float freeMemory{0.0};
  std::string line{""};
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
