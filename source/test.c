//
//  test.c
//  Stats Analysis
//
//  Created by Freddie Rice on 3/24/13.
//

#include "main.h"

/* Internal Functions */
inline double zstat( sample_info *sample );

void *doTestThread(void *info)
{
    //Initialize the datastructures
    thread_data *data       = (thread_data *)info;
    sample_info *samples    = (sample_info *)malloc(sizeof(sample_info)* data->reps);
    test_results *results   = (test_results *)malloc(sizeof(test_results));
    
    //create the samples
    createRandomSamples(samples, data->reps, data->mu, data->sd, data->n, data->meanVary, data->ID);
    
    //create the results
    test(results, samples, data->reps, data->n, data->meanVary, data->z_off, data->t_off);
    
    //write to the file
    writeResults(results, RESULTS_FILE);
    
    //free(data);
    free(samples);
    free(results);
    
    //exit this thread
    pthread_exit(NULL);
    
    return NULL;
}

void test( test_results *results, sample_info *samples, unsigned long numSamples, unsigned long n, double meanVary, double z_off, double t_off )
{
    memset((void *)results,0,sizeof(test_results));
    results->total      = numSamples;
    results->samp_size  = n;
    results->mean_vary  = meanVary;
    
    for(;numSamples > 0; --numSamples)
    {
        sample_info *s = &samples[numSamples-1];
        if( zstat(s) > z_off ){
            if( s->gen_mean == s->pop_mean )
                results->z_err1 += 1;
            else
                results->z_corr += 1;
        }else{
            if( s->gen_mean == s->pop_mean )
                results->z_corr += 1;
            else
                results->z_err2 += 1;
        }
        if( zstat(s) > t_off ){
            if( s->gen_mean == s->pop_mean )
                results->t_err1 += 1;
            else
                results->t_corr += 1;
        }else{
            if( s->gen_mean == s->pop_mean )
                results->t_corr += 1;
            else
                results->t_err2 += 1;
        }
    }
}

double zstat( sample_info *sample )
{
    return (fabs(sample->sam_mean - sample->pop_mean))/(sample->sam_sd / sqrt(sample->sam_size));
}
