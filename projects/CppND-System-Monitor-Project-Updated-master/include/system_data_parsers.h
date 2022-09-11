#ifndef SYSTEMDATA_H
#define SYSTEMDATA_H

#include "parsers.h"

namespace SystemData {

class OperatingSystemFileParser: public Parsers::parser {
public:
	OperatingSystemFileParser() {
	}

	std::string parseOperatingSystemFile();
};

class KernelFileParser: public Parsers::parser {
public:
	KernelFileParser() {
	}

	std::string parseKernelFile();
};

class SystemUptimeFileParser: public Parsers::parser {
public:
	SystemUptimeFileParser() {
	}

	long parseSystemUptimeFile();

private:
	long roundFloatToLong(float number) {
		return std::lroundf(number);
	}
};

class SystemJiffiesReader: public Parsers::parser {
public:
	SystemJiffiesReader() {
	}


	std::vector<std::string> Jiffies();
	long SystemJiffies();
	long IdleJiffies();
	long ActiveJiffies();
	long ActiveJiffies(int pid);

private:
	long GetJiffies(int rangeStart, int rangeEnd);
	std::vector<std::string> GetJiffies();
	long GetJiffies(int rangeStart, int rangeEnd,  const std::string &token);
	std::vector<std::string> GetJiffies(const std::string &token);
};

class MemInfoFilesParser: public Parsers::parser {
public:
	MemInfoFilesParser() {
	}

	float parseMemInfoFile();
};

}
;
// namespace SystemData

#endif
