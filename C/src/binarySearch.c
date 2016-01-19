#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

#define BILLION  1000000000L

int binary_search (float T[], float x, int n){
  int d = 0, f = n, m = 0;

  while (d < f){
    m = (d + f)/2;

    if(T[m] < x)
      d = m+1;
    else
      f = m;
  }

  return f;
}

int binary_search2 (float T[], float x, int n){
  int d = 0, f = n, m = 0;

  while (d < f){
    m = (d + f)/2;

    if(T[m] == x)
      return m;

    if(T[m] < x)
      d = m+1;
    else
      f = m;
  }

  return -1;
}

int biased_binary_search(float T[], float x, int n){
  int d = 0, f = n, m = 0;
  
  while (d < f){
    m = (3*d + f)/4;

    if(T[m] < x)
      d = m+1;
    else
      f = m;
  }

  return f;
  
}

int skew_search(float T[], float x, int n){
  int d = 0, f = n, m1 = 0, m2 = 0;

  while(d < f){
    m1 = (3*d + f)/4;
    if(T[m1] > x)
      f = m1;
    else{
      m2 = (d + f) / 2;
      if(T[m2] > x){
	f = m2;
	d = m1 + 1;
      }
      else
	d = m2 + 1;
    }
  }


  return f;
}

void comparatif(){
  long i;
  long j;
  int k;
  float test;
  struct timespec start, stop;

  //FILE* fichier = fopen("courbeBinarySearch.txt", "w+");
  for(j = 1; j < 500001; j+=50000){
    printf("%ld \n",j);
    float tab[j];
      
    long binarySearchTime = 0;
    long biaisedSearchTime = 0;
    long skewSearchTime = 0;

    for(k = 0; k < 100; k++){
      for(i = 0;i<j;i++) {
	srand(time(NULL)); 
	do{
	  test = (float)rand()/(float)RAND_MAX;
	}while(binary_search2(tab, test, i) != -1);
	tab[i] = test;
      }
      int valueSearching = rand() /(RAND_MAX / (j - 1 + 1) + 1);

      clock_gettime(CLOCK_REALTIME, &start);
      binary_search(tab, valueSearching,j);
      clock_gettime(CLOCK_REALTIME, &stop); 
      binarySearchTime +=  stop.tv_nsec - start.tv_nsec;

      clock_gettime(CLOCK_REALTIME, &start);
      biased_binary_search(tab,valueSearching,j);
      clock_gettime(CLOCK_REALTIME, &stop);  
      biaisedSearchTime += stop.tv_nsec - start.tv_nsec;

      clock_gettime(CLOCK_REALTIME, &start);
      skew_search(tab,valueSearching,j);
      clock_gettime(CLOCK_REALTIME, &stop);  
      skewSearchTime +=  stop.tv_nsec - start.tv_nsec;
    }
    printf("time : binary_search %lu ", binarySearchTime/100);
    printf("time : biased_binary_search %lu ", biaisedSearchTime/100);
    printf("time : skew_search %lu \n",skewSearchTime/100);

  }
  //fclose(fichier);
}


int main(int argc, char** argv){
  comparatif();
  return 0;

}




 

