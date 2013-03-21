//
//  data.c
//  Stats Analysis
//
//  Created by Freddie Rice on 3/14/13.
//

#include "main.h"

void createRandomSamples( sample_info *samples, unsigned long repititions, double mu, double sd, unsigned long n )
{
	unsigned long i;
	unsigned long j;

    initializeSampleInfo(samples, repititions);
    for (i = 0; i < repititions; ++i) 
    {
        double *data = (double *)malloc(n*sizeof(double));
        double mean = 0;
		double sumSquareDifs;

        for( j = 0; j < n; ++j )
        {
            data[j] = getRandomNormal(mu, sd);
            mean += data[j];
        }
        mean /= (double)n;
        
        sumSquareDifs = 0;
        for( j = 0; j < n; ++j )
            sumSquareDifs += pow(mean-data[j],2);
        
        samples[i].pop_mean = mu;
        samples[i].pop_sd   = sd;
        samples[i].sam_mean = mean;
        samples[i].sam_sd   = sumSquareDifs / (double)n;
        samples[i].sam_size = n;
    }
}

void initializeSampleInfo( sample_info *s, unsigned long samples )
{
    s = (sample_info *)malloc((unsigned long)sizeof(sample_info));
}