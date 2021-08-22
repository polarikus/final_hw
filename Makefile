APPNAME += main
SRCS += main.c
SRCS += stat_lib.h
SRCS += stat_lib.c

all:
	gcc $(SRCS) -o $(APPNAME)

clean:
	rm -f *.o $(APPNAME)