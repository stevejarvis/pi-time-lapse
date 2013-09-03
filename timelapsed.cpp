/*
 * A daemon to capture timelapse photography. 
 * Focused on Raspberry Pi and Raspian.
 */

#include <cstdio>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include "timelapsed.h"

const bool DEBUG = true;

Timelapsed::Timelapsed ( int seconds, const char * logfile ) {
    this->secondsBreak = seconds; 
    this->logpath = logfile;
}

Timelapsed::~Timelapsed ( ) {
    this->log.close ( );
}

int Timelapsed::getBreak ( ) {
    return this->secondsBreak;
}

bool Timelapsed::daemonize ( ) {
    /*
     * Return true if successfully deamonize, else false.
     */
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

    this->log.open ( this->logpath, std::ios_base::app );

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
    }

    // TODO do work

    return true;
}

