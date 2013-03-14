//
//  printing.h
//  Stats Analysis
//
//  Created by Freddie Rice on 3/14/13.
//

#ifndef __printing_h__
#define __printing_h__

#define PRINT_ERR(x)        printf("%s\n", x);
#define PRINT_USAGE(name)   printf("Usage: %s <sample size> <mean> <std> \n\n", name)
#define PRINT_HELP()        printf("%s\n","<sample size>   size of the samples"); \
printf("%s\n","<std>    standard deviation."); \
printf("\n");

#endif /* __printing_h__ */
