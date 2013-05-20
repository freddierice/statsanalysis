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
    sample_info *samples    = (sample_info *)malloc(sizeof(sample_info)*data->reps);
    test_results *results   = (test_results *)malloc(sizeof(test_results));
    
    stick_this_thread_to_core(data->ID);
    
    //create the samples
    createRandomSamples(samples, data);
    
    //create the results
    test(results, samples, data);
    
    //write to the file
    writeResults(results, RESULTS_FILE);
    
    //free(data);
    free(samples);
    free(results);
    
    //exit this thread
    pthread_exit(NULL);
    
    return NULL;
}

void stick_this_thread_to_core(int core_id) {
    int num_cores = sysconf(_SC_NPROCESSORS_ONLN);
    if (core_id >= num_cores)
        return;
    
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(core_id, &cpuset);
    
    pthread_t current_thread = pthread_self();    
    pthread_setaffinity_np(current_thread, sizeof(cpu_set_t), &cpuset);
}

void test( test_results *results, sample_info *samples, thread_data *data )
{
    memset((void *)results,0,sizeof(test_results));
    results->total      = data->reps;
    results->samp_size  = data->n;
    results->sd         = data->sd;
    results->mean_vary  = data->meanVary;
    
    long numSamples = data->reps;
    for(;numSamples > 0; --numSamples)
    {
        sample_info *s = &samples[numSamples-1];
        if( zstat(s) > data->z_off ){
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
        if( zstat(s) > data->t_off ){
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
