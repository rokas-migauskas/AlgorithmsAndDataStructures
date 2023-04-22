main.exe : main.c queue.h queue.o priority_queue.h priority_queue.o 
	gcc -std=c11 -o main.exe main.c queue.o priority_queue.o

queue.o : queue.c queue.h
	gcc -c -std=c11 queue.c -o queue.o

priority_queue.o : priority_queue.c priority_queue.h
	gcc -c -std=c11 priority_queue.c -o priority_queue.o
