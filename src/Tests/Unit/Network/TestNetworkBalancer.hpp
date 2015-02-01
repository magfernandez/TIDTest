#ifndef __TESTNETWORKBALANCER_HPP
#define __TESTNETWORKBALANCER_HPP

#include <cstdlib>
#include <cppunit/extensions/HelperMacros.h>

class TestNetworkBalancer : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE( TestNetworkBalancer );
    CPPUNIT_TEST( testSendTroughBalancer );

private:

public:

    void setUp()
    {
    }

    void tearDown()
    {
    }

    void testSendTroughBalancer()
    {
        CPPUNIT_ASSERT( true );
    }
};

#endif // __TESTNETWORKBALANCER_HPP
