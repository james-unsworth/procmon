#include <errno.h>
#include <inttypes.h>
#include <stdio.h>
#include <snapshot.h>
#include <string.h>
#include <ctype.h>
#include <dirent.h>
#include <stdlib.h>
#include "parser.h"

int populate_cpu_snapshot(cpu_snapshot *cpu_sh) {
  FILE *proc_stat = fopen("/proc/stat", "r");
  if (proc_stat == NULL) { 
    fclose(proc_stat);
    return -1;
  }

  char line_buffer[1000];
  fscanf(proc_stat, "cpu %" SCNd64 " %" SCNd64 " %" SCNd64 " %" SCNd64 " %" SCNd64 " %" SCNd64 " %" SCNd64 " %" SCNd64 " %" SCNd64 " %" SCNd64,
         &cpu_sh->user, &cpu_sh->nice, &cpu_sh->system, &cpu_sh->idle, &cpu_sh->iowait, 
         &cpu_sh->irq, &cpu_sh->softirq, &cpu_sh->steal, &cpu_sh->guest, &cpu_sh->guest_nice); 

  fclose(proc_stat);
  
}

bool isnumeric(char *string) {
  for (int i = 0; i < strlen(string); i++) {
    if (!isdigit(string[i])) {
      return false;
    }
  }  
  return true;
}

size_t list_pids(pid_t out[], size_t max) {
  DIR *proc;
  struct dirent *entry;

  proc = opendir("/proc");
  if (proc == NULL) {
    closedir(proc);
    return 1;
  }
  
  int count = 0;
  while ((entry = readdir(proc)) != NULL) {
    if (isnumeric(entry->d_name) && count < max) {
        out[count] = strtoul(entry->d_name, NULL, 0);
        count++;
    }
  }
  closedir(proc);
  return count;
}

int build_proc_stat_path(char *buf, size_t buflen, pid_t pid) {
  snprintf(buf, buflen, "/proc/%d/stat", pid);
}

int populate_proc_entry(process_entry *proc, pid_t pid) {
  char path[PROC_PATH_LEN];
  build_proc_stat_path(path, PROC_PATH_LEN, pid);

  FILE *proc_pid_stat = fopen(path, "r");
  if (proc_pid_stat == NULL) return 1;

  char line[LINE_LEN];
  if (fgets(line, sizeof(line), proc_pid_stat) == NULL) {
    fclose(proc_pid_stat);
    return 1;
  }
  fclose(proc_pid_stat);

  // PID
  char pid_str[PID_STR_LEN];
  snprintf(pid_str, sizeof(pid_str), "%d", pid);

  size_t len = strlen(pid_str);
  if (memcmp(pid_str, line, len) != 0) return 1;
  if (line[len] != ' ') return 1;
  proc->pid = pid;

  // COMM
  size_t line_len = strlen(line);
  int comm_start = -1;
  int comm_end = -1;
  for (int i = len + 1; i < line_len; i++) {
    if (line[i] == '(') {
      comm_start = i + 1;
    }
    if (line[i] == ')') {
      comm_end = i;
      break;
    }
  }
  if (comm_start == -1 || comm_end == -1) return 1;
  line[comm_end] = '\0';

  if (comm_end + 1 >= line_len) return 1;
  if (line[comm_end + 1] != ' ') return 1;

  char *comm = &line[comm_start];
  char *rest = &line[comm_end + 2];
  
  strncpy(proc->comm, comm, COMM_LENGTH - 1);
  proc->comm[COMM_LENGTH - 1] = '\0';

  // STATE
  char *save;
  char *tok = strtok_r(rest, " ", &save);
  if (tok == NULL) return 1;
  proc->state = tok[0];

  // UTIME, STIME + RSS
  int field = 3;
  bool utime_ok = false;
  bool stime_ok = false;
  while (field <= 24 && (tok = strtok_r(NULL, " ", &save)) != NULL) {
    field++;
    if (field == 14) { 
      proc->utime = strtoull(tok, NULL, 10);
      utime_ok = true;
    }
    else if (field == 15) {
    proc->stime = strtoull(tok, NULL, 10);
    stime_ok = true;
    }
    else if (field == 24) {
      proc->rss = strtoull(tok, NULL, 10);
    }
  }
  if (!utime_ok || !stime_ok) return 1;

  proc->total_time = proc->utime + proc->stime;
  proc->status = ACTIVE;
  proc->seen_this_cycle = true;
  return 0;
}


