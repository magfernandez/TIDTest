#ifndef __NETWORKBALANCER_HPP
#define __NETWORKBALANCER_HPP

#include <stdlib.h>

namespace Network
{
    class NetworkBalancer
    {
    public:

        /**
         * @brief NetworkBalancer Class constructor
         */
        NetworkBalancer();

        /**
         * @brief sendTroughBalancer Sends a buffer through an automatically chosen output channel,
         * trying to balance the output
         * @param Buffer Reference to buffer to be sent
         * @param length Length of buffer
         * @return Output channel chosen
         */
        int sendTroughBalancer( const char *Buffer, int length );

        /* @brief Total number of output channels */
        const static int MAX_OUTPUTS = 4;

    private:

        /**
         * @brief calculateOutputChannel Calculates an output channel following the strategy
         * stated in this class
         * @return Calculated output channel, a number between 1 and 4
         */
        int calculateOutputChannel();

    private:

        /**
         * @brief The BALANCE_STRATEGY enum Enumerated class containing the strategies that can be
         * chosen for this class to produce the output
         */
        enum class BALANCE_STRATEGY { ROUNDROBIN4, RANDOM };

        /* @brief theLastOutput Contains the last chosen channel */
        int theLastOutput;

        /* @brief theChosenStrategy Currently chosen strategy  */
        BALANCE_STRATEGY theChosenStrategy;
    };
}

#endif // __NETWORKBALANCER_HPP
