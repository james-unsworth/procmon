#ifndef PARSER_H
#define PARSER_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#endif /* PARSER_H */  

int populate_cpu_snapshot(cpu_snapshot *cpu_sh);
bool isnumeric(char *string);
size_t list_pids(pid_t out[], size_t max);
int build_proc_stat_path(char *buf, size_t buflen, pid_t pid);
