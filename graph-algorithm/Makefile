CC = g++
CFLAGS = -c -Wall

useGraph.exe: useGraph.o heap.o hash.o graph.o
	$(CC) useGraph.o heap.o hash.o graph.o -o useGraph.exe

useGraph.o: useGraph.cpp
	$(CC) $(CFLAGS) useGraph.cpp

graph.o: graph.cpp graph.h
	$(CC) $(CFLAGS) graph.cpp

heap.o: heap.cpp heap.h
	$(CC) $(CFLAGS) heap.cpp

hash.o: hash.cpp hash.h
	$(CC) $(CFLAGS) hash.cpp

debug:
	$(CC) -g -o useGraphDebug.exe useGraph.cpp graph.cpp heap.cpp hash.cpp

clean:
	rm -f *.exe *.o *.stackdump *~

backup:
	test -d backups || mkdir backups
	cp *.cpp backups
	cp *.h backups
	cp Makefile backups
