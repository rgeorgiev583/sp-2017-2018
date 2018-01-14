RM := rm -f

SRC := $(wildcard *.c)
BIN := $(patsubst %.c,%,$(SRC))

CFLAGS += -std=c11
ifdef DEBUG
CFLAGS += -g -Og
else
CFLAGS += -g
endif

.PHONY: all clean

all: $(BIN)

%: %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	$(RM) $(BIN)
