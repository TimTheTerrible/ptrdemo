CC=gcc
CFLAGS=-Wall
LDFLAGS=-o
SOURCE=ptrdemo.c
HEADER=ptrdemo.h
TARGET=ptrdemo

all:	$(TARGET)

$(TARGET):	$(SOURCE) $(HEADER)
	$(CC) $(CFLAGS) $(SOURCE) $(LDFLAGS) $(TARGET)

clean:
	rm -f $(TARGET)

