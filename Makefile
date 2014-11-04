CC=gcc
COMMON=-Wall -I/usr/local/cuda/include
CFLAGS=-O0 -g
EXEC = leak
UNAME = $(shell uname)
CFLAGS += $(COMMON)
LDFLAGS=-lm -lOpenCL

OBJ=leak.o
all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

%.o: %.c 
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm -rf $(OBJ) $(EXEC)

