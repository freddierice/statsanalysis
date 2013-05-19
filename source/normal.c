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

/* Internal Variables */
const double x[127] =    {0.197946913, 0.425507993, 0.47905519,
    0.523481243, 0.562122587, 0.596702226, 0.628245162, 0.65741804,
    0.684682225, 0.710372064, 0.734738644, 0.757975971, 0.780237477,
    0.801646894, 0.82230566, 0.842298129, 0.86169532, 0.880557681,
    0.898937161, 0.916878794, 0.934421925, 0.951601175, 0.968447205,
    0.98498733, 1.001246022, 1.017245316, 1.033005151, 1.048543647,
    1.063877344, 1.0790214, 1.09398976, 1.108795299, 1.123449949,
    1.137964801, 1.152350205, 1.166615845, 1.18077081, 1.19482366,
    1.208782481, 1.22265493, 1.23644828, 1.250169463, 1.263825099,
    1.277421533, 1.29096486, 1.304460951, 1.317915479, 1.331333942,
    1.344721679, 1.35808389, 1.371425657, 1.384751954, 1.39806767,
    1.411377617, 1.424686547, 1.437999164, 1.45132014, 1.464654121,
    1.478005747, 1.491379659, 1.504780512, 1.518212987, 1.531681803,
    1.545191731, 1.558747602, 1.572354322, 1.586016888, 1.599740396,
    1.613530058, 1.627391218, 1.641329365, 1.655350149, 1.669459403,
    1.683663155, 1.697967656, 1.712379393, 1.726905119, 1.741551876,
    1.756327022, 1.77123826, 1.786293674, 1.801501764, 1.816871482,
    1.832412284, 1.848134169, 1.864047743, 1.880164271, 1.896495749,
    1.913054982, 1.929855664, 1.94691248, 1.96424121, 1.981858861,
    1.999783804, 2.018035937, 2.036636881, 2.055610188, 2.074981602,
    2.09477935, 2.115034493, 2.135781337, 2.157057917, 2.178906582,
    2.201374699, 2.224515503, 2.248389136, 2.273063935, 2.298618029,
    2.32514135, 2.352738196, 2.381530532, 2.411662304, 2.443305174,
    2.47666627, 2.511998876, 2.549617529, 2.589919912, 2.633419615,
    2.680797023, 2.732982035, 2.791296261, 2.857715616, 2.935403561,
    3.029948617, 3.152892252, 3.336429462, 3.88562802};

void initializeNormal(void)
{
    exit(0);
}

double getRandomNormal(double mean, double sd, short ID)
{
    return randNormal(ID)*sd + mean;
}

double randNormal(short ID)
{
    unsigned char r, n;
    r = 0;
    n = 1;
    //getRandomBytes((char *)&r, 1, ID);
    r = ((char *)random())[0];
    n &= r;
    r >>= 1;
    
    if( r == 127 )
        return randNormal(ID);
        //return getRandom()*randNormalSlow()*(-n);
    if( n )
        return -1*getRandom()*x[r];
    else
        return getRandom()*x[r];
}

//http://www.dtic.mil/cgi-bin/GetTRDoc?AD=AD423993&Location=U2&doc=GetTRDoc.pdf
double randNormalSlow(void)
{
    double x1, y1;
    do
    {
        x1 = -log(random()) / x[126];
        y1 = -log(random());
    }while(y1+y1 < x1*x1);
    
    return x[126] + x1;
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
