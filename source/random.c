//
//  random.c
//  Stats Analysis
//
//  Created by Freddie Rice on 3/17/13.
//

#include "main.h"

/* Internal Function */
void generateRandomBytes(short ID);

/* Internal Globals */
#ifdef _WIN32
HCRYPTPROV hProvider = 0;
#endif
char** randomBytes;
int* byteIter;
pthread_mutex_t fileLock;

void initializeRandom(void)
{   
    int i;
    randomBytes     = (char **)malloc(sizeof(char *)*CONC_THREADS);
    for (i = 0; i < CONC_THREADS; ++i) 
        randomBytes[i] = (char *)malloc(RANDOM_BUF*sizeof(char));
    
    byteIter        = (int *)malloc(CONC_THREADS*sizeof(int));

    pthread_mutex_init(&fileLock, NULL);
    
    for( i = 0; i < CONC_THREADS; ++i )
    {
        byteIter[i] = 0;
        generateRandomBytes(i);
    }
    
#ifdef _WIN32
	if (!CryptAcquireContextW(&hProvider, 0, 0, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT | CRYPT_SILENT))
	{
		PRINT_ERR("Could not create the context for random number generation");
		return;
	}
#elif defined(__linux__) || defined(__APPLE__)
    
	char *randomness = (char *)malloc(COMPLEXITY);
    unsigned int seed = 0;
    
    getRandomBytes((char *)&seed, sizeof(seed), 0);
    getRandomBytes(randomness, COMPLEXITY, 0);
    initstate(seed, randomness, COMPLEXITY);
    
    free(randomness);
#endif
}

void cleanupRandom( void )
{
    int i;
    for( i = 0; i < CONC_THREADS; ++i )
        free(randomBytes[i]);
    free(randomBytes);
    free(byteIter);
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

void getRandomBytes(char* buf, short bufLength, short ID)
{
    pthread_mutex_lock(&fileLock);
    --bufLength; // make indexing easier
    while( bufLength > 0 )
    {
        long k = random();
        char *bytes = (char *)&k;
        for( int j = 0; 0 <= bufLength && j < 4; ++j, --bufLength )
        {
            buf[bufLength] = bytes[j];
        }
    }
    pthread_mutex_unlock(&fileLock);
    /*
    
    while( bufLength > 0 )
    {
        if( byteIter[ID] == RANDOM_BUF )
            generateRandomBytes(ID);
        
        buf[bufLength - 1] = randomBytes[ID][byteIter[ID]];
        
        byteIter[ID] += 1;
        --bufLength;
    }
    
     */
}

void generateRandomBytes(short ID)
{
#ifdef _WIN32
	if (!CryptGenRandom(hProvider, (DWORD)RANDOM_BUF, (BYTE *)randomBytes))
	{
		PRINT_ERR("Error generating randomness");
	}
#elif defined(__linux__) || defined(__APPLE__)
    
	FILE *file;
	unsigned int i;
	file = fopen(EPOCH_POOl,"a+");
	for( i = 0; i < RANDOM_BUF; ++i )
        randomBytes[ID][i] = getc(file);
    fclose(file);
    
#endif
    byteIter[ID] = 0;
}

