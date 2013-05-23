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
const double x[127] =    {0.0000448607, 0.313222, 0.396972, 0.456719, 0.504992, 0.546317, 
    0.582908, 0.616034, 0.646498, 0.674845, 0.701461, 0.726636, 0.750587, 
    0.773487, 0.795475, 0.81666, 0.837138, 0.856984, 0.876265, 0.895036, 
    0.913347, 0.93124, 0.948751, 0.965914, 0.982757, 0.999307, 1.01559, 
    1.03162, 1.04742, 1.06301, 1.0784, 1.09361, 1.10865, 1.12354, 
    1.13828, 1.15289, 1.16737, 1.1817471047988755172537263387941, 
    1.1960145045676203946986856701106, 1.2101856027478815913988050494524, 
    1.2242683829698284302917326815823, 1.2382704257933617307815912731284, 
    1.2521989503313251854835125765955, 1.2660608516058362874923888140233, 
    1.2798627342194981848600107446655, 1.2936109428376545093881473507435, 
    1.3073115899067494470580451310771, 1.3209705809749734331925167096954, 
    1.3345936379319579269433767381734, 1.3481863204432476168864099500781, 
    1.3617540458205877146310746676635, 1.3753021075402492773903319841867, 
    1.3888356925971817281927027188318, 1.4023598978623187121221145667581, 
    1.4158797455934495780066119297645, 1.4294001982355272271172652409964, 
    1.4429261726346283756983355864724, 1.4564625537800637785461080118966, 
    1.4700142081811534041135456297453, 1.4835859969791603131557558027154, 
    1.4971827888900677111059928653113, 1.5108094730707066134847853932176, 
    1.5244709719985105921191534582438, 1.5381722544546956439880799044810, 
    1.5519183487007993862955801115452, 1.5657143559402967198841995355014, 
    1.5795654641598237050434510475169, 1.5934769624485197923752150362740, 
    1.6074542558996758245200399215258, 1.6215028812054621453627155108630, 
    1.6356285230643427272731962995106, 1.6498370315306532981093870872423, 
    1.6641344404482863131524385331533, 1.6785269871248548515705269692685, 
    1.6930211334196264592225140959312, 1.7076235884386520750926563996052, 
    1.7223413330539057242856650582187, 1.7371816464907724306542497635652, 
    1.7521521352603731340778561451407, 1.7672607647511327212851308513065, 
    1.7825158938383919349361697096866, 1.7979263129231129387664455168967, 
    1.8135012858727363752546261079848, 1.8292505964102131046407354171333, 
    1.8451845995842621341334300319839, 1.8613142790574107909419281476732, 
    1.8776513110722249605308450111633, 1.8942081361047864498984646130827, 
    1.9109980393937842320061748610146, 1.9280352417505591305820327820670, 
    1.9453350023195110584273239750731, 1.9629137352810279074758184988750, 
    1.9807891428857265667517390892113, 1.9989803676989476006385889993793, 
    2.0175081675433721602132328381123, 2.0363951173896340070513372205843, 
    2.0556658434031844019311511142054, 2.0753472955712285310606104878345, 
    2.0954690668849128155259784563440, 2.1160637690490745890731382927590, 
    2.1371674772831005640567126127985, 2.1588202601702021615527623970895, 
    2.1810668149988088061606754553759, 2.2039572350334041816392991180885, 
    2.2275479432481177529507216064441, 2.2519028381250970788735673913509, 
    2.2770947124513487206218768495673, 2.3032070275871425113496701980750, 
    2.3303361564141464112887060878575, 2.3585942527773508946240679457897, 
    2.3881129711992531190561969613030, 2.4190483602369366456842072113774, 
    2.4515874067330552788506778217424, 2.4859569522150255615747206061789, 
    2.5224361010964533803759338313044, 2.5613739128797293847917218774530, 
    2.6032153502722266000877814258416, 2.6485406188838926331356014257927, 
    2.698127217231625632728037504699, 2.753052629510107585048942305416, 
    2.814874756461709381623052084029, 2.885974166036334326432305265735, 
    2.970273048999110202932635870809, 3.074979445337220889946874866572, 
    3.215874496312785349241354558912, 3.441535095119376470880567296433, 
    7.7751581629126943253};

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
    long temp = random();
    r = ((char *)&temp)[0];
    n &= r;
    r >>= 1;
    
    if( r == 127 )
        if( n ){
            return randNormalSlow()*-1;
        }else{
            return randNormalSlow();
        }
    if( n )
        return -1*getRandom()*x[r];
    else
        return getRandom()*x[r];
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
    
    return x[126] + a*sqrt(-2*log(s)/s);
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
