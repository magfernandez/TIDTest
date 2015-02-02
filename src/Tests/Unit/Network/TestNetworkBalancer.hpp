#ifndef __TESTNETWORKBALANCER_HPP
#define __TESTNETWORKBALANCER_HPP

#include <cstdlib>
#include <cppunit/extensions/HelperMacros.h>
#include "Network/NetworkBalancer.hpp"

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
    const static int MAX_TESTS_TO_FAIL = 100000;
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
    
    /**
     * @brief testSendIsRandom Tests that the send method is producing a randomized output by checking
     * that all the possible combinations are appearing near the same number of times in executions
     * with a big number of iterations
     */
    void testSendIsRandom()
    {
    // Create and fill a list containing all possible combinations of four consecutive numbers
    std::list<int> aPossibleResList = std::list<int>();
    for (int i=1; i<Network::NetworkBalancer::MAX_OUTPUTS+1; i++)
    {
        for(int j=1; j<Network::NetworkBalancer::MAX_OUTPUTS+1; j++)
        {
            for (int k=1;  k<Network::NetworkBalancer::MAX_OUTPUTS+1; k++)
            {
                for (int l=1; l<Network::NetworkBalancer::MAX_OUTPUTS+1; l++)
                {
                    // Calculate a number "signature" for each four-number combination
                    aPossibleResList.insert(aPossibleResList.end(), i*1000+j*100+k*10+l);
                }
            }
        }
    }
    
    
    // Create a data to be sent
    std::string aTestPacket( "TestPacketIsRandom" );
    
    // Create a map to store the results of the iteration
    std::map<int, int> aResultsMap = std::map<int, int>();
    // Initialize all possible keys in the map
    for ( std::list<int>::iterator it = aPossibleResList.begin(); it!=aPossibleResList.end(); ++it )
    {
        //std::cout << ' ' << *it << '\n';
        aResultsMap[ *it ] = 0;
    }
        
    // Number of iterations that will be performed. Assure this number is big enough for
    // the results to be statistically sensible
    int aRepetitionNumber = Network::NetworkBalancer::MAX_OUTPUTS * MAX_TESTS_TO_FAIL;
    // Iteration process
    for ( int i=0; i<aRepetitionNumber; i++ )
    {
        // Calculate a signature value for each four iteration
        int aSignatureValue = ( theNetSender.sendTroughBalancer( aTestPacket.c_str(), aTestPacket.size() )*1000
                              + theNetSender.sendTroughBalancer( aTestPacket.c_str(), aTestPacket.size() )*100
                              + theNetSender.sendTroughBalancer( aTestPacket.c_str(), aTestPacket.size() )*10
                              + theNetSender.sendTroughBalancer( aTestPacket.c_str(), aTestPacket.size() ) );
                             
        if ( aResultsMap.find( aSignatureValue )!=aResultsMap.end() )
        {
            aResultsMap[ aSignatureValue ] = aResultsMap.at( aSignatureValue )+1;
        }
        else
        {
            // Key not found, but it should be, so an inconsistent sequence has been produced
            // Fail the test
            CPPUNIT_ASSERT( false );
        }
    }
    
    // TODO: Check that every result in the map has appeared near the same number of times than the rest
    double aEstimatedPercentage = ( (double)aRepetitionNumber / (double)aPossibleResList.size() )*100.0;
    
    for ( std::map<int, int>::iterator it = aResultsMap.begin(); it!=aResultsMap.end(); ++it )
    {
        std::cout << it->first << " -> " << (double)it->second/100.0 << "% (" << ((double)it->second/100.0-aEstimatedPercentage) << "%)" ;
    }
    
        
    }
};

#endif // __TESTNETWORKBALANCER_HPP
