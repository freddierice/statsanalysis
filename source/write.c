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
#ifdef _WIN32
    fopen_s(&outfile, file, "a+");
#elif defined(__linux__) || defined(__APPLE__)
	outfile = fopen(file, "a+");
#endif

    fprintf(outfile, "id,popMean,popSD,samMean,samSD,n\n");
#ifdef _WIN32
	long i;
#elif defined(__linux__) || defined(__APPLE__)
	unsigned long i;
#endif
    for (i=1; i <= samples; ++i) 
    {
        sample_info *t = &info[i];
        fprintf(outfile, "%lu,%f,%f,%f,%f,%lu\n", i, t->pop_mean, t->pop_sd, t->sam_mean, t->sam_sd, t->sam_size);
    }
    fclose(outfile);
}