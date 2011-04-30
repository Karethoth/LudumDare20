CC = g++

EXEC = entry

CFLAGS = -g -Wall -c -I /usr/include/ncurses
LFLAGS = -g -lstdc++ -lncurses

SRCS = $(wildcard src/*.cpp)
OBJS = $(patsubst %,obj/%,$(subst src/,,$(SRCS:.cpp=.o)))

all : $(EXEC)
	@

$(EXEC) : obj $(OBJS)
	$(CC) -o $(EXEC) $(OBJS) $(LFLAGS) 

obj/%.o : src/%.cpp
	$(CC) $(CFLAGS) -o $@ $<

obj :
	mkdir obj

clean :
	rm -f $(EXEC) obj/*.o

