CC = g++
CFLAGS = -Wall -Wextra -pedantic -O3 -std=c++17

DAYS = day01 day02 day03 day04 day05 day06 day07 day08 day09
OBJ = $(DAYS:%=src/%.o)
SOURCE	= $(DAYS:%=src/%.cpp)
day =

.PHONY: all clean run

all: $(DAYS)

run:
	@if [ -z "$(day)" ]; then \
		echo "Please specify a day to run"; \
		exit 1; \
	else \
		./$(day) < input/$(day); \
	fi

$(DAYS): %: src/%.o
	$(CC) $(CFLAGS) $< -o $@

src/%.o: src/%.cpp
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	$(RM) $(DAYS) $(OBJ)