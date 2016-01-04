#include <stdio.h>
#include <stdlib.h>
#include <time.h>

clock_t debut, fin;
double tps_ecoule;

void minMax(float tab[], int n, float* max, float* min){
  int i = 0;
 
  for(i = 0; i < n; i++){
    if(tab[i] < *min)
      *min = tab[i];
    if(tab[i] > *max)
      *max = tab[i];
  }
    
}

int main(int argc, char** argv){
  float tab[] = {0.0, 0.1, 0.9};
  float max = 0.0;
  float min = 0.0;
  debut = clock();
  minMax(tab, 3, &max, &min);
  fin = clock();
  printf("min : %f \n max : %f \n Temps ecoule : %f \n", min, max, (double)(fin - debut) / CLOCKS_PER_SEC);

  return 0;
}
