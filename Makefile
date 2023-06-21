# Makefile

# Compiler
CC = g++

# Compiler flags
CFLAGS = -Wall

# Libraries
LIBS = -lncurses -pthread

# Source files
SRCS = main.cpp Airplane.cpp Airport.cpp Runways.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Output executable
EXEC = myprogram1

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(EXEC)