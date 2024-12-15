// shell.h
#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

#define MAX_CMD_LEN 1024

// Arka planda çalışan süreçlerin PID'lerini tutacak bir dizi
extern pid_t background_pids[MAX_CMD_LEN];
extern int bg_pid_count;

// Fonksiyon prototipleri
void execute_command(char *command);
void check_background_processes();

#endif // SHELL_H
