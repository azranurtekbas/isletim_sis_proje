#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Ana program
int main() {
    char command[256]; // Kullanıcının komutlarını tutmak için bir tampon

    while (1) { // Sonsuz döngü, kullanıcı quit yazana kadar devam eder
        printf("> "); // Prompt'u ekrana yazdır
        fflush(stdout); // Print buffer'ı hemen boşalt ki prompt görünsün

        // Kullanıcıdan komut al
        if (fgets(command, sizeof(command), stdin) == NULL) {
            printf("\nHata: Komut okunamadı.\n");
            continue;
        }

        // Yeni satır karakterini temizle (fgets bunu da alır)
        command[strcspn(command, "\n")] = '\0';

        // Kullanıcı "quit" yazarsa programı sonlandır
        if (strcmp(command, "quit") == 0) {
            printf("Kabuk kapatılıyor...\n");
            break;
        }

        // Şimdilik komutu ekrana yazdırıyoruz (geliştirme için placeholder)
        printf("Komut alındı: %s\n", command);
    }

    return 0;
}


