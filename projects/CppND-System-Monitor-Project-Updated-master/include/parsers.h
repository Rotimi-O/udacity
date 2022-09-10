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

	parser(std::string filepathin) :
			filepath(filepathin) {}


	parser(std::string topdirin, std::string filename) :
		filepath(topdirin + filename) {}

protected:
	std::string filepath { "" };
	std::string topdir { "" };
	std::string subdir { "" };

	bool PidDirectoryExists(int pid);

	void buildfilepath(std::string filename) :
					filepath(topdir + subdir + filename) {}

	void buildfilepath() :
						filepath(procdir) {}
};

}
;
// namespace Parsers

#endif
