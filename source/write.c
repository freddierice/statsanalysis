//
//  write.c
//  Stats Analysis
//
//  Created by Freddie Rice on 3/18/13.
//

#include "main.h"

void writeSamples(sample_info *info, unsigned long samples, const char *file)
{
    FILE *outfile;
	unsigned long i;

#ifdef _WIN32
    fopen_s(&outfile, file, "a+");
#elif defined(__linux__) || defined(__APPLE__)
	outfile = fopen(file, "a+");
#endif

    fprintf(outfile, "id,popMean,popSD,samMean,samSD,n\n");
    printf("%s\n", "About to go to loop");
    for (i=1; i <= samples; ++i) 
        fprintf(outfile, "%lu,%f,%f,%f,%f,%lu\n", i, info[i].pop_mean, info[i].pop_sd, info[i].sam_mean, info[i].sam_sd, info[i].sam_size);
    fclose(outfile);
}

void writeResults(test_results *r, const char *file)
{
    FILE *outfile;
    
#ifdef _WIN32
    fopen_s(&outfile, file, "a+");
#elif defined(__linux__) || defined(__APPLE__)
	outfile = fopen(file, "a+");
#endif
    
    fprintf(outfile, "total,zcorr,zerr1,zerr2,tcorr,terr1,terr2,n\n");
    fprintf(outfile, "%lu,%lu,%lu,%lu,%lu,%lu,%lu\n", r->total, r->z_corr, r->z_err1, r->z_err2, r->t_corr, r->t_err1, r->t_err2);
    fclose(outfile);
}

