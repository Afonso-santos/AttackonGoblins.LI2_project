CC := gcc

CFLAGS := -IInclude -Wall -Wextra -pedantic -O2 -g
LIBS := -lncurses
	
SRCS := $(shell find . -name '*.c')
OBJS := $(SRCS:%.c=%.o)

EXEC := jogo

.PHONY: all clean

all: $(EXEC)
	
clean:
	find . -name '*.o' -exec rm -f {} \;
	rm -f $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $^ $(LIBS) -o $@