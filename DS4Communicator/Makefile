$(shell mkdir -p bin obj)

all : main.o backend.o crc32.o
	$(CC) -o bin/DS4Communicator obj/main.o obj/backend.o obj/crc32.o -lhidapi -lncurses

main.o : src/main.c
	$(CC) -o obj/main.o -c -I/usr/local/include/hidapi -Iinclude/ src/main.c

backend.o : src/backend.c
	$(CC) -o obj/backend.o -c -I/usr/local/include/hidapi -Iinclude/ src/backend.c

crc32.o : src/crc32.c
	$(CC) -o obj/crc32.o -c -Iinclude/ src/crc32.c

clean:
	@rm -f obj/* bin/*
