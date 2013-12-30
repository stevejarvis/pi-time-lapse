/*
 * Just start the daemon.
 */

#include <iostream>
#include <string>

#include "timelapsed.h"

// Logpath
const std::string logpath = "/var/log/timelapsed";
// Directory to contain pictures
const std::string picdir = "/home/pi/pi-time-lapse/raspipics/";
// Delay in seconds
const int delay = 300;

int main ( int argc, char * argv[] ) {

    Timelapsed* td = new Timelapsed( delay, logpath.c_str(), picdir.c_str() );
    td->daemonize();

    return 0;
}
