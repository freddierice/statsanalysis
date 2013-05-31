#include "main.h"
#include <math.h>

/* Math Constants */
#define GAUSS_CONST	   -1.83787706640935 
#define OVER_SQRT_2PI	0.39894228040143
#define OVER_SQRT_2     0.70710678118655
#define E				2.71828182845905

/* Internal Functions */
double GuassianPDF( double x );
double GaussianPDFInverse( double y );
double GuassianInverseCDF( double p );
double GaussianCDF( double x );
double randNormal(short ID);
double randNormalSlow(void);



#define WEDGES 10000
#define LAYERS 256
double **wedges;
double *quantiles;
double *percentStart;
double *percentMultiplier;

void initializeNormal(void)
{
    printf("%s\n","Initializing..");
    
    FILE *wedgeFile, *percentStartFile, *percentMultiplierFile, *quantilesFile;
    wedgeFile = fopen("wedges.bin","rb");
    percentStartFile = fopen("starts.bin", "rb");
    percentMultiplierFile = fopen("multiplier.bin", "rb");
    quantilesFile = fopen("quantiles.bin", "rb");
    
    wedges = (double **)malloc(LAYERS*sizeof(double *));
    percentStart = (double *)malloc(LAYERS*sizeof(double));
    percentMultiplier = (double *)malloc(LAYERS*sizeof(double));
    quantiles = (double *)malloc(LAYERS*sizeof(double));
    
    for( int i = 0; i < WEDGES; ++i )
    {
        wedges[i] = (double *)malloc(WEDGES*sizeof(double));
        fread(wedges[i],sizeof(double),WEDGES,wedgeFile);
    }
    
    fread(percentStart, sizeof(double), LAYERS, percentStartFile);
    fread(percentMultiplier, sizeof(double), LAYERS, percentStartFile);
    fread(quantiles, sizeof(double), LAYERS, quantilesFile);
    
    printf("Done Reading!\n");
}

double getRandomNormal(double mean, double sd, short ID)
{
    return randNormal(ID)*sd + mean;
}

double randNormal(short ID)
{
    long temp = random();       //get random string of bits
    unsigned char u1=0, bit=1;
    double u2 = getRandom();
    u1   = ((char *)&temp)[0]; //get two numbers [0,255]
    bit &= ((char *)&temp)[1]; //get a boolean [0,1]
    
    if( u1 == LAYERS-1 )
    {
        if(bit ){
            return randNormalSlow()*-1;
        }else{
            return randNormalSlow();
        }
    }
    
    if( u2 < percentStart[u1] )
    {
        if( bit )
            return -1*wedges[u1][(int)((u2-quantiles[u1])*percentMultiplier[u1])]*u2;
        else
            return wedges[u1][(int)((u2-quantiles[u1])*percentMultiplier[u1])]*u2;
    }else{
        if( bit )
            return -1*quantiles[u1]*u2;
        else
            return quantiles[u1]*u2;
    }
}

//marsaglia polar method for the tail.
double randNormalSlow(void)
{
    double a=0.0, b=0.0, s=0.0;
    do{
        a = getRandom()*2 - 1;
        b = getRandom()*2 - 1;
        s = a*a + b*b;
    }while(s > 1);
    
    return quantiles[LAYERS-1] + a*sqrt(-2*log(s)/s);
}

double GaussianCDF( double x )
{
    return 0.5*erfc(x*-1*OVER_SQRT_2);
}

double GuassianInverseCDF( double p )
{
    return 0.0;
}

double GuassianPDF( double x )
{
	return OVER_SQRT_2PI * powf((float)E,(float)(-1/2*x*x));
}

double GaussianPDFInverse( double y )
{   
	return sqrt(log(y)*-2 + GAUSS_CONST);
}
