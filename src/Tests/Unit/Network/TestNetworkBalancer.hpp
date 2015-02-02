#ifndef __TESTNETWORKBALANCER_HPP
#define __TESTNETWORKBALANCER_HPP

#include <cstdlib>
#include <cppunit/extensions/HelperMacros.h>
#include "Network/NetworkBalancer.hpp"

class TestNetworkBalancer : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE( TestNetworkBalancer );
    CPPUNIT_TEST( testSendTroughBalancer );
    CPPUNIT_TEST_SUITE_END();

private:

    /* @brief Stores the channel result output from the send method */
    int theResult;
    /* @brief Expected RR4 result calculation */
    int theExpectedRoundRobinResult;
    /* @brief Instance to be tested */
    Network::NetworkBalancer theNetSender;
    /* @brief Maximum number of iterations to set the send test as not passed */
    const static int MAX_TESTS_TO_FAIL = 10000;
    /* @brief Flag to control the output of the send method and the expected result comparison */
    bool isMatching;

public:

    void setUp()
    {
        theResult = -1;
        theExpectedRoundRobinResult = 0;
        theNetSender = Network::NetworkBalancer();
        isMatching = true;
    }

    void tearDown()
    {
    }

    /**
     * @brief testSendTroughBalancer Test that iterates until the expected result based on
     * Round-Robin-4 differs from the result got from the sending procedure. The maximum number of
     * iterations assures this test finishes even if the sendTroughBalancer method is using a
     * Round-Robin-4 strategy. MAX_TESTS_TO_FAIL number has to be big enough to assure there are no
     * false negatives
     */
    void testSendTroughBalancer()
    {
        // Create a data to be sent
        std::string aTestPacket( "TestPacket" );

        // Iterate until the expected result differs from the send method output. When a big enough
        // number of repetitions is reach, we set the test as failed.
        for ( int i=0; i<MAX_TESTS_TO_FAIL; i++ )
        {
            theExpectedRoundRobinResult = ( theExpectedRoundRobinResult
                                            % Network::NetworkBalancer::MAX_OUTPUTS )+1;
            theResult = theNetSender.sendTroughBalancer( aTestPacket.c_str(), aTestPacket.size() );

            //std::cout << "Test iteration " << i+1 << ". Result: " << theResult << " Expected: "
            //          << theExpectedRoundRobinResult << "\n";

            // The first time there is a difference, stop the iterations and set the test as passed
            if ( theResult!=theExpectedRoundRobinResult )
            {
                isMatching = false;
                break;
            }
        }
        // The test is passed if there is a difference in the output channel. Otherwise set the
        // test as failed
        CPPUNIT_ASSERT( !isMatching );
    }
};

#endif // __TESTNETWORKBALANCER_HPP
