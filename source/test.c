//
//  test.c
//  Stats Analysis
//
//  Created by Freddie Rice on 3/24/13.
//

#include "main.h"

/* Internal Functions */
inline double zstat( sample_info *sample );


void test( test_results *results, sample_info *samples, unsigned long numSamples, unsigned long n, double meanVary, double z_off, double t_off )
{
    results->total      = numSamples;
    results->samp_size  = n;
    results->mean_vary  = meanVary;
    for(;numSamples > 0; -- numSamples)
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
