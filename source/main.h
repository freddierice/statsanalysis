//
//  main.h
//  Stats Analysis
//
//  Created by Freddie Rice on 3/14/13.
//

#ifndef __MAIN_H__
#define __MAIN_H__

/* General C Libraries */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#ifdef _WIN32
#include <Windows.h>
#pragma comment(lib, "advapi32.lib")

#endif

/* data.c */
typedef struct sample_info_struct {
    double          pop_mean;    //population mean
    double          pop_sd;      //population standard deviation
    double          sam_mean;    //sample mean
    double          sam_sd;      //sample standard deviation
    unsigned long   sam_size;    //sample size
} sample_info;
extern void initializeSampleInfo( sample_info *s,           //initialize the sample info
                                 unsigned long n);    

/* write.c */
void write(sample_info *info, unsigned long samples, const char *file);


/* random.c */
#define COMPLEXITY 256                                      //the complexity of the algorithm 
                                                            //(256 is the max supported)
#define EPOCH_POOl "/dev/urandom"                           //the epoch pool to take the randomness
extern void initializeRandom( void );                       //seed the PRNG
extern double getRandom( void );                            //get a random number [0,1]
extern void createRandomSamples( sample_info *samples,      //create random samples based off
                                unsigned long repititions,  //the gaussian curve
                                double mu, double sd, 
                                unsigned long n );   
extern void getRandomBytes(char* buf, short bufLength);            //get random bytes


/* normal.c */
extern void initializeNormal(void);
extern double getRandomNormal(double sd, double mean);

/* printing to console */
#define PRINT_ERR(x)        printf("%s\n", x);
#define PRINT_USAGE(name)   printf("Usage: %s <sample size> <mean> <std> \n\n", name)
#define PRINT_HELP()        printf("%s\n","<sample size>   size of the samples"); \
printf("%s\n","<std>    standard deviation."); \
printf("\n"); 

#endif /* __MAIN_H__ */
