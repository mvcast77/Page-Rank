CC	= g++
CFLAGS	= -g -Wall
LDFLAGS	=
PROGS	= page_rank graph

all:	$(PROGS)

page_rank: page_rank.o csr_utility.o vector_utility.o
	$(CC) -o $@ $(LDFLAGS) page_rank.o csr_utility.o vector_utility.o

graph: graph_script.cpp
	$(CC) -o $@ $(LDFLAGS) graph_script.cpp

clean:;	$(RM) $(PROGS) *.o core
