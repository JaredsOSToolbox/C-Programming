OBJS = tuple_t.o vector_t.o

COMPILER = clang
CFLAGS = -Wall -g
OUTPUT = genetics

all: $(OBJS) main.c
	$(COMPILER) $(CFLAGS) main.c $(OBJS) -o $(OUTPUT)

vector_t.o: src/vector_t.c includes/vector_t.h
	$(COMPILER) $(CFLAGS) -c src/vector_t.c

tuple_t.o: src/tuple_t.c includes/tuple_t.h
	$(COMPILER) $(CFLAGS) -c src/tuple_t.c

clean:
	rm $(OBJS) $(OUTPUT)
