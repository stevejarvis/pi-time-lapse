/*
 * Test suite for the Pi Time Lapse.
 */

#include <cxxtest/TestSuite.h>
#include <sys/stat.h>
#include <stdio.h>
#include <cstdlib>
#include "timelapsed.h"

class MTestSuite : public CxxTest::TestSuite {
    
    const char * logname;

public:

    void setUp ( ) {
        logname = "testlog.txt";
    }

    void tearDown ( ) {
        remove ( logname );
    }

    void testSetup ( void ) {
        TS_ASSERT ( 1 );
    }

    void testTimelapsedInstantiation ( void ) {
        int ms = 7;
        Timelapsed * tl = new Timelapsed ( ms, logname );
        int s = tl->getBreak ( );
        TS_ASSERT_EQUALS ( s, ms );
        delete tl;
    }

    void testUmaskPermissions ( void ) {
        struct stat file_perms;
        Timelapsed * tl = new Timelapsed ( 30, logname );
        TS_ASSERT ( tl->daemonize ( ) );
        stat ( logname, &file_perms );
        TS_ASSERT ( file_perms.st_mode & S_IRUSR );
        TS_ASSERT ( file_perms.st_mode & S_IWUSR );
        TS_ASSERT ( ! ( file_perms.st_mode & S_IWOTH ) );
        TS_ASSERT ( file_perms.st_mode & S_IROTH );
        delete tl;
    }

};
