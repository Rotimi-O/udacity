#ifndef PARSERS_H
#define PARSERS_H

#include <string>

#include <fstream>
#include <regex>
#include <string>

namespace Parsers {
class parser {
 public:
  parser() {}
  parser(std::string path) : path{path} {}

 protected:
  std::string path{""};
};

class OperatingSystemFileParser : public parser {
 public:
  OperatingSystemFileParser() {}
  OperatingSystemFileParser(std::string path) : parser(path) {}
  std::string parseOperatingSystemFile();
};

class KernelFileParser : public parser {
public:
  KernelFileParser() {}
  KernelFileParser(std::string path) : parser(path) {}
  std::string parseKernelFile();
};
};  // namespace Parsers

#endif