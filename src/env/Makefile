VERSION=1.0
DATE=$(shell date)

CC=gcc
CFLAGS= -Wall -g\
		-DCOMPILE_TIME="\"$(DATE)\""\
		-DVERSION="\"$(VERSION)\""

all: env.c
	$(CC) $(CFLAGS) env.c -o ../../bin/env
