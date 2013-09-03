/*
 * A daemon to capture timelapse photography. 
 * Focused on Raspberry Pi and Raspian.
 */

#include <cstdio>
#include "timelapsed.h"

Timelapsed::Timelapsed ( int seconds ) {
    this->secondsBreak = seconds; 
}

Timelapsed::~Timelapsed ( ) { }

int Timelapsed::getBreak ( ) {
    return this->secondsBreak;
}

bool Timelapsed::daemonize ( ) {
    /*
     * Return true if successfully deamonize, else false.
     */
}
