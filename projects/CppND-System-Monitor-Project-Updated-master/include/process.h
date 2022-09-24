#ifndef PROCESS_H
#define PROCESS_H

#include <string>

class Process {
public:
	int Pid();
	std::string User();
	std::string Command();
	float CpuUtilization();
	std::string Ram();
	long int UpTime();
	bool operator<(Process const &a) const;

	Process() :
			pid_ { 0 }, cpu_utilization_ { 0.0f }, user_ { "" }, command_ { "" }, ram_ {
					"" }, up_time_ { 0l }, compare_measure_(0l){
	}

	void setCpuUtilization() {
		this->cpuUtilization();
	}

	void setRam() {
		this->ram();
	}

	void setUser() {
		this->user();
	}

	void setUpTime() {
		this->upTime();
	}

	void setCommand() {
		this->command();
	}

	void setPid(int pid) {
		this->pid_ = pid;
	}

	void setCompareMeasure() {
		this->compareMeasure();
	}


private:
	int pid_;
	float cpu_utilization_;
	std::string user_;
	std::string command_;
	std::string ram_;
	long int up_time_;
	long compare_measure_;

	void user();
	void command();
	void cpuUtilization();
	void compareMeasure();
	void ram();
	void upTime();

};

#endif
