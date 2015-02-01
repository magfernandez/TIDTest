#include "NetworkBalancer.hpp"

using namespace Network;

NetworkBalancer::NetworkBalancer() :
    theLastOutput( MAX_OUTPUTS-1 ),
    theChosenStrategy( NetworkBalancer::BALANCE_STRATEGY::ROUNDROBIN4 )
{
}

int NetworkBalancer::sendTroughBalancer( char &Buffer, int length )
{
    int anOutputChannel = calculateOutputChannel();

    // Fake sending method
    // fakeSend( Buffer, size );
    return( anOutputChannel );
}

int NetworkBalancer::calculateOutputChannel()
{
    switch ( theChosenStrategy )
    {
    case BALANCE_STRATEGY::ROUNDROBIN4: return ( ( theLastOutput++%MAX_OUTPUTS )+1 );
        break;
    case BALANCE_STRATEGY::RANDOM: return ( ( rand() % MAX_OUTPUTS )+1 );
        break;
    default: return (-1);
        break;
    }
}
