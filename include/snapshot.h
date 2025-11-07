#ifndef SNAPSHOT_H 
#define SNAPSHOT_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#endif /* SNAPSHOT_H */  

const size_t MAX_PID = 65536;

enum status {
  ACTIVE,
  EXPITED,
  EMPTY
}

struct process_entry {
  pid_t pid;
  char *comm;
  char *user;
  uint64_t utime;
  uint64_t stime;
  // status;
}; 

struct CPU_snapshot {
  uint64_t user,
           nice,
           system, 
           idle, 
           iowait,
           irq,
           softirq,
           steal,
           guest,
           guest_nice
}

struct system-snapshot {
  CPU_snapshot *cpu;
  process_entry[] processes;
  char *timestamp;
}

