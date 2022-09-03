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
};
}
#endif
