CC=gcc
OBJECTS=
GLIB=`pkg-config --cflags --libs glib-2.0`

test_helloWorld: helloWorld
	./build/helloWorld

wordfreq_test: wordFreq
	./build/wordfreq

wordfreq: wordFreq.o
	$(CC) build/wordFreq.o -o wordfreq $(GLIB)

helloWorld: helloWorld.o
	$(CC) build/helloWorld.o -o build/helloWorld $(GLIB)

wordFreq: wordFreq.o
	$(CC) build/wordFreq.o -o build/wordFreq $(GLIB)

helloWorld.o: helloWorld.c
	$(CC) -c helloWorld.c -o build/helloWorld.o $(GLIB)

wordFreq.o: wordFreq.c
	$(CC) -c wordFreq.c -o build/wordFreq.o $(GLIB)
