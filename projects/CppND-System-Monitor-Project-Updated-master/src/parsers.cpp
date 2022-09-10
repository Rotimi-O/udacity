#include "parsers.h"

bool Parsers::parser::PidDirectoryExists(int pid) {
	const std::filesystem::path proc_dir { filepath };
	std::string processCommand { "" };
	for (auto const &dir_entry : std::filesystem::directory_iterator { proc_dir }) {
		if (dir_entry.is_directory()) {
			std::filesystem::path p = dir_entry.path();
			std::string filename = p.filename();

			if (std::all_of(filename.begin(), filename.end(), isdigit)) {
				int pidloc = stoi(filename);
				if (pidloc == pid) {
					return true;
				}
			}
		}
	}
	return false;
}
