CC := g++

SO_NAME := AudaciousStats.so
VERSION := 1.0

SOURCE := src/*
CFLAGS := -fPIC -shared -O -DVERSION=\"$(VERSION)\"
STATIC_LIBS := -ljsoncpp

build:
	g++ $(CFLAGS) $(SOURCE) -Wl,-Bstatic $(STATIC_LIBS) -Wl,-Bdynamic -o $(SO_NAME)

clean:
	rm -f $(SO_NAME) *.fuse_hidden*

run: build
	audacious -H
