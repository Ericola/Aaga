#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include "constants.h"
#include "timer.h"


double *TAB;
double *ALEA;

double rand01(){
  return ((double)rand())/RAND_MAX;
}

int compare_doubles (const void *a, const void *b){
  const double *da = (const double *) a;
  const double *db = (const double *) b;

  return (*da > *db) - (*da < *db);
}

int binary(double *T,double xb2,int n){
  unsigned int d,f,m;
  d = 0;
  f = n;
 
  while (d < f){
    m = (d+f) / 2;
    if (T[m] < xb2)
      d = m+1;
    else
      f = m;
  }
  return f;
}

int binary_biased(double *T,double xb3,int n){
  unsigned int d,f,m;
  d = 0;
  f = n;
 
  while (d < f){
    m = (3*d+f)/4;
    if (T[m] < xb3)
      d = m+1;
    else
      f = m;
  }
  return f;
}

int skew(double *T,double xs2,int n){
  unsigned int d,f,m1,m2;
  d = 0;
  f = n;

  while (d < f){
    m1 = (3*d+f)/4;
    if (T[m1] > xs2)
      f = m1;
    else {
      m2 = (d+f)/2;
      if (T[m2] > xs2){
         d = m1+1;
         f = m2;
      }
      else
         d = m2+1;
    }
  }
  return f;
}

void print_tab(double *t,int n, char* str){
  int i;
  printf("%s [ ", str);
  for (i = 0; i < n; ++i){
    printf("%.3f ", t[i]);
  }
  printf("]\n");
}

void check_algos(int size, int nb){
  int i;
  double r;
  TAB = (double*)calloc(size,sizeof(double));
  
  for(i=0;i<size;i++)
    TAB[i] = rand01();
  qsort(TAB, size, sizeof(double), compare_doubles);

  print_tab(TAB, size, "\n\n\nTAB");

  for (i = 0; i <= nb; ++i){
    //r=rand01(); 
    r=(TAB[i]+TAB[i-1])/2;
    if (i==0)
      r=-1;
    if (i==nb)
      r=TAB[size-1]+1;
    printf("%.3f : binary - %d\t",r,binary(TAB,r,size));
    printf("binary_biased - %d\t",binary_biased(TAB,r,size));
    printf("skew - %d\n",skew(TAB,r,size));
  }
  free(TAB);
}


/////////////////////////////////////////////////
/////////////////////////////////////////////////
int test(int nbr, int size){
  int i;
  double a=0,b=0,c=0,elem;
  double toto;

  init_timer;

  ALEA = (double*)calloc(nbr,sizeof(double));

  for(i=0;i<nbr;i++)
    ALEA[i] = rand01();


  TAB = (double*)calloc(size,sizeof(double));
  
  for(i=0;i<size;i++)
    TAB[i] = rand01();
  qsort(TAB, size, sizeof(double), compare_doubles);

  
  first_step_timer;
  for(i=0;i<nbr;i++){
    a+=binary(TAB,ALEA[i],size);
  }
  second_step_timer;
  toto=tim1;
  print_time("binary time");



  first_step_timer;
  for(i=0;i<nbr;i++){
    b+=binary_biased(TAB,ALEA[i],size);
  }
  second_step_timer;
  print_time_notln("biased binary time");
  printf("speed-up: %lf percents\n", (toto/tim1-1)*100);



  first_step_timer;
  for(i=0;i<nbr;i++){
    c+=skew(TAB,ALEA[i],size);
  }
  second_step_timer;
  print_time_notln("skew time");
  printf("speed-up: %lf percents\n", (toto/tim1-1)*100);



  free(TAB);
  free(ALEA);
  return a+b+c;
}
/////////////////////////////////////////////////
/////////////////////////////////////////////////

int main(int argc, char *argv[]){
  int i;
  srand(time(NULL));
  
  //check_algos(10,10);

  if (argc==2){
    printf("size=%d\n", atoi(argv[1]));
    test(nbr_iterations,atoi(argv[1]));
  }
  else{
    printf("size=%d\n", aray_size);
    test(nbr_iterations,aray_size);
  }
}


