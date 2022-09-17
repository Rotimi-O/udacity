#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor {
 public:
  float Utilization();
  Processor(): utilization_{0} {}

 private:
  float utilization_;
  float utilization();
};

#endif
