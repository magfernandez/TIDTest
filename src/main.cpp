#include <QCoreApplication>
#include "Tests/Unit/Network/TestNetworkBalancer.hpp"

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/ui/text/TestRunner.h>

using namespace std;
using namespace CppUnit;

int main(int argc, char *argv[])
{
    // Initialice test runner
    CppUnit::TextUi::TestRunner aRunner;
    // Add network balancer test suite
    aRunner.addTest( TestNetworkBalancer::suite() );
    // Start test runner
    aRunner.run();

    return( 0 );
}
