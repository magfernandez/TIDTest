#ifndef __TESTNETWORKBALANCER_HPP
#define __TESTNETWORKBALANCER_HPP

#include <iostream>
#include <cppunit/extensions/HelperMacros.h>
#include "Network/NetworkBalancer.hpp"
#include <cmath>

class TestNetworkBalancer : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE( TestNetworkBalancer );
    CPPUNIT_TEST( testSendIsNotRr );
    CPPUNIT_TEST( testSendIsRandom );
    CPPUNIT_TEST_SUITE_END();

private:

    /* @brief Stores the channel result output from the send method */
    int theResult;
    /* @brief Expected RR4 result calculation */
    int theExpectedRoundRobinResult;
    /* @brief Instance to be tested */
    Network::NetworkBalancer theNetSender;
    /* @brief Maximum number of iterations to set the send test as not passed */
    const static int MAX_TESTS_TO_FAIL = 500000;
    /* @brief Flag to control the output of the send method and the expected result comparison */
    bool isMatching;
    /* @brief Maximum tolerance allowed when comparing the expected appearance ratio with the real
     * one. In this case we assume a 0.25% of variability from the max number of tests. This should
     * be enough for any random number generator without compromising the reliability of the test */
    constexpr static int RANDOM_TOLERANCE = MAX_TESTS_TO_FAIL*0.0025;

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

 //-------------------------------------------------------------------------------------------------

    /**
     * @brief testSendIsNotRr Test that iterates until the expected result based on
     * Round-Robin-4 differs from the result got from the sending procedure. The maximum number of
     * iterations assures this test finishes even if the sendTroughBalancer method is using a
     * Round-Robin-4 strategy. MAX_TESTS_TO_FAIL number has to be big enough to assure there are no
     * false negatives
     */
    void testSendIsNotRr()
    {
        // Create a data to be sent
        std::string aTestPacket( "TestPacketIsNotRr" );

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

//--------------------------------------------------------------------------------------------------

    /**
     * @brief testSendIsRandom Tests that the send method is producing a randomized output by
     * checking that all the possible combinations are appearing near the same number of times in
     * executions with a big number of iterations
     */
    void testSendIsRandom()
    {
    // Create a data to be sent
    std::string aTestPacket( "TestPacketIsRandom" );
    
    // Counter for matches
    int aMatchCounter = 0;

    // Given an execution, count the number of times that the next execution returns the next
    // number of the series. In a random system, this should be near to 1/number_of_outputs
    for ( int i=0; i<MAX_TESTS_TO_FAIL; i++ )
    {
        int aFirst  = theNetSender.sendTroughBalancer( aTestPacket.c_str(), aTestPacket.size() );
        int aSecond = theNetSender.sendTroughBalancer( aTestPacket.c_str(), aTestPacket.size() );

        if ( aSecond == ( aFirst%Network::NetworkBalancer::MAX_OUTPUTS )+1)
            aMatchCounter++;
    }

    // Check if the abs value of the difference between the real appearance count and the
    // expected one is lower than the calculated tolerance
    if ( std::abs( aMatchCounter - ( MAX_TESTS_TO_FAIL / Network::NetworkBalancer::MAX_OUTPUTS )) < RANDOM_TOLERANCE )
    {
        // If the value is between the limits, the test is passed
        CPPUNIT_ASSERT( true );
    }
    else
    {
        // If the value is bigger than the limits, the test is passed
        CPPUNIT_ASSERT( false );
    }
    }
};


#endif // __TESTNETWORKBALANCER_HPP
