#ifndef PARSERS_H
#define PARSERS_H

#include <cmath>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>
#include <unistd.h>

namespace Parsers {
class parser {
public:
	parser() {
	}

	bool PidDirectoryExists(int pid);

	void buildfilepath(std::string filepathname) {
		buildpath(filepathname);
	}

	void buildfilepath(std::string dirname, std::string filename) {
		buildpath(dirname, filename);
	}

	void buildfilepath(std::string dirname, std::string subdirname,
			std::string filename) {
		buildpath(dirname, subdirname, filename);
	}

protected:
	std::string filepath { "" };
	std::string topdir { "" };

	long extractFromVector(const std::vector<std::string> v,
			unsigned int rangeStart, unsigned int rangeEnd) {
		long jiffies = { 0l };
		if (rangeStart == rangeEnd) {
			return (std::stol(v[rangeStart - 1]));
		} else {
			for (unsigned int cnt = rangeStart - 1; cnt < rangeEnd; cnt++) {
				jiffies = jiffies + (std::stol(v[cnt]));
			}
			return jiffies;
		}
	}

	long roundToLong(float number) {
		return std::lroundf(number);
	}

	long roundToLong(double number) {
		return std::lroundf(number);
	}

private:
	void buildpath(std::string filepathname) {
		filepath = filepathname;
		topdir = filepathname;
	}

	void buildpath(std::string dirname, std::string filename) {
		filepath = dirname + filename;
		topdir = dirname;
	}

	void buildpath(std::string dirname, std::string subdirname,
			std::string filename) {
		filepath = dirname + subdirname + filename;
		topdir = dirname;
	}
};

}
;
// namespace Parsers

#endif
