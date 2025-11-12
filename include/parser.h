#ifndef PARSER_H
#define PARSER_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#endif /* PARSER_H */ 

#define PROC_PATH_LEN 64
#define PID_STR_LEN 16
#define LINE_LEN 4096

int populate_cpu_snapshot(cpu_snapshot *cpu_sh);
bool isnumeric(char *string);
size_t list_pids(pid_t out[], size_t max);
int build_proc_stat_path(char *buf, size_t buflen, pid_t pid);
int populate_proc_entry(process_entry *proc, pid_t pid);
