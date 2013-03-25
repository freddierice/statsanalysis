//
//  main.c
//  Stats Analysis
//
//  Created by Freddie Rice on 3/14/13.
//

#include "main.h"

int main (int argc, const char * argv[])
{
    
    /*
    if(argc == 2 && (!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help")))
    {
        PRINT_USAGE(argv[0]);
        PRINT_HELP();
        return 0;
    }
    
    if(argc != 4)
    {
        PRINT_ERR("Wrong number of arguments.");
        PRINT_USAGE(argv[0]);
        return -1;
    }
     argv[0]
     
    
    unsigned long reps  = atof(argv[1]);
    unsigned long n     = atol(argv[2]);
    double mu           = atof(argv[3]);
    double sd           = atof(argv[4]);
    double z_off        = atof(argv[5]);
    double t_off        = atof(argv[6]);
    sample_info *samples;
    test_results *results;
     */
    
    unsigned long reps  = 10000;
    unsigned long n     = 100;
    double mu           = 0;
    double sd           = 1;
    double z_off        = 1.644854;
    double t_off        = 1.676551;
    double meanVary     = 5;
    sample_info *samples;
    test_results *results;

    samples = (sample_info *)malloc((unsigned long)sizeof(sample_info)*reps);
    
    PRINT_DEBUG("Initializing the random number generator");
    initializeRandom();
    
    PRINT_DEBUG("Generating the random samples");
    createRandomSamples(samples, reps, mu, sd, n, meanVary);
    
    //PRINT_DEBUG("Writing the samples to a file");
    //writeSamples(samples, reps, SAMPLES_FILE);
    
    PRINT_DEBUG("Generating results");
    results = test( samples, reps, n, meanVary, z_off, t_off );
    
    PRINT_DEBUG("Writing the results to a file");
    writeResults(results, RESULTS_FILE);
    
    PRINT_DEBUG("Cleaning up");
    free(results);
    free(samples);
    
    return 0;
}


