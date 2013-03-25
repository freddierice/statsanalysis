//
//  test.c
//  Stats Analysis
//
//  Created by Freddie Rice on 3/24/13.
//

#include "main.h"

/* Internal Functions */
inline double zstat( sample_info *sample );
inline double tstat( sample_info *sample );


test_results* test( sample_info *samples, unsigned long n, double z_off, double t_off )
{
    test_results *results;
    results = (test_results *)malloc((unsigned long)sizeof(test_results));
    results->total = n;
    for(;n > 0; --n)
    {
        sample_info *s = &samples[n-1];
        if( zstat(s) > z_off )
            if( s->gen_mean == s->pop_mean )
                results->z_err1 += 1;
            else
                results->z_corr += 1;
        else
            if( s->gen_mean == s->pop_mean )
                results->z_corr += 1;
            else
                results->z_err2 += 1;
        
        if( tstat(s) > t_off )
            if( s->gen_mean == s->pop_mean )
                results->t_err1 += 1;
            else
                results->t_corr += 1;
        else
            if( s->gen_mean == s->pop_mean )
                results->t_corr += 1;
            else
                results->t_err2 += 1;
    }
    
    return results;
}

double zstat( sample_info *sample )
{
    return (fabs(sample->sam_mean - sample->pop_mean))/sample->sam_sd;
}

double tstat( sample_info *sample )
{
    return sqrt(sample->sam_size)*(fabs(sample->sam_mean - sample->pop_mean))/sample->sam_sd;
}

