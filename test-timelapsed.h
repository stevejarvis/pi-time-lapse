/*
 * Test suite for the Pi Time Lapse.
 */

#include <cxxtest/TestSuite.h>
#include <sys/stat.h>
#include <stdio.h>
#include <cstdlib>
#include <stdlib.h>
#include <fstream>
#include "timelapsed.h"

class MTestSuite : public CxxTest::TestSuite {
    
    const char * logname;
    const char * picpath;

public:

    void setUp ( ) {
        logname = "/home/pi/pi-time-lapse/testlog.txt";
        picpath = "/home/pi/pi-time-lapse/pics/";
    }

    void tearDown ( ) {
        remove ( logname );
    }

    void testSetup ( void ) {
        TS_ASSERT ( 1 );
    }

    void testTimelapsedInstantiation ( void ) {
        int ms = 7;
        Timelapsed * tl = new Timelapsed ( ms, logname, picpath );
        int s = tl->getBreak ( );
        TS_ASSERT_EQUALS ( s, ms );
        delete tl;
    }

    void testUmaskPermissions ( void ) {
        struct stat file_perms;
        Timelapsed * tl = new Timelapsed ( 30, logname, picpath );
        tl->daemonize ( );
        stat ( logname, &file_perms );
        TS_ASSERT ( file_perms.st_mode & S_IRUSR );
        TS_ASSERT ( file_perms.st_mode & S_IWUSR );
        TS_ASSERT ( ! ( file_perms.st_mode & S_IWOTH ) );
        TS_ASSERT ( file_perms.st_mode & S_IROTH );
        delete tl;
    }

    void testLogFile ( void ) {
        std::ifstream in;
        std::string message = "hello log";
        std::string recv;
        Timelapsed * tl = new Timelapsed ( 300, logname, picpath );  

        tl->daemonize ( );
        tl->log ( message );
        in.open ( logname, std::ifstream::in );
        std::getline ( in, recv );
        in.close ( );
        TS_ASSERT_EQUALS ( message, 
                           recv.substr( recv.length() - message.length() ) );
        delete tl;
    }

    void testPictureTaken ( void ) {
        TS_ASSERT ( system(NULL) );
        // TODO 
    }

};

