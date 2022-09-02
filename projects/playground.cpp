#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <filesystem>
#include <regex>

using std::istringstream;
int main()
{
  std::string path = "/proc/meminfo";
  std::string entryName{""}, unit{""};
  std::string quantity{""};
  double totalMemory{0.0};
  double freeMemory{0.0};
  std::string line{""};
  std::ifstream filestream(path);
  if (filestream.is_open())
  {
    while (std::getline(filestream, line))
    {
      // std::cout << line << std::endl;
      std::istringstream linestream(line);
      linestream >> entryName >> quantity >> unit;
      // std::cout <<entryName <<quantity <<unit <<std::endl;
      if (entryName.compare("MemTotal:") == 0)
      {
        std::cout << entryName << quantity << unit << std::endl;
        totalMemory = std::stod(quantity);
        std::cout << totalMemory << std::endl;
      }
      else if (entryName.compare("MemFree:") == 0)
      {
        std::cout << entryName << quantity << unit << std::endl;
        freeMemory = std::stod(quantity);
        std::cout << freeMemory << std::endl;
      }
    }
  }
  double usedMemory = (totalMemory - freeMemory) * 100.0 / totalMemory;
  std::cout << usedMemory << std::endl;
  // return usedMemory;

  std::string entry{""};
  std::string user{""};
  std::string nice{""};
  std::string systemmode{""};
  std::string idle{""};
  std::string iowait{""};
  std::string irq{""};
  std::string softirq{""};
  std::string line1{""};
  path = "/proc/stat";
  std::ifstream filestream1(path);
  if (filestream1.is_open())
  {
    while (std::getline(filestream1, line1))
    {
      std::istringstream linestream(line1);
      linestream >> entry >> user >> nice >> systemmode >> idle >> iowait >> irq >> softirq;
      if (entry.compare("cpu0") == 0)
      {
        std::cout << entry << std::endl;
      }
    }
  }

  path = "/proc/";
  const std::filesystem::path proc_dir{path};
  std::string line2{""};
  std::vector<int> pids;
  long jiffies = 0;
  for (auto const &dir_entry : std::filesystem::directory_iterator{proc_dir})
  {
    if (dir_entry.is_directory())
    {
      std::filesystem::path p = dir_entry.path();
      std::string filename = p.filename();
      
      if (std::all_of(filename.begin(), filename.end(), isdigit))
      {
        int pid = stoi(filename);
        std::string path1 = path + filename + "/stat";
        std::cout << "file -: " <<path1 <<std::endl;
        std::ifstream filestream2(path1);
        if (filestream2.is_open())
        {
          std::string word;
          int idx = 0;
          while (std::getline(filestream2, line2))
          {
            std::istringstream linestream(line2);
            int len = line2.length();
            int wordlen = 0;
            int cnt = 0;
            while(wordlen < len) {
            linestream.seekg(idx);
            linestream >> word;
            std::cout <<cnt << " " << idx << " " << word << " " << len << std::endl;
            if(cnt >= 13 && cnt <= 16) {
              jiffies = jiffies + std::stol(word);
            }
            wordlen = wordlen + word.length() + 1;
            idx = wordlen + 1;
            cnt++;
            }
            std::cout << std::endl;
            std::cout << line2 <<std::endl;

          }
        }
      }
    }
  }
}
