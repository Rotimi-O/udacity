#ifndef PROCESSDATAPARSERS_H
#define PROCESSDATAPARSERS_H

#include "parsers.h"

namespace ProcessData {
class PidsFilesParser: public Parsers::parser {
public:
	PidsFilesParser() {
	}
	PidsFilesParser(std::string path) :
			parser(path) {
	}
	std::vector<int> parsePidsFiles();

	int Processes(std::string token);

	std::string ProcessCommand(int pid);
private:
	std::string ReadFile(std::string path);
};
}
#endif
