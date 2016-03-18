CC = g++
CFLAGS = -c -Wall

spell.exe: spellcheck.o hash.o
	$(CC) spellcheck.o hash.o -o spell.exe

spellcheck.o: spellcheck.cpp
	$(CC) $(CFLAGS) spellcheck.cpp

hash.o: hash.cpp hash.h
	$(CC) $(CFLAGS) hash.cpp

debug:
	$(CC) -g -o spellDebug.exe spellcheck.cpp hash.cpp

clean:
	rm -f *.exe *.o *.stackdump *~

backup:
	test -d backups || mkdir backups
	cp *.cpp backups
	cp *.h backups
