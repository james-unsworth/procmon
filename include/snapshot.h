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

#define MAX_PID 65536

typedef enum status {
  ACTIVE,
  EXPITED,
  EMPTY
} status;

typedef struct process_entry {
  pid_t pid;
  char *comm;
  char *user;
  uint64_t utime;
  uint64_t stime;
  // status status;
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
  process_entry *processes[MAX_PID];
  char *timestamp;
} system_snapshot;

int print_cpu(cpu_snapshot *cpu_sh);
