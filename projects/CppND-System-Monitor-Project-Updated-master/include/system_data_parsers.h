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
	long UpTime(int pid);

private:
	long GetJiffies(unsigned int rangeStart, unsigned int rangeEnd);
	std::vector<std::string> GetJiffies();
	long GetJiffies(unsigned int rangeStart, unsigned int rangeEnd,  const std::string &token);
	std::vector<std::string> GetJiffies(const std::string &token);
};

class MemInfoFilesParser: public Parsers::parser {
public:
	MemInfoFilesParser() {
	}

	float parseMemInfoFile();
};



class CpuFileParser: public Parsers::parser {
public:
	CpuFileParser() {
	}

	float parseMemInfoFile();
};

};
// namespace SystemData

#endif
