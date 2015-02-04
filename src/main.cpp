#include <QCoreApplication>
#include <iostream>
#include <string>
#include <map>
#include <set>
#include "Tests/Unit/Network/TestNetworkBalancer.hpp"

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/ui/text/TestRunner.h>

using namespace std;
using namespace CppUnit;

//------------ Type and operation definitions problem #1 of TID Test -------------------------//
/* @brief Pair of two unsigned int elements */
typedef std::pair<unsigned int, unsigned int > t_PairIntInt;
/* @brief Pair of a strin element and a unsigned int element */
typedef std::pair<std::string, unsigned int > t_PairStrInt;

struct lexiComparePairFirst : public std::unary_function<t_PairIntInt, bool>
{
    /**
     * @brief The lexiComparePairFirst struct Definition of a lexicographical
     * comparison procedure between to std::pair<uint, uint> elements
     */
    bool operator ()( const t_PairIntInt& p1, const t_PairIntInt& p2 ) const
    {
        return std::to_string( p1.first ) < std::to_string( p2.first );
    }
};

/* @brief Set of int-int pairs, with custom '<' operator comparison */
typedef std::set< t_PairIntInt, lexiComparePairFirst > t_OrderedSetIntInt;
/* @brief Set of string-int pairs, with standard '<' operator comparison */
typedef std::set< t_PairStrInt > t_OrderedSetStrInt;




int main(int argc, char *argv[])
{
    //---------------- PROPOSED SOLUTION to problem #3 of TID Test ---------------------------//
    // Initialice test runner
    CppUnit::TextUi::TestRunner aRunner;
    // Add network balancer test suite
    aRunner.addTest( TestNetworkBalancer::suite() );
    // Start test runner
    aRunner.run();

    //---------------- PROPOSED SOLUTION to problem #1 of TID Test ---------------------------//
    // <STR, INT>
    t_OrderedSetStrInt aSetStr;
    // Fill in the map in an unordered fashion
    aSetStr.insert( std::make_pair( "alpha", 2 ) );
    aSetStr.insert( std::make_pair( "beta" , 3 ) );
    aSetStr.insert( std::make_pair( "gamma" , 5 ) );
    aSetStr.insert( std::make_pair( "alfalfa" , 1 ) );
    aSetStr.insert( std::make_pair( "gama_alta" , 4 ) );

    // Print str-int map
    std::cout << "Map <int, int> contains:\n";
    for( t_OrderedSetStrInt::iterator it = aSetStr.begin();
         it !=aSetStr.end(); it++ )
    {
      std::cout << it->first << " => " << it->second << '\n';
    }
    std::cout << '\n';

    // <INT, INT>
    t_OrderedSetIntInt aSetInt;
    // Fill in the map in an unordered fashion
    aSetInt.insert( std::make_pair( 34, 3 ) );
    aSetInt.insert( std::make_pair( 998 , 5 ) );
    aSetInt.insert( std::make_pair( 14327 , 1 ) );
    aSetInt.insert( std::make_pair( 335 , 2 ) );
    aSetInt.insert( std::make_pair( 99799 , 4 ) );

    // Print int-int map
    std::cout << "Map <string, int> contains:\n";
    for( t_OrderedSetIntInt::iterator it = aSetInt.begin();
         it !=aSetInt.end(); it++ )
    {
      std::cout << it->first << " => " << it->second << '\n';
    }
    std::cout << '\n';

    return( 0 );
}
