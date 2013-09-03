CC=g++
CFLAGS=-Wall -g
CFLAGS_TEST=-g

TIMELAPSE_FILES= timelapse.cpp timelapse.h
TIMELAPSE_TEST_FILES= test-timelapse.h

all: timelapse run-tests

timelapse: $(TIMELAPSE_FILES)
	$(CC) $(CFLAGS) -o timelapse timelapse.cpp

run-tests: $(TIMELAPSE_TEST_FILES)
	cxxtestgen --error-printer -o run-tests.cpp test-timelapse.h
	$(CC) $(CFLAGS_TEST) -o run-tests run-tests.cpp

clean:
	rm -rf timelapse run-tests*
