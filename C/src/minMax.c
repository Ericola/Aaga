#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

#include "timer.h"
#define BILLION  1000000000L



clock_t debut, fin;
double tps_ecoule;

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

void testNaif() {
  float tab[] = {0.0, 0.1, 0.9};
  int n = 3;
  float max = tab[0];
  float min = tab[0];
  debut = clock();
  naiveminMax(tab, n, &max, &min);
  fin = clock();
  printf("min : %f \n max : %f \n Temps ecoule : %f \n", min, max, (double)(fin - debut) / CLOCKS_PER_SEC);
}

void testOpti() {
  float tab[] = {0.0, 0.1, 0.9};
  int n = 3; 
  float max = tab[n-1];
  float min = tab[n-1];
  debut = clock();
  optiMinMax(tab,n,&max,&min);
  fin = clock();
  printf("min : %f \n max : %f \n Temps ecoule : %f \n", min, max, (double)(fin - debut) / CLOCKS_PER_SEC);
}


void comparatif() {
  long i;
  long j;
  float max;
  float min;

  struct timespec start, stop;

  init_timer;
  FILE* fichier = fopen("courbe.txt","w+");
  for(j = 1;j<1000000;j+=50000) {
    printf("%ld \n",j);
    float tab[j];
    for(i = 0;i<j;i++) {
      srand(time(NULL)); 
      tab[i] = (float)rand()/(float)RAND_MAX;
    }
    max = tab[0];
    min = tab[0];

    /* if( clock_gettime( CLOCK_REALTIME, &start) == -1 ) {
      perror( "clock gettime" );
      exit( EXIT_FAILURE );
      }*/
    first_step_timer;
    naiveminMax(tab,j,&max,&min);
    second_step_timer;
    /*if( clock_gettime( CLOCK_REALTIME, &stop) == -1 ) {
      perror( "clock gettime" );
      exit( EXIT_FAILURE );
      }
 
    double accum1 =( stop.tv_nsec - start.tv_nsec );
    */
    double accum1 = tim1;
    
    max = tab[j-1];
    min = tab[j-1];

    /*if( clock_gettime( CLOCK_REALTIME, &start) == -1 ) {
      perror( "clock gettime" );
      exit( EXIT_FAILURE );
      }*/
    first_step_timer;
    optiMinMax(tab,j,&max,&min);
    second_step_timer;
    /*if( clock_gettime( CLOCK_REALTIME, &stop) == -1 ) {
      perror( "clock gettime" );
      exit( EXIT_FAILURE );
      }
      
      double accum2 =  ( stop.tv_nsec - start.tv_nsec );*/
    double accum2 = tim1;
    fprintf(fichier,"%ld %f %f \n",j,accum1,accum2);
  }
  fclose(fichier);
}

int main(int argc, char** argv){
  comparatif();
  return 0;
}
