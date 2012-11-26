VERSION=1.0
DATE=$(shell date)

CC=clang
CFLAGS= -Wall -g\
		-DCOMPILE_TIME="\"$(DATE)\""\
		-DVERSION="\"$(VERSION)\""

all: env.c
	$(CC) $(CFLAGS) env.c -o ../../usr/bin/env

clean:
	rm -i ../../usr/bin/env
