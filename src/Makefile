all: scheduler

process.o: process.c process.h
	gcc process.c -c -o process.o

scheduler: scheduler.c process.o
	gcc scheduler.c process.o -o scheduler

clean:
	rm process.o