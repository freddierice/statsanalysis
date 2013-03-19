//
//  write.c
//  Stats Analysis
//
//  Created by Freddie Rice on 3/18/13.
//

#include "main.h"

void write(sample_info *info, unsigned long samples, const char *file)
{
    FILE *outfile;
    outfile = fopen(file, "a+");
    fprintf(outfile, "id,popMean,popSD,samMean,samSD,n\n");
    for (unsigned long i = 1; i <= samples; ++i) 
    {
        sample_info *t = &info[i];
        fprintf(outfile, "%lu,%f,%f,%f,%f,%lu\n", i, t->pop_mean, t->pop_sd, t->sam_mean, t->sam_sd, t->sam_size);
    }
    fclose(outfile);
}