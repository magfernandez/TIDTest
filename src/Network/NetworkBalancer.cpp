#include "NetworkBalancer.hpp"

using namespace Network;

NetworkBalancer::NetworkBalancer() :
    theLastOutput( MAX_OUTPUTS ),
    theChosenStrategy( NetworkBalancer::BALANCE_STRATEGY::RANDOM )
{
}

int NetworkBalancer::sendTroughBalancer( const char *Buffer, int length )
{
    // Calculate the output channel
    int anOutputChannel = calculateOutputChannel();

    // Fake sending method
    // fakeSend( Buffer, size );

    // Return the channel that has been used for sending the data
    return( anOutputChannel );
}

int NetworkBalancer::calculateOutputChannel()
{
    // Calculate the output depending on the chosen strategy
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
