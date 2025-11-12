#ifndef SNAPSHOT_H 
#define SNAPSHOT_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#endif /* SNAPSHOT_H */  

#include <stddef.h>
#include <stdint.h>
#include <sys/types.h>

#define MAX_PIDS 65536
#define COMM_LENGTH 64

typedef enum status {
  ACTIVE,
  EXITED,
  EMPTY
} status;

typedef struct process_entry {
  pid_t pid;
  char comm[COMM_LENGTH];
  char state;
  char *user;
  uint64_t utime;
  uint64_t stime;
  uint64_t total_time;
  uint64_t rss;
  bool seen_this_cycle;
  enum status status;
} process_entry; 

typedef struct cpu_snapshot {
  uint64_t user,
           nice,
           system, 
           idle, 
           iowait,
           irq,
           softirq,
           steal,
           guest,
           guest_nice;
} cpu_snapshot;

typedef struct system_snapshot {
  cpu_snapshot *cpu;
  process_entry *processes[MAX_PIDS];
  char *timestamp;
} system_snapshot;

int print_cpu(cpu_snapshot *cpu_sh);
