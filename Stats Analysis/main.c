//
//  main.c
//  Stats Analysis
//
//  Created by User on 3/14/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include "main.h"

int main (int argc, const char * argv[])
{
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
    
    
    
    return 0;
}

