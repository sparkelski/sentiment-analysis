CC = gcc
CFLAGS = -Wall -Wextra -std=c99
EXECUTABLE = mySA
SRCS = analysis.c functions.c

$(EXECUTABLE): $(SRCS)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm mySA