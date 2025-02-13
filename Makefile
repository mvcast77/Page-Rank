CC	= g++
CFLAGS	= -g -Wall
LDFLAGS	=
PROGS	= page_rank

all:	$(PROGS)

page_rank: page_rank.o csr_utility.o vector_utility.o
	$(CC) -o $@ $(LDFLAGS) page_rank.o csr_utility.o vector_utility.o

clean:;	$(RM) $(PROGS) *.o core
