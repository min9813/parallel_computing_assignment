#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>

int main() {

    int repeat = 1000;
    struct timeval myTime[repeat]; 
    struct tm *time_st;

    for(int i=0;i<repeat;i++){
        gettimeofday(myTime+i, NULL);
    }
    
    double min_d = 100000.;
    for(int i=1;i<repeat;i++){
        double d = difftime(myTime[i].tv_usec, myTime[i-1].tv_usec);
        if(min_d > d){
            min_d = d;
        }
    }

    double mean_d = difftime(myTime[repeat-1].tv_usec, myTime[0].tv_usec);
    mean_d += difftime(myTime[repeat-1].tv_sec, myTime[0].tv_sec)*1e6;
    mean_d *= 1./repeat;
    printf("mean elapsed time:%06f micros\n", mean_d);
    printf("minimum elapsed time:%06f micros\n", min_d);

}