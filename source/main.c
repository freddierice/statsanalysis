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
    
    unsigned long repititions = 10;
    double mu = 0;
    double sd = 1;
    unsigned long n = 50;
    char *filename = (char *)malloc(sizeof("outfile.csv"));
    strcpy(filename, "outfile.csv");
    
    initializeRandom();
    sample_info *samples;
    
    createRandomSamples(samples, repititions, mu, sd, n);
    
    return 0;
}