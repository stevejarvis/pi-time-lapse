/*
 * Test suite for the Pi Time Lapse.
 */

#include <cxxtest/TestSuite.h>
#include "timelapsed.h"

class MTestSuite : public CxxTest::TestSuite
{
public:

    void testSetup ( void ) {
        TS_ASSERT ( 1 );
    }

    void testTimelapsedInstantiation ( void ) {
        int ms = 7;
        Timelapsed * tl = new Timelapsed ( ms );
        int s = tl->getBreak ( );
        TS_ASSERT_EQUALS ( s, ms );
        delete tl;
    }

};
