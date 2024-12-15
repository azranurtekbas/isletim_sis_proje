#include <stdio.h>

int main() {
    while (1) { // Sonsuz döngü: Sürekli komut istemi yazdır.
        printf("> "); // Prompt'u ekrana yazdır.
        fflush(stdout); // Print buffer'ı boşalt, hemen ekranda görünsün.

        // Kullanıcının komutunu al
        char command[256]; // Komut için bir tampon (buffer)
        fgets(command, sizeof(command), stdin); // Kullanıcıdan komut oku

        // Kullanıcı "quit" yazarsa programdan çık
        if (strncmp(command, "quit", 4) == 0) {
            printf("Kabuk kapatılıyor...\n");
            break;
        }

        // Şimdilik sadece komutu yazdırıyoruz
        printf("Komut alındı: %s", command);
    }
    return 0;
}

