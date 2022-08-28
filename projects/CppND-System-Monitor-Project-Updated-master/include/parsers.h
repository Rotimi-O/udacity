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

class PidsFilesParser : public parser {
 public:
  PidsFilesParser() {}
  PidsFilesParser(std::string path) : parser(path) {}
  std::vector<int> parsePidsFiles();
};

class MemInfoFilesParser : public parser {
 public:
  MemInfoFilesParser() {}
  MemInfoFilesParser(std::string path) : parser(path) {}
  float parseMemInfoFile();
};

class SystemUptimeFileParser : public parser {
 public:
  SystemUptimeFileParser() {}
  SystemUptimeFileParser(std::string path) : parser(path) {}
  long parseSystemUptimeFile();

 private:
  long roundFloatToLong(float number) { return std::lroundf(number); }
};
};  // namespace Parsers

#endif