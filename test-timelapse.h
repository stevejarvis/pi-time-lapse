/*
 * Test suite for the Pi Time Lapse.
 */

#include <cxxtest/TestSuite.h>
#include "timelapse.h"

class MTestSuite : public CxxTest::TestSuite
{
public:

    void testSetup ( void ) {
        TS_ASSERT ( 1 );
    }
};
