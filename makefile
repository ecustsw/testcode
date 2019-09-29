DB2PATH=/home/db2inst3/sqllib

INCLDIR= -I$(DB2PATH)/include -I./include

LIBPATH=-L$(DB2PATH)/lib -L./lib
LIBS=-lstdc++

LINKFLAG=-Xlinker

CC=g++

CPPDEFS = -Wall  -g -D_MT  -O2

SRCFILES=test main test2 

SRCFILESSYSCALL=syscall_test

all:testapp systest
	@echo "test systest built successful!"

testapp: $(SRCFILES:=.o)
	g++ $(LINKFLAG) $(LIBPATH) -O2 -o ./test $(SRCFILES:=.o) $(LIBS)

systest: $(SRCFILESSYSCALL:=.o)
	g++ $(LINKFLAG) $(LIBPATH) -o ./systest $(SRCFILESSYSCALL:=.o) $(LIBS)

pipe_read:pipe_read.o
	g++ $(LINKFLAG) $(LIBPATH) -o ./pipe_read pipe_read.o $(LIBS)

pipe_write:pipe_write.o
	g++ $(LINKFLAG) $(LIBPATH) -o ./pipe_write pipe_write.o $(LIBS)

.SUFFIXES:.cpp .o


.cpp.o:
	g++ -c  $(CPPDEFS) $(INCLDIR) $< -o $@

clear:
	rm *.o test systest

