#ifndef TIMELAPSE
#define TIMELAPSE

class Timelapsed {

private:
    int secondsBreak;
    
public:
    Timelapsed ( int seconds );
    ~Timelapsed ( );
    int getBreak ( );
    bool daemonize ( );

};

#endif
