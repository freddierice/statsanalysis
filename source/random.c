//
//  random.c
//  Stats Analysis
//
//  Created by Freddie Rice on 3/17/13.
//

#include "main.h"

/* Internal Functions */
void getRandomBytes(char* buf, short bufLength);

void initializeRandom(void)
{
    char *randomness = (char *)malloc(COMPLEXITY);
    unsigned int seed = 0;
    
    getRandomBytes((char *)&seed, sizeof(seed));
    getRandomBytes(randomness, COMPLEXITY);
    
    initstate(seed, randomness, COMPLEXITY);
}

double getRandomNormal( double mu, double sd )
{
    
    return 0;
}


double getRandom( void )
{
    return (((double)random())/((double)0x7FFFFFFF));
}

void getRandomBytes(char* buf, short bufLength)
{
    FILE *file;
    file = fopen(EPOCH_POOl,"a+");
    for( short i = 0; i < bufLength; ++i )
        buf[i] = getc(file);
    fclose(file);
}

