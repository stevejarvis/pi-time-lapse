/*
 * A daemon to capture timelapse photography. 
 * Focused on Raspberry Pi and Raspian.
 */

#include <cstdio>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <time.h>
#include <sstream>
#include "timelapsed.h"

const bool DEBUG = false;

Timelapsed::Timelapsed ( int seconds, const char * logfile, const char * picpath ) {
    this->secondsBreak = seconds; 
    this->logpath = logfile;
    this->picdir = picpath;
}

Timelapsed::~Timelapsed ( ) {
    this->logfile.close ( );
}

bool Timelapsed::takePicture ( ) {
    std::stringstream cmd; 
    cmd << "raspistill --exposure auto -o " 
        << this->picdir 
        << "/" << getTimeString() 
        << ".jpg";
    const char * c_cmd = cmd.str().c_str(); 
    if ( system( c_cmd ) == -1 )
    {
        log( "takePicture: Error executing picture command." );
        return false;
    }
    return true;
}

std::string Timelapsed::getTimeString ( ) {
    std::stringstream timeStr;
    time_t rawtime;
    struct tm * timeinfo;
    char buffer [80];

    time ( &rawtime );
    timeinfo = localtime ( &rawtime );

    //YY-MM-DD@HH:MM:SS (year, mon, day of mon, 24hr, min, sec)
    strftime ( buffer, 80, "%y-%m-%d@%H:%M:%S", timeinfo );
    timeStr << buffer;
    return timeStr.str( );
}

int Timelapsed::getBreak ( ) {
    return this->secondsBreak;
}

void Timelapsed::log ( std::string message ) {
    this->logfile << getTimeString() << "\t" << message << std::endl;
}

bool Timelapsed::daemonize ( ) {
    pid_t pid, sid;

    pid = fork ( );
    if ( pid < 0 ) {
        return false;
    }
    else if ( pid > 0 ) {
        exit ( 0 );
    }

    // 022 will create files with 644 perms
    umask ( S_IWGRP | S_IWOTH );

    this->logfile.open ( this->logpath, std::ios_base::app );

    // Getting a unique session ID takes process out of orphan land
    sid = setsid ( );
    if ( sid < 0 ) {
        return false;
    }

    if ( ( chdir ( "/" ) ) < 0 ) {
        return false;
    }

if ( ! DEBUG ) {
    close ( STDIN_FILENO );
    close ( STDOUT_FILENO );
    close ( STDERR_FILENO );

    log ( "Starting captures" );
    while ( 1 ) {
        takePicture();
        sleep( this->secondsBreak );
    }
}

    return true;
}

