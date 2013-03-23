#include "main.h"

/* Math Constants */
#define GAUSS_CONST	   -1.83787706640935 
#define OVER_SQRT_2PI	0.39894228040143
#define E				2.71828182845905

/* Internal Functions */
double GaussianPDF( double x );
double GaussianPDFInverse( double y );

/* Internal Variables */
#define	BLOCKS	10	 //number of trapazoids
#define A		0.01 //area of each trapazoid
#define X_START	2147483647	 //start to the first trapazoid
double *x, *y;

void initializeNormal(void)
{
	x = (double *)malloc(sizeof(double)*BLOCKS);
	y = (double *)malloc(sizeof(double)*BLOCKS);

	x[0] = X_START;
	y[0] = 0;
}

double randNormal(void)
{

	return 0.0;
}

double GuassianPDF( double x )
{
	return OVER_SQRT_2PI * powf(E,-1/2*x*x);
}

double GaussianPDFInverse( double y )
{   
	return sqrt(log(y)*-2 + GAUSS_CONST);
}