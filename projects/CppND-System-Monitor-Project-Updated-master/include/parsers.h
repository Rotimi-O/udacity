#ifndef PARSERS_H
#define PARSERS_H

#include <regex>
#include <string>
#include <filesystem>
#include <vector>
#include <iostream>
#include <fstream>

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
  double parseMemInfoFile();
};  
};  // namespace Parsers

#endif