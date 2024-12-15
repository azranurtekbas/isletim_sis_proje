CC = gcc
CFLAGS = -Wall

# Kaynak dosyası ve çıktı dosyası
SRC = src/main.c
OUT = shell_project

# Varsayılan hedef
all: $(OUT)

# Derleme komutu
$(OUT): $(SRC)
	$(CC) $(CFLAGS) -o $(OUT) $(SRC)

# Temizleme komutu
clean:
	rm -f $(OUT)
