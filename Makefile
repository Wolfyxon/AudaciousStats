CC := g++

SO_NAME := AudaciousStats.so
VERSION := 1.0

SOURCE := src/*
CFLAGS := -fPIC -shared -DVERSION="\$(VERSION)\"
LIBS := /usr/lib/libjsoncpp.so

build:
	g++ $(CFLAGS) $(SOURCE) $(LIBS) -o $(SO_NAME)

clean:
	rm -f $(SO_NAME)

run: build
	audacious -H
