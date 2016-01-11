#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#include "timer.h"

int NBR = 10000000;
int MAX = 10000000;
int *TAB, *ALEA;

void randomize(int *T,int max, int n) {
  int i;
  for(i=0;i<n;i++){
    T[i] = rand();//(max);
  }
}

void init() {
  ALEA = (int*)calloc(NBR,sizeof(int));
  randomize(ALEA,MAX,NBR);
}

void test(){
  int i,j;
  int min, max;

  init();

  init_timer;


  /////// Optimized minimum and maximum searching ///////
  min = MAX + 1; max = -1;
  first_step_timer;
  for(i=0;i<NBR;i+=2){
    int a1=ALEA[i], a2=ALEA[i+1];
    if (a1 < a2) {
      if (a1 < min) min = a1;
      if (a2 > max) max = a2;
    }
    else {
      if (a2 < min) min = a2;
      if (a1 > max) max = a1;
    }
  }
  second_step_timer;
  print_time("3/2");
  printf("(%d,%d)\n",min,max);


  /////// Naive minimum and maximum searching ///////
  min = MAX + 1; max = -1;

  first_step_timer;
  for(i=0;i<NBR;i++){
    if (ALEA[i] < min) 
      min = ALEA[i];
    if (ALEA[i] > max) 
      max = ALEA[i];
  }

  second_step_timer;
  print_time("naive");
  printf("(%d,%d)\n",min,max);
  
}

int main() {
  int i;
  srand(time(NULL));

  test();
}
