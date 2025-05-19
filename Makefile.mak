CC = gcc
FLAGS = -fopenmp -O2
LDFLAGS = -lm
PROG = montecarlo.x
OBJS = montecarlo.o

all: $(PROG)

$(PROG): $(OBJS)
	$(CC) $(OBJS) -o $(PROG) $(FLAGS) $(LDFLAGS)

%.o: %.c
	$(CC) -c $< $(FLAGS)

clean:
	rm -f $(OBJS) $(PROG)
