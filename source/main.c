//
//  main.c
//  Stats Analysis
//
//  Created by Freddie Rice on 3/14/13.
//

#include "main.h"

int main (int argc, const char * argv[])
{
    /*
    if(argc == 2 && (!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help")))
    {
        PRINT_USAGE(argv[0]);
        PRINT_HELP();
        return 0;
    }
    
    if(argc != 4)
    {
        PRINT_ERR("Wrong number of arguments.");
        PRINT_USAGE(argv[0]);
        return -1;
    }
     */
    
    initializeNormal();
    
    unsigned long repititions = 10;
    double mu = 0;
    double sd = 1;
    unsigned long n = 50;
	sample_info *samples;

    char *filename = (char *)malloc(sizeof("outfile.csv"));
#ifdef _WIN32
    strcpy_s(filename, sizeof("outfile.csv"),"outfile.csv");
#elif defined(__linux__) || defined(__APPLE__)
	strcpy(filename, "outfile.csv");
#endif
    
    initializeRandom();
    createRandomSamples(samples, repititions, mu, sd, n);
    write(samples, n, filename);
    
    return 0;
}