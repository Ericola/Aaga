#include <stdio.h>
#include <stdlib.h>


void minMax(int tab[], int n, int* min, int* max){
  int i;
  for(i = 0; i < n; i++){
    if(tab[i] < &min)
      &min = tab[i];
    if(tab[i] > &max)
      &max = tab[i];
  }

}
