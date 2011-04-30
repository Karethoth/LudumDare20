CC = g++

EXEC = entry

CFLAGS = -g -Wall -c
LFLAGS = -g -Wall -lstdc++

SRCS = $(wildcard src/*.cpp)
OBJS = $(patsubst %,obj/%,$(subst src/,,$(SRCS:.cpp=.o)))

all : $(EXEC)
	@

$(EXEC) : obj $(OBJS)
	$(CC) $(LFLAGS) -o $(EXEC) $(OBJS)

obj/%.o : src/%.cpp
	$(CC) $(CFLAGS) -o $@ $<

obj :
	mkdir obj

clean :
	rm -f $(EXEC) obj/*.o

