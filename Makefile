CC := g++

SO_NAME := AudaciousStats.so
SOURCE := src/*
CFLAGS = -fPIC -shared
LIBS := /usr/lib/libjsoncpp.so

build:
	g++ $(CFLAGS) $(SOURCE) $(LIBS) -o $(SO_NAME)

clean:
	rm -f $(SO_NAME)

run: build
	audacious -H
