#include <stdio.h>
#include <stdlib.h>


void minMax(float tab[], int n, float* max, float* min){
  int i = 0;

  for(i = 0; i < n; i++){
    if(tab[i] < *min)
      min = &tab[i];
    if(tab[i] > *max)
      max = &tab[i];
  }
    
}

int main(int argc, char** argv){
  float tab[] = {0.0, 0.1, 0.9};
  float* max = &tab[0];
  float* min = &tab[0];
  minMax(tab, 3, max, min);
  
  printf("min : %f \n max : %f", *min, *max);

  return 0;
}
