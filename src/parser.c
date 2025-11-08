#include <errno.h>
#include <inttypes.h>
#include <stdio.h>
#include <snapshot.h>
#include <string.h>
#include <ctype.h>
#include <dirent.h>
#include <stdlib.h>

int populate_cpu_snapshot(cpu_snapshot *cpu_sh) {
  FILE *fptr = fopen("/proc/stat", "r");
  if (fptr == NULL) { 
    errno = ENOENT;
    return -1;
  }

  char line_buffer[1000];
  fscanf(fptr, "cpu %" SCNd64 " %" SCNd64 " %" SCNd64 " %" SCNd64 " %" SCNd64 " %" SCNd64 " %" SCNd64 " %" SCNd64 " %" SCNd64 " %" SCNd64,
         &cpu_sh->user, &cpu_sh->nice, &cpu_sh->system, &cpu_sh->idle, &cpu_sh->iowait, 
         &cpu_sh->irq, &cpu_sh->softirq, &cpu_sh->steal, &cpu_sh->guest, &cpu_sh->guest_nice); 
  
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
    errno = ENOENT;
    return 1;
  }
  
  int count = 0;
  while ((entry = readdir(proc)) != NULL) {
    if (isnumeric(entry->d_name) && count < max) {
        out[count] = strtoul(entry->d_name, NULL, 0);
        count++;
    }
  }
  return count;
}

int build_proc_stat_path(char *buf, size_t buflen, pid_t pid) {
  snprintf(buf, buflen, "/proc/%d/stat", pid);
}

int populate_proc_entry(process_entry *proc) {
  

}
