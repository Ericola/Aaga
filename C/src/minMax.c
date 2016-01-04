#include <stdio.h>
#include <stdlib.h>

void naiveminMax(float tab[], int n, float* max, float* min){
  int i = 0;
 
  for(i = 0; i < n; i++){
    if(tab[i] < *min)
      *min = tab[i];
    if(tab[i] > *max)
      *max = tab[i];
  }  
}

void optiMinMax(float tab[], int n, float* max, float* min) {
  int i;
  for(i=0;i<n-1;i+=2){
    if(tab[i] < tab[i+1]){
      if(tab[i] < *min){
	*min = tab[i];
      }
      if(tab[i+1]> *max) {
	*max = tab[i+1];
      }	
    }
    else {
      if(tab[i+1] < *min) {
	*min = tab[i+1];
      }
      if(tab[i] > *max) {
	*max = tab[i];
      }
    }
  }

} 
  
int main(int argc, char** argv){
  float tab[] = {0.0, 0.1, 0.9};
  int n = 3;
  /*float max = tab[0];
  float min = tab[0];
  naiveminMax(tab, n, &max, &min);*/
  float max = tab[n-1];
  float min = tab[n-1];
  optiMinMax(tab,n,&max,&min);
  printf("min : %f \n max : %f \n", min, max);

  return 0;
}
