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
#ifdef _WIN32
    
#elif defined(__linux__) || defined(__APPLE__)
	char *randomness = (char *)malloc(COMPLEXITY);
    unsigned int seed = 0;
    
    getRandomBytes((char *)&seed, sizeof(seed));
    getRandomBytes(randomness, COMPLEXITY);
    initstate(seed, randomness, COMPLEXITY);
#endif
}

double getRandomNormal( double mu, double sd )
{
    
    return 0;
}


double getRandom( void )
{
#ifdef _WIN32
    return 0.0;
#elif defined(__linux__) || defined(__APPLE__)
	return (((double)random())/((double)0x7FFFFFFF));
#endif
}

void getRandomBytes(char* buf, short bufLength)
{
    
#ifdef _WIN32

#elif defined(__linux__) || defined(__APPLE__)
	FILE *file;
	short i;
	file = fopen(EPOCH_POOl,"a+");
	for( i = 0; i < bufLength; ++i )
        buf[i] = getc(file);
    fclose(file);
#endif
}

