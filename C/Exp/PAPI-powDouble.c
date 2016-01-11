#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "papi.h"

// compilation: gcc -I/usr/local/include -O0 PAPI-powInt.c /usr/local/lib/libpapi.a


#define NB_EVENT 3  // max:3

/* Get actual CPU time in seconds */
float gettime() {
  return((float)PAPI_get_virt_usec()/1000000);
}

#define mult(a,b) (a*b)

int NBR = 50000000;
int MAX = 67108864;
int MIN = 1;
int  *ALEA;


int randomDe(int max){
    int de;
    do {
        de = random();
        
    } while(de >= INT_MAX - (INT_MAX % max));
    
    return de % max;
}

void randomize(int *T,int max, int min, int n) {
    int i;
    for(i=0;i<n;i++){
        T[i] = randomDe(max-min)+min;
    }
}

double binPow(double x,int n){
    double r;
    r = 1;
    while (n > 0) {
        if (n & 1) {
            r = mult(r,x);
        }
        n >>= 1;
        x = mult(x,x);
    }
    return r;
}

long int binPowCounter(long int x,int n){
    long int r;
    r = 1;
    int counter =0 ;
    while (n > 0) {
        counter++;
        if (n & 1) {
            r = mult(r,x);
        }
        n >>= 1;
        x = mult(x,x);
    }
    return counter;
}

long int binPowMult(long int x,int n){
    long int r;
    r = 1;
    int counter =0 ;
    while (n > 0) {
        if (n & 1) {
            counter++;
            r = mult(r,x);
        }
        n >>= 1;
        counter++;
        x = mult(x,x);
    }
    return counter;
}

double guidedPow(double x,int n){
    double r,t;
    r = 1;
    while (n > 0) {
        t = mult(x,x);
        if (n & 3) {
            if (n & 1) {
                r = mult(r,x);
            }
            if (n & 2) {
                r = mult(r,t);
            }
        }
        
        n >>= 2;
        x = mult(t,t);
    }
    return r;
}

long int guidedPowCounter(long int x,int n){
    long int r,t;
    r = 1;
    int counter =0 ;
    while (n > 0) {
        counter++;
        t = mult(x,x);
        if (n & 3) {
            if (n & 1) {
                r = mult(r,x);
            }
            if (n & 2) {
                r = mult(r,t);
            }
        }
        
        n >>= 2;
        x = mult(t,t);
    }
    return counter;
}

long int guidedPowMult(long int x,int n){
    long int r,t;
    r = 1;
    int counter =0 ;
    while (n > 0) {
        counter++;
        t = mult(x,x);
        if (n & 3) {
            if (n & 1) {
                counter++;
                r = mult(r,x);
            }
            if (n & 2) {
                counter++;
                r = mult(r,t);
            }
        }
        
        n >>= 2;
        counter++;
        x = mult(t,t);
    }
    return counter;
}


double unrolledPow(double x,int n){
    double r,t;
    r = 1;
    while (n > 0) {
        t = mult(x,x);
        if (n & 1) {
            r = mult(r,x);
        }
        if (n & 2) {
            r = mult(r,t);
        }
        n >>= 2;
        x = mult(t,t);
    }
    return r;
}

long int unrolledPowCounter(long int x,int n){
    long int r,t;
    r = 1;
    int counter =0 ;
    while (n > 0) {
        counter++;
        t = mult(x,x);
        if (n & 1) {
            r = mult(r,x);
        }
        if (n & 2) {
            r = mult(r,t);
        }
        n >>= 2;
        x = mult(t,t);
    }
    return counter;
}

long int unrolledPowMult(long int x,int n){
    long int r,t;
    r = 1;
    int counter =0 ;
    while (n > 0) {
        counter++;
        t = mult(x,x);
        if (n & 1) {
            counter++;
            r = mult(r,x);
        }
        if (n & 2) {
            counter++;
            r = mult(r,t);
        }
        n >>= 2;

        counter++;
        x = mult(t,t);
    }
    return counter;
}


void test(int nbr){
    struct timeval tim;


     printf( "PAPI Version             : %d.%d.%d.%d\n",
        PAPI_VERSION_MAJOR( PAPI_VERSION ),
        PAPI_VERSION_MINOR( PAPI_VERSION ),
        PAPI_VERSION_REVISION( PAPI_VERSION ),
        PAPI_VERSION_INCREMENT( PAPI_VERSION ) );


    /////////////////////////////////////////////////////////////////////////////
    float t0, t1;
    int events[NB_EVENT] = { PAPI_BR_CN, PAPI_BR_MSP, PAPI_L1_DCM }, ret;
    long_long values[NB_EVENT];
    /////////////////////////////////////////////////////////////////////////////
    if (PAPI_num_counters() < 2) {
     fprintf(stderr, "No hardware counters here, or PAPI not supported.\n");
     exit(1);
    }
    /////////////////////////////////////////////////////////////////////////////

    int i;
    long int nbloops,nbmult;
    double x1;
    
    randomize(ALEA,MAX,MIN,nbr);
    

    /////////////////////////////////////////////////////////////////////////////
    if ((ret = PAPI_start_counters(events, NB_EVENT)) != PAPI_OK) {
     fprintf(stderr, "PAPI failed to start counters: %s\n", PAPI_strerror(ret));
     exit(1);
    }
    /////////////////////////////////////////////////////////////////////////////

    t0 = gettime();

    x1 = 0;
    for(i=0;i<nbr;i++)
        x1 += binPow(2,ALEA[i]);
  
    t1 = gettime();

    /////////////////////////////////////////////////////////////////////////////
    if ((ret = PAPI_stop_counters(values, NB_EVENT)) != PAPI_OK) {
    fprintf(stderr, "PAPI failed to read counters: %s\n", PAPI_strerror(ret));
    exit(1);
    }

    printf("------ binPow -------- %lf\n", x1);
    printf("time = %f sec.\n", t1-t0);
    
    if ((ret = PAPI_start_counters(events, NB_EVENT)) != PAPI_OK) {
     fprintf(stderr, "PAPI failed to start counters: %s\n", PAPI_strerror(ret));
     exit(1);
    }
    /////////////////////////////////////////////////////////////////////////////

    nbloops = 0;
    for(i=0;i<nbr;i++)
        nbloops += binPowCounter(2,ALEA[i]);

    /////////////////////////////////////////////////////////////////////////////
    if ((ret = PAPI_stop_counters(values, NB_EVENT)) != PAPI_OK) {
    fprintf(stderr, "PAPI failed to read counters: %s\n", PAPI_strerror(ret));
    exit(1);
    }
    
    printf("Conditional branch instructions (without loops):  %lld\n", values[0]-nbr-nbloops);
    printf("Conditional branch instructions mispredicted: %lld\n", values[1]);
    printf("Ratio: %f\n",(float)((float)(values[1])/(values[0]-nbr-nbloops)));
    printf("L1 data cache misses is %lld\n", values[2]);
    printf("nbloops %ld\n", nbloops);

    /////////////////////////////////////////////////////////////////////////////

    nbmult = 0;
    for(i=0;i<nbr;i++)
        nbmult+= binPowMult(2,ALEA[i]);

    
    printf("nbmult %ld\n", nbmult);
    /////////////////////////////////////////////////////////////////////////////







    /////////////////////////////////////////////////////////////////////////////
    if ((ret = PAPI_start_counters(events, NB_EVENT)) != PAPI_OK) {
     fprintf(stderr, "PAPI failed to start counters: %s\n", PAPI_strerror(ret));
     exit(1);
    }
    /////////////////////////////////////////////////////////////////////////////

    t0 = gettime();

    x1 = 0;
    for(i=0;i<nbr;i++)
        x1 += unrolledPow(2,ALEA[i]);
  
    t1 = gettime();

    /////////////////////////////////////////////////////////////////////////////
    if ((ret = PAPI_stop_counters(values, NB_EVENT)) != PAPI_OK) {
    fprintf(stderr, "PAPI failed to read counters: %s\n", PAPI_strerror(ret));
    exit(1);
    }

    printf("------ unrolledPow -------- %lf\n", x1);
    printf("time = %f sec.\n", t1-t0);
    
    if ((ret = PAPI_start_counters(events, NB_EVENT)) != PAPI_OK) {
     fprintf(stderr, "PAPI failed to start counters: %s\n", PAPI_strerror(ret));
     exit(1);
    }
    /////////////////////////////////////////////////////////////////////////////


    nbloops = 0;
    for(i=0;i<nbr;i++)
        nbloops += unrolledPowCounter(2,ALEA[i]);

    /////////////////////////////////////////////////////////////////////////////
    if ((ret = PAPI_stop_counters(values, NB_EVENT)) != PAPI_OK) {
    fprintf(stderr, "PAPI failed to read counters: %s\n", PAPI_strerror(ret));
    exit(1);
    }
    
    printf("Conditional branch instructions (without loops):  %lld\n", values[0]-nbr-nbloops);
    printf("Conditional branch instructions mispredicted: %lld\n", values[1]);
    printf("Ratio: %f\n",(float)((float)(values[1])/(values[0]-nbr-nbloops)));
    printf("L1 data cache misses is %lld\n", values[2]);
    printf("nbloops %ld\n", nbloops);

    /////////////////////////////////////////////////////////////////////////////

    nbmult = 0;
    for(i=0;i<nbr;i++)
        nbmult+= unrolledPowMult(2,ALEA[i]);

    
    printf("nbmult %ld\n", nbmult);
    /////////////////////////////////////////////////////////////////////////////










    /////////////////////////////////////////////////////////////////////////////
    if ((ret = PAPI_start_counters(events, NB_EVENT)) != PAPI_OK) {
     fprintf(stderr, "PAPI failed to start counters: %s\n", PAPI_strerror(ret));
     exit(1);
    }
    /////////////////////////////////////////////////////////////////////////////

    t0 = gettime();

    x1 = 0;
    for(i=0;i<nbr;i++)
        x1 += guidedPow(2,ALEA[i]);
  
    t1 = gettime();

    /////////////////////////////////////////////////////////////////////////////
    if ((ret = PAPI_stop_counters(values, NB_EVENT)) != PAPI_OK) {
    fprintf(stderr, "PAPI failed to read counters: %s\n", PAPI_strerror(ret));
    exit(1);
    }

    printf("------ guidedPow -------- %lf\n", x1);
    printf("time = %f sec.\n", t1-t0);
    
    if ((ret = PAPI_start_counters(events, NB_EVENT)) != PAPI_OK) {
     fprintf(stderr, "PAPI failed to start counters: %s\n", PAPI_strerror(ret));
     exit(1);
    }
    /////////////////////////////////////////////////////////////////////////////


    nbloops = 0;
    for(i=0;i<nbr;i++)
        nbloops += guidedPowCounter(2,ALEA[i]);

    /////////////////////////////////////////////////////////////////////////////
    if ((ret = PAPI_stop_counters(values, NB_EVENT)) != PAPI_OK) {
    fprintf(stderr, "PAPI failed to read counters: %s\n", PAPI_strerror(ret));
    exit(1);
    }
    
    printf("Conditional branch instructions (without loops):  %lld\n", values[0]-nbr-nbloops);
    printf("Conditional branch instructions mispredicted: %lld\n", values[1]);
    printf("Ratio: %f\n",(float)((float)(values[1])/(values[0]-nbr-nbloops)));
    printf("L1 data cache misses is %lld\n", values[2]);
    printf("nbloops %ld\n", nbloops);

    /////////////////////////////////////////////////////////////////////////////

    nbmult = 0;
    for(i=0;i<nbr;i++)
        nbmult+= guidedPowMult(2,ALEA[i]);

    
    printf("nbmult %ld\n", nbmult);
    /////////////////////////////////////////////////////////////////////////////
}

void init() {
    ALEA = (int *) calloc (NBR,sizeof(int));
}

int main() {
    int i,n;
    long int x = 2;
    srandom(time(NULL));
    init();
    test(NBR);
}
