#ifndef TIMELAPSE
#define TIMELAPSE

#include <string>
#include <iostream>
#include <fstream>

class Timelapsed {

private:
    int secondsBreak;
    const char * logpath;
    const char * picdir;
    std::ofstream logfile;
    
public:
    Timelapsed ( int seconds, const char * logfile, const char * picpath );
    ~Timelapsed ( );
    bool takePicture ( );
    int getBreak ( );
    bool daemonize ( );
    void log ( std::string message );
    std::string getTimeString ( );

};

#endif
