//
//  printing.h
//  Stats Analysis
//
//  Created by User on 3/14/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#ifndef __printing_h__
#define __printing_h__

#define PRINT_ERR(x)        printf("%s\n", x);
#define PRINT_USAGE(name)   printf("Usage: %s <sample size> <mean> <std> \n\n", name)
#define PRINT_HELP()        printf("%s\n","<sample size>   size of the samples"); \
printf("%s\n","<std>    standard deviation."); \
printf("\n");

#endif /* __printing_h__ */
