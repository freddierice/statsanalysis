//
//  data.c
//  Stats Analysis
//
//  Created by Freddie Rice on 3/14/13.
//

#include "main.h"

void createRandomSamples( sample_info *samples, unsigned long repititions, double mu, double sd, unsigned long n, double meanVary )
{
	unsigned long i;
	unsigned long j;

    for (i = 0; i < repititions; ++i) 
    {
        double *data = (double *)malloc(n*sizeof(double));
        double mean = 0;
		double sumSquareDifs;

        //get half from the actual mean, and half not.
        double gen_mean = mu;
        if( i % 2 )
            gen_mean = getRandomNormal(mu, 5*sd);
        for( j = 0; j < n; ++j )
        {
            data[j] = getRandomNormal(gen_mean, sd);
            mean += data[j];
        }
        
        mean /= (double)n;
        
        sumSquareDifs = 0;
        for( j = 0; j < n; ++j )
            sumSquareDifs += pow(mean-data[j],2);
        
        samples[i].pop_mean = mu;
        samples[i].gen_mean = gen_mean;
        samples[i].pop_sd   = sd;
        samples[i].sam_mean = mean;
        samples[i].sam_sd   = sumSquareDifs / (double)n;
        samples[i].sam_size = n;
    }
}