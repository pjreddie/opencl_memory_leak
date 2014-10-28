CC=gcc
COMMON=-Wall
CFLAGS= $(COMMON) -O0 -g
EXEC = leak
UNAME = $(shell uname)
CFLAGS += $(COMMON)
ifeq ($(UNAME), Darwin)
LDFLAGS=-framework OpenCL -lm
else
LDFLAGS=-lm -lOpenCL
CFLAGS += -march=native
endif

OBJ=leak.o
all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

%.o: %.c 
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm -rf $(OBJ) $(EXEC)

