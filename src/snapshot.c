#include "snapshot.h"
#include <stdio.h>
#include <inttypes.h>

int print_cpu(cpu_snapshot *cpu_sh) {
  printf("%" PRId64 " %" PRId64 " %" PRId64 " %" PRId64 " %" PRId64 " %" PRId64 " %" PRId64 " %" PRId64 " %" PRId64 " %" PRId64 "\n",
         cpu_sh->user, cpu_sh->nice, cpu_sh->system, cpu_sh->idle, cpu_sh->iowait, cpu_sh->irq, cpu_sh->softirq, cpu_sh->steal,
         cpu_sh->guest, cpu_sh->guest_nice);
}


