#include <stdio.h>
#include <stdlib.h>
#include "timer.h"
#include <limits.h>

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
        
        n >>=2;
        x = mult(t,t);
    }
    return r;
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

void test(int nbr){
    int i;
    double x1,x2,x3,x4;

    init_timer;
    
    randomize(ALEA,MAX,MIN,nbr);
    
    x1 = 0;
    first_step_timer;
    for(i=0;i<nbr;i++)
        x1 += binPow(2,ALEA[i]);
    second_step_timer;
    print_time("binPow");
    
    x3 = 0;
    first_step_timer;
    for(i=0;i<nbr;i++)
        x3 += guidedPow(2,ALEA[i]);
    second_step_timer;
    print_time("guidedPow");
    
    x4 = 0;
    first_step_timer;
    for(i=0;i<nbr;i++)
        x4 += unrolledPow(2,ALEA[i]);
    second_step_timer;
    print_time("unrolledPow");


    printf("%f %f %f\n",x1,x3,x4);
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
