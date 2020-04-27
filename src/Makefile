all: scheduler

process.o: process.c process.h
	gcc process.c -c -o process.o

heap.o: heap.c heap.h
	gcc heap.c -c -o heap.o

fifo.o: fifo.c fifo.h
	gcc fifo.c -c -o fifo.o

rr.o: rr.c rr.h
	gcc rr.c -c -o rr.o

sjf.o: sjf.c sjf.h
	gcc sjf.c -c -o sjf.o

psjf.o: psjf.c psjf.h
	gcc psjf.c -c -o psjf.o

scheduler: scheduler.c process.o heap.o fifo.o rr.o sjf.o psjf.o
	gcc scheduler.c process.o heap.o fifo.o rr.o sjf.o psjf.o -o scheduler

clean:
	rm process.o fifo.o rr.o sjf.o psjf.o