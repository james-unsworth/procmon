#include "snapshot.h"
#include "parser.h"
#include <stdio.h>
#include <inttypes.h>

int main(void) {
  cpu_snapshot cpu;
  populate_cpu_snapshot(&cpu);
  print_cpu(&cpu);  
}
