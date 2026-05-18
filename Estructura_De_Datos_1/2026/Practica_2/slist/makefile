CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c11
TARGET_GLIST = test_glist
TARGET_SLIST = test_slist
OBJS_GLIST = test_glist.o glist.o
OBJS_SLIST = test_slist.o slist.o

.PHONY: all run clean run_glist run_slist

all: $(TARGET_GLIST) $(TARGET_SLIST)

$(TARGET_GLIST): $(OBJS_GLIST)
	$(CC) $(CFLAGS) $(OBJS_GLIST) -o $(TARGET_GLIST)

$(TARGET_SLIST): $(OBJS_SLIST)
	$(CC) $(CFLAGS) $(OBJS_SLIST) -o $(TARGET_SLIST)

test_glist.o: test_glist.c glist.h
	$(CC) $(CFLAGS) -c test_glist.c -o test_glist.o

glist.o: glist.c glist.h
	$(CC) $(CFLAGS) -c glist.c -o glist.o

test_slist.o: test_slist.c slist.h
	$(CC) $(CFLAGS) -c test_slist.c -o test_slist.o

slist.o: slist.c slist.h
	$(CC) $(CFLAGS) -c slist.c -o slist.o

run: run_glist run_slist

run_glist: $(TARGET_GLIST)
	./$(TARGET_GLIST)

run_slist: $(TARGET_SLIST)
	./$(TARGET_SLIST)

clean:
	rm -f $(OBJS_GLIST) $(OBJS_SLIST) $(TARGET_GLIST) $(TARGET_SLIST)