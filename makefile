OBJECTS = cooking.o tests.o

# OS identification from: https://stackoverflow.com/questions/714100/os-detecting-makefile
OS := $(shell uname -s)

ifeq ($(OS), Darwin)
  CUNIT_PATH_PREFIX = /usr/local/Cellar/cunit/2.1-3/
  CUNIT_DIRECTORY = cunit
endif
ifeq ($(OS), Linux)
  CUNIT_PATH_PREFIX = /util/CUnit/
  CUNIT_DIRECTORY = CUnit/
endif

CC = gcc
NO_DEBUG_FLAGS = -c -Wall -std=c11
DEBUG_FLAGS = -g -c -Wall -std=c11
FLAGS = $(DEBUG_FLAGS)

SRC = cooking.c
TST = tests.c
GEX = world-gprof
VEX = world-valgrind
TEX = test
FLAGS = -pg -fprofile-arcs -ftest-coverage
CFLAGS = -L $(CUNIT_PATH_PREFIX)lib -I $(CUNIT_PATH_PREFIX)include/$(CUNIT_DIRECTORY)
CLIB = -lcunit

.PHONY: clean
clean:
	rm -rf *~ *.o $(GEX) $(TEX) $(VEX) runner *.dSYM *.gc?? analyze.txt gmon.out

cooking.o: cooking.c
	gcc -c -g -O0 -Wall -std=c11 $(SRC)

runner: runner.c cooking.o
	$(CC) -g -O0 -Wall -std=c11 -o runner cooking.o runner.c

tests.o: tests.c
	gcc -c -g -O0 -Wall -std=c11 -I $(CUNIT_PATH_PREFIX)include/$(CUNIT_DIRECTORY) $(TST)

c-exec: cooking.o
	gcc -g -O0 -Wall $(FLAGS) $(CFLAGS) -o $(GEX) $(SRC) runner.c

c-test: tests.o cooking.o
	gcc -g -O0 -Wall $(FLAGS) $(CFLAGS) -o $(TEX) $(SRC) tests.c $(CLIB)

v-exec: cooking.o
	gcc -g -O0 -Wall $(CFLAGS) -o $(VEX) $(SRC) runner.c

.PHONY: andRunPerformance
andRunPerformance:
	make clean
	make c-exec
	./$(GEX)
	gprof -b ./$(GEX) gmon.out > analyze.txt
	gcov $(SRC)
	@echo "Look at analyze.txt for gprof timing data"
	@echo "Look at $(SRC).gcov for gcov annotated source code with execution counts"

.PHONY: andRunTests
andRunTests:
	make clean
	make c-test
	./$(TEX)
	gcov $(SRC)
	@echo "Look at $(SRC).gcov for gcov annotated source code with execution counts"

.PHONY: andRunCallGrind
andRunCallGrind:
	make clean
	make v-exec
	@echo "******************************************************************************"
	@echo "** Running program on large file using callgrind. This may take a minute... **"
	@echo "******************************************************************************"
	valgrind --tool=callgrind ./$(VEX) 1000 1000
	@echo "******************************************************************************"
	@echo "** Done! Use callgrind_annotate to interpret the data file                  **"
	@echo "******************************************************************************"
