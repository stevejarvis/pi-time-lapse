CC=g++
CFLAGS=-Wall -g
CFLAGS_TEST=-g

TIMELAPSED_OBJS= timelapsed.o
TIMELAPSED_TEST_FILES= test-timelapsed.h

all: timelapsed run-tests

timelapsed: $(TIMELAPSED_OBJS) main.o
	$(CC) $(CFLAGS) $^ -o timelapsed

run-tests: runner
	./runner

runner: runner.cpp $(TIMELAPSED_OBJS)
	$(CC) $(CFLAGS_TEST) -o $@ $^

runner.cpp: $(TIMELAPSED_TEST_FILES)
	cxxtestgen -o $@ --error-printer $^

clean:
	rm -rf timelapsed runner* *.o

%.o: %.cpp
	$(CC) $(CFLAGS) -c $<
