$(CC) = gcc
PNTC=$(wildcard src/* .c)
PNTH=$(wildcard includes/* .h)
FLAGS= -IInclude -Wall -Wextra -pedantic -O2 -g
DIREC:=objetos/
PNTO=$(PNTC:src/%.c=$(DIREC)%.o)

run: $(PNTO)
	$(CC) $(PNTC) $(FLAGS) -lncurses -g -o jogo -lncurses -lm

compile: run
	./jogo

objetos:
	mkdir -p $@

$(DIREC)%.o: src/%.c | objetos
	$(CC) $(FLAGS) -o "$@" -c "$<"  

clean:
	rm -rf $(DIREC) jogo *.o