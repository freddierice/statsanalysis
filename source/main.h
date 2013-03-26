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
#include <pthread.h>

#ifdef _WIN32
#include <Windows.h>
#pragma comment(lib, "advapi32.lib")
#endif

/* filenames */
#define SAMPLES_FILE "samples.csv"
#define RESULTS_FILE "results.csv"

/* threading */
#define THREADS 50000
#define CONC_THREADS 25
/* data.c */
typedef struct sample_info_struct {
    double          gen_mean;   //sample generated from this mean
    double          pop_mean;   //population mean
    double          pop_sd;     //population standard deviation
    double          sam_mean;   //sample mean
    double          sam_sd;     //sample standard deviation
    unsigned long   sam_size;   //sample size
} sample_info;
typedef struct test_results_struct {
    unsigned long   total;      //number of tests
    unsigned long   samp_size;  //size of the samples
    unsigned long   z_corr;     //z-test was correct
    unsigned long   z_err1;     //made a type I error
    unsigned long   z_err2;     //made a type II error
    unsigned long   t_corr;     //t-test was correct
    unsigned long   t_err1;     //made a type I error
    unsigned long   t_err2;     //made a type II error
    double          mean_vary;  //variability in the mean
} test_results;  
typedef struct thread_data_struct {
    unsigned long   n;          //sample size
    unsigned long   reps;       //repititions
    double          mu;         //population mean
    double          sd;         //population standard deviation
    double          meanVary;   //variation in the mean
    double          z_off;      //z offset
    double          t_off;      //t offset
} thread_data;  

/* write.c */
extern void writeSamples(sample_info *info, unsigned long samples, const char *file);
extern void writeResults(test_results *results, const char *file);


/* random.c */
#define RANDOM_BUF 25000                                    //the number of random bytes to load at once
#define COMPLEXITY 256                                      //the complexity of the algorithm 
                                                            //(256 is the max supported)
#define EPOCH_POOl "/dev/urandom"                           //the epoch pool to take the randomness
extern void initializeRandom( void );                       //seed the PRNG
extern double getRandom( void );                            //get a random number [0,1]
extern void createRandomSamples( sample_info *samples,      //create random samples based off
                                unsigned long repititions,  //the gaussian curve
                                double mu, double sd, 
                                unsigned long n, double meanVary );   
extern void getRandomBytes(char* buf, short bufLength);            //get random bytes


/* normal.c */
extern void initializeNormal(void);
extern double getRandomNormal(double mean, double sd);

/* printing to console */
#define PRINT_ERR(x)        printf("%s\n", x);
#define PRINT_DEBUG(x)      printf("%s\n", x);
#define PRINT_USAGE(name)   printf("Usage: %s <repititions> <sample size> <mean> <std> <z-cutoff> <t-cutoff> \n\n", name)
#define PRINT_HELP()        printf("%s\n","<repititions> The number of samples"); \
printf("%s\n","<sample size>   size of the samples"); \
printf("%s\n","       <mean>   mean of the randomely generated samples"); \
printf("%s\n","        <std>   standard deviation of the randomely generated samples."); \
printf("%s\n","   <z-cutoff>   a standard z score cutoff."); \
printf("%s\n","   <t-cutoff>   a standard cutoff determined by a pearson's t-test."); \
printf("\n"); 

/* test.c */
extern void test( test_results *results, sample_info *samples, unsigned long numSamples, unsigned long n, double meanVary, double z_off, double t_off );
void *doTestThread(void *info);

/* boolean type */
#ifndef __cplusplus
#define false 0
#define true 1
typedef unsigned char bool; // or #define bool int
#endif

/* Offsets for the t distribution at a 95% confidence level */


#endif /* __MAIN_H__ */
