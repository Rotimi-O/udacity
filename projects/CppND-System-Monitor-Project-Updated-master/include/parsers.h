#ifndef PARSERS_H
#define PARSERS_H

#include <cmath>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

namespace Parsers {
class parser {
public:
	parser() {
	}
	parser(std::string path) :
			filepath { path } {
	}

protected:
	std::string filepath { "" };
};

}
;
// namespace Parsers

#endif
