//
//  data.c
//  Stats Analysis
//
//  Created by Freddie Rice on 3/14/13.
//

#include "main.h"

void createRandomSamples( sample_info *samples, thread_data *data )
{
	unsigned long i;
	unsigned long j;
    
    short ID        = data->ID;
    double mu       = data->mu;
    //double meanVary = data->meanVary;
    double sd       = data->sd;
    unsigned long n = data->n;

    for (i = 0; i < data->reps; ++i) 
    {
        double* restrict sam_data = (double *)malloc(n*sizeof(double));
        double mean = 0;
		double sumSquareDifs;

        //get half from the actual mean, and half not.
        double gen_mean = mu;
        if( i % 2 )
            gen_mean = 100;
        for( j = 0; j < n; ++j )
        {
            sam_data[j] = getRandomNormal(gen_mean, sd, ID);
            mean += sam_data[j];
        }
        
        mean /= (double)n;
        
        sumSquareDifs = 0;
        for( j = 0; j < n; ++j )
            sumSquareDifs += pow(mean-sam_data[j],2);
        
        samples[i].pop_mean = mu;
        samples[i].gen_mean = gen_mean;
        samples[i].pop_sd   = sd;
        samples[i].sam_mean = mean;
        samples[i].sam_sd   = sqrt(sumSquareDifs / (double)n);
        samples[i].sam_size = n;
        
        free(sam_data);
    }
}