//
//  main.c
//  Stats Analysis
//
//  Created by Freddie Rice on 3/14/13.
//
#include "main.h"
#include "tdist.h"

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
    
    
    unsigned long reps  = 10000;    //number of samples to take
    double mu           = 0;        //mean of the samples
    unsigned long n_ini = 3;        //starting number of observations in the sample
    unsigned long n_end = 2000;     //ending number of observations in the sample
    unsigned long n_inc = 1;        //number to increment by
    double sd_ini       = 6;        //starting standard deviation
    double sd_inc       = 2;        //amound to increment the standard deviation
    double sd_end       = 15;       //ending standard deviation
    double meanVary_ini = 1;        //
    double meanVary_inc = 2;
    double meanVary_end = 10;
    
    double z_off        = 1.959964;
    
    double meanVary     = meanVary_ini;
    double sd           = sd_ini;
    unsigned long n     = n_ini;
    thread_data   threadData[THREADS];
    pthread_t     threads[CONC_THREADS];
    long iter = 0;
    long i    = 0;
    long tc   = 0;
    
    PRINT_DEBUG("Initializing the random number generator");
    initializeRandom();
    
    PRINT_DEBUG("Initializing the thread data");
    for( ; n <= n_end; n += n_inc )
    {
        for( ; sd <= sd_end; sd += sd_inc )
        {
            for( ; meanVary <= meanVary_end; meanVary += meanVary_inc )
            {
                thread_data *data = (thread_data *)malloc(sizeof(thread_data));
                data->mu          = mu;
                data->sd          = sd;
                data->n           = n;
                data->t_off       = t_offs[n-2]; //t_offs starts with 1 degree of freedom
                data->z_off       = z_off;
                data->reps        = reps;
                data->meanVary    = meanVary;
                threadData[iter]  = *data;
                /*
                printf("Generating n: %lu, meanVary: %f, sd: %f\n", n, meanVary, sd);
                createRandomSamples(samples, reps, mu, sd, n, meanVary);
        
                //PRINT_DEBUG("Writing the samples to a file");
                //writeSamples(samples, reps, SAMPLES_FILE);
                //PRINT_DEBUG("Generating results");
                test(results, samples, reps, n, meanVary, z_off, t_off );
                //PRINT_DEBUG("Writing the results to a file");
                writeResults(results, RESULTS_FILE);
                 */
                ++iter;
            }
            meanVary = meanVary_ini;
        }
        sd = sd_ini;
    }
    
    printf("%lu\n", iter);
    
    PRINT_DEBUG("Starting threads");
    for(tc = 0; tc < THREADS / CONC_THREADS; ++tc)
    {
        for( i = tc*CONC_THREADS; i < CONC_THREADS*(tc+1); ++i )
        {
            threadData[i].ID = i % CONC_THREADS;
            pthread_create(&threads[i], NULL, doTestThread, (void *)&threadData[i]);
        }
        
        for( i = tc*CONC_THREADS; i < CONC_THREADS*(tc+1); ++i )
            pthread_join(threads[i], NULL);
        
        printf("%f%% done.\n",(double)(tc*CONC_THREADS*100)/THREADS);
    }
    
    
    printf("Finished with %lu threads.\n", iter);
    PRINT_DEBUG("Cleaning up");
    cleanupRandom();
    
    
    return 0;
}


