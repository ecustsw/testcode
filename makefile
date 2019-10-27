DB2PATH=/home/db2inst3/sqllib

INCLDIR= -I$(DB2PATH)/include -I./include

LIBPATH=-L$(DB2PATH)/lib -L./lib
LIBS=-lstdc++

LINKFLAG=-Xlinker

CC=g++

ALLEXE=test systest pipe_read pipe_write server client fork msg_read msg_write semaphore\
		 shm

CPPDEFS = -Wall  -g -D_MT  -O2

SRCFILES=test main test2 

SRCFILESSYSCALL=syscall_test

all:$(ALLEXE)
	@echo "$(ALLEXE) built successful!"



test: $(SRCFILES:=.o)
	g++ $(LINKFLAG) $(LIBPATH) -O2 -o ./test $(SRCFILES:=.o) $(LIBS)

systest: $(SRCFILESSYSCALL:=.o)
	g++ $(LINKFLAG) $(LIBPATH) -o ./systest $(SRCFILESSYSCALL:=.o) $(LIBS)

pipe_read:pipe_read.o
	g++ $(LINKFLAG) $(LIBPATH) -o ./pipe_read pipe_read.o $(LIBS)

pipe_write:pipe_write.o
	g++ $(LINKFLAG) $(LIBPATH) -o ./pipe_write pipe_write.o $(LIBS)

server:server.o
	g++ $(LINKFLAG) $(LIBPATH) -o ./server server.o $(LIBS)

client:client.o
	g++ $(LINKFLAG) $(LIBPATH) -o ./client client.o $(LIBS)

fork:fork.o
	g++ $(LINKFLAG) $(LIBPATH) -o ./fork fork.o $(LIBS)

msg_read:msg_read.o
	g++ $(LINKFLAG) $(LIBPATH) -o ./msg_read msg_read.o $(LIBS)

msg_write:msg_write.o
	g++ $(LINKFLAG) $(LIBPATH) -o ./msg_write msg_write.o $(LIBS)

semaphore:semaphore.o
	g++ $(LINKFLAG) $(LIBPATH) -o ./semaphore semaphore.o $(LIBS)

shm:shm.o
	g++ $(LINKFLAG) $(LIBPATH) -o ./shm shm.o $(LIBS)


.SUFFIXES:.cpp .o

.cpp.o:
	g++ -c  $(CPPDEFS) $(INCLDIR) $< -o $@

clean:
	rm -f *.o $(ALLEXE)

