//
//  data.h
//  Stats Analysis
//
//  Created by Freddie Rice on 3/14/13.
//

#ifndef __data_h__
#define __data_h__

/* Data */
struct sample_info {
    double          pop_mean;    //population mean
    double          pop_sd;      //population standard deviation
    double          sam_mean;    //sample mean
    unsigned long   sam_size;    //sample size
};

/* Initializers */
extern void initializeSampleInfo( struct sample_info *s );

#endif /* __data_h__ */
