//
//  data.c
//  Stats Analysis
//
//  Created by Freddie Rice on 3/14/13.
//

#include "data.h"

/* General C Libraries */
#include <stdlib.h>

void initializeSampleInfo( struct sample_info *s )
{
    s = (struct sample_info *)malloc((unsigned long)sizeof(struct sample_info));
}