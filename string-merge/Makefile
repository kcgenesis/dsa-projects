CC = g++
CFLAGS = -c -Wall

useMerge.exe: useMerge.cpp useMerge.o
	$(CC) useMerge.o -o useMerge.exe

useMerge.o: useMerge.cpp
	$(CC) $(CFLAGS) useMerge.cpp

debug:
	$(CC) -g -o useGraphDebug.exe

clean:
	rm -f *.exe *.o *.stackdump *~

backup:
	test -d backups || mkdir backups
	cp *.cpp backups
	cp *.h backups
	cp Makefile backups