
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_CMD_LEN 1024

void execute_command(char *command) {
    char *args[MAX_CMD_LEN];
    char *input_file = NULL;
    int arg_count = 0;

    // Komutu parçala
    char *token = strtok(command, " ");
    while (token != NULL) {
        if (strcmp(token, "<") == 0) {
            // Giriş yönlendirme işareti buldu
            token = strtok(NULL, " ");
            if (token == NULL) {
                fprintf(stderr, "Hata: '<' işaretinden sonra dosya adı gelmelidir.\n");
                return;
            }
            input_file = token;
        } else {
            // Normal argüman
            args[arg_count++] = token;
        }
        token = strtok(NULL, " ");
    }
    args[arg_count] = NULL; // Argüman sonlandırıcı

    // Giriş dosyası varsa işleme devam et
    if (input_file) {
        int fd = open(input_file, O_RDONLY);
        if (fd < 0) {
            perror("Giriş dosyası bulunamadı");
            return;
        }

        // Alt süreci oluştur
        pid_t pid = fork();
        if (pid == 0) {
            // Çocuk süreç: Dosyayı standart girişe yönlendir
            dup2(fd, STDIN_FILENO);
            close(fd);
            execvp(args[0], args); // Komutu çalıştır
            perror("Komut çalıştırılamadı");
            exit(EXIT_FAILURE);
        } else if (pid > 0) {
            // Ebeveyn süreç: Çocuk sürecin bitmesini bekle
            close(fd);
            int status;
            waitpid(pid, &status, 0);
        } else {
            perror("Fork başarısız");
        }
    } else {
        // Giriş yönlendirme olmadan çalıştır
        pid_t pid = fork();
        if (pid == 0) {
            execvp(args[0], args);
            perror("Komut çalıştırılamadı");
            exit(EXIT_FAILURE);
        } else if (pid > 0) {
            int status;
            waitpid(pid, &status, 0);
        } else {
            perror("Fork başarısız");
        }
    }
}

int main() {
    char command[MAX_CMD_LEN];

    while (1) {
        printf("> ");
        fflush(stdout);

        // Kullanıcıdan komut al
        if (fgets(command, sizeof(command), stdin) == NULL) {
            break; // EOF
        }

        // Yeni satır karakterini kaldır
        command[strcspn(command, "\n")] = '\0';

        // quit komutuyla çıkış
        if (strcmp(command, "quit") == 0) {
            break;
        }

        // Komutu çalıştır
        execute_command(command);
    }

    return 0;
}

