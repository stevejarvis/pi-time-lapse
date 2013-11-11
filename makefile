CC=g++
CFLAGS=-Wall -g
CFLAGS_TEST=-g 

TIMELAPSED_OBJS= timelapsed.o
TIMELAPSED_TEST_FILES= test-timelapsed.h

all: timelapsed 

timelapsed: $(TIMELAPSED_OBJS) main.o
	$(CC) $(CFLAGS) $^ -o timelapsed

install:
	cp timelapsed /usr/local/bin/timelapsed
	cp timelapse /etc/init.d/timelapse
	update-rc.d timelapse defaults
	service timelapse start

run-tests: runner timelapsed
	./runner

runner: runner.cpp $(TIMELAPSED_OBJS)
	$(CC) $(CFLAGS_TEST) -o $@ $^

runner.cpp: $(TIMELAPSED_TEST_FILES)
	cxxtestgen -o $@ --error-printer $^

clean:
	rm -rf timelapsed runner* *.o

%.o: %.cpp
	$(CC) $(CFLAGS) -c $<
