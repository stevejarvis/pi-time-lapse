#ifndef TIMELAPSE
#define TIMELAPSE

#include <string>
#include <iostream>
#include <fstream>

class Timelapsed {

private:
    int secondsBreak;
    const char * logpath;
    std::ofstream log;
    
public:
    Timelapsed ( int seconds, const char * logfile );
    ~Timelapsed ( );
    int getBreak ( );
    bool daemonize ( );

};

#endif
