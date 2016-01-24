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

void triRapide(float* t, int size){
  int en_desordre = 1;
  int i,j;

  for (i = 0; (i < size) && en_desordre; ++i)
    {
      en_desordre = 0;
      for (j = 1; j < (size - i); ++j)
	{
	  if (t[j-1] > t[j])
	    {
	      int temp = t[j-1];
	      t[j-1] = t[j];
	      t[j] = temp;
	      en_desordre = 1;
	    }
	}
    }
}

void comparatif(){
  long i;
  long j;
  int k;
  float test;
  struct timespec start, stop;

  //FILE* fichier = fopen("courbeBinarySearch.txt", "w+");
  for(j = 50000; j < 500001; j+=50000){
    printf("%ld \n",j);
    float* tab = (float*)malloc(sizeof(float)*j);
      
    double binarySearchTime = 0;
    double biaisedSearchTime = 0;
    double skewSearchTime = 0;

    for(k = 0; k < 5; k++){
      for(i = 0;i<j;i++) {
	srand(time(NULL)); 
	test = (float)rand()/(float)RAND_MAX;
	tab[i] = test;
      }
      int valueSearching = rand() /(RAND_MAX / (j - 1 + 1) + 1);
      triRapide(tab, j);
      clock_gettime(CLOCK_REALTIME, &start);
      binary_search(tab, valueSearching,j);
      clock_gettime(CLOCK_REALTIME, &stop); 
      binarySearchTime += (double)( stop.tv_nsec - start.tv_nsec );

      clock_gettime(CLOCK_REALTIME, &start);
      biased_binary_search(tab,valueSearching,j);
      clock_gettime(CLOCK_REALTIME, &stop);  
      biaisedSearchTime +=(double)( stop.tv_nsec - start.tv_nsec );

      clock_gettime(CLOCK_REALTIME, &start);
      skew_search(tab,valueSearching,j);
      clock_gettime(CLOCK_REALTIME, &stop);  
      skewSearchTime += (double)( stop.tv_nsec - start.tv_nsec );
    }
    printf("time : binary_search %lf ", binarySearchTime/(5*1000));
    printf("time : biased_binary_search %lf ", biaisedSearchTime/(5*1000));
    printf("time : skew_search %lf \n",skewSearchTime/(5*1000));

  }
  //fclose(fichier);
}

void test(){
  float* tab = (float*)malloc(sizeof(float)*5);
  tab[0] = 3;
  tab[1] = 2;
  tab[2] = 5;
  tab[3] = 4;
  tab[4] = 6;
  int i = 0;
  triRapide(tab, 5);
  for(i = 0; i < 5; i++){
    printf("%lf\n", tab[i]);
  }

}


int main(int argc, char** argv){
  comparatif();
  //test();
  return 0;

}




 

