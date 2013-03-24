//
//  random.c
//  Stats Analysis
//
//  Created by Freddie Rice on 3/17/13.
//

#include "main.h"

/* Internal Globals */
#ifdef _WIN32
HCRYPTPROV hProvider = 0;
#endif

void initializeRandom(void)
{   
#ifdef _WIN32
	if (!CryptAcquireContextW(&hProvider, 0, 0, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT | CRYPT_SILENT))
	{
		PRINT_ERR("Could not create the context for random number generation");
		return;
	}
#elif defined(__linux__) || defined(__APPLE__)
	char *randomness = (char *)malloc(COMPLEXITY);
    unsigned int seed = 0;
    
    getRandomBytes((char *)&seed, sizeof(seed));
    getRandomBytes(randomness, COMPLEXITY);
    initstate(seed, randomness, COMPLEXITY);
#endif
}


double getRandom( void )
{
	double randomNumber = 0;
#ifdef _WIN32
	getRandomBytes((char *)&randomNumber, (short)sizeof(double));
#elif defined(__linux__) || defined(__APPLE__)
	randomNumber = random();
#endif
	return (((double)randomNumber)/((double)0x7FFFFFFF));
}

void getRandomBytes(char* buf, short bufLength)
{
    
#ifdef _WIN32
	if (!CryptGenRandom(hProvider, (DWORD)bufLength, (BYTE *)buf))
	{
		PRINT_ERR("Error generating randomness");
	}
#elif defined(__linux__) || defined(__APPLE__)
	FILE *file;
	short i;
	file = fopen(EPOCH_POOl,"a+");
	for( i = 0; i < bufLength; ++i )
        buf[i] = getc(file);
    fclose(file);
#endif
}
