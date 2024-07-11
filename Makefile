# the compiler: gcc for C program, define as g++ for C++
CC = gcc

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -O3

# the build target executable:
TARGET = barrett

all: $(TARGET)

barrett: barrett.c
	$(CC) $(CFLAGS) xoshiro256starstar.c -o $(TARGET) BIKE.c $(TARGET).c

clean:
	$(RM) $(TARGET)
