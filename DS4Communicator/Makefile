$(shell mkdir -p bin obj)

SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c, obj/%.o, $(SRC))

INCLUDES = -Iinclude/ -I/usr/local/include/hidapi
LIBS = -lhidapi -lncurses

all : $(OBJ)
	$(CC) -o bin/DS4Communicator $(OBJ) $(LIBS)

obj/%.o: src/%.c
	$(CC) -c $(INCLUDES) $< -o $@

clean:
	@rm -f obj/* bin/*
