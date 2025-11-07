#include <errno.h>
#include <inttypes.h>
#include <stdio.h>
#include <snapshot.h>

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
