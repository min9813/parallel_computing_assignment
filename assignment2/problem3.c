// #pragma GCC target ("sse4")
#include <stdlib.h>
#include <stdio.h>
// #include <x86intrin.h>
#include <omp.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>

double b_vec[100000000];
double c_vec[100000000];

double a_vec[100000000];

double copy(int vec_size){
    // printf("copy ok1 \n");

    // printf("copy ok2 \n");

    for(int i=0;i<vec_size;i++){
        a_vec[i] = ((double)i) * 0.001;
    }
    // printf("copy ok \n");
    // copy
    struct timeval myTime[3]; 
    struct tm *time_st;

    gettimeofday(myTime, NULL);
    gettimeofday(myTime+1, NULL);
    for(int i=0;i<vec_size;i++){
        b_vec[i] = a_vec[i];
    }

    gettimeofday(myTime+2, NULL);
    double st_s = difftime(myTime[1].tv_sec, myTime[0].tv_sec) * 1000;
    double st_m = difftime(myTime[1].tv_usec, myTime[0].tv_usec) / 1000;
    double st = st_s + st_m;
    double en_s = difftime(myTime[2].tv_sec, myTime[0].tv_sec) * 1000;
    double en_m = difftime(myTime[2].tv_usec, myTime[0].tv_usec) / 1000;
    double en = en_s + en_m;

    return en - st;
}

double inner_product(int vec_size){
    // double a_vec[vec_size];
    // double b_vec[vec_size];

    for(int i=0;i<vec_size;i++){
        a_vec[i] = ((double)i) * 0.001;
        b_vec[i] = ((double)i) * 0.002 * (i%2*2-1);
    }

    // copy
    struct timeval myTime[3]; 
    struct tm *time_st;

    double ans = 0;
    gettimeofday(myTime, NULL);
    gettimeofday(myTime+1, NULL);
    for(int i=0;i<vec_size;i++){
        ans += b_vec[i] * a_vec[i];
    }

    gettimeofday(myTime+2, NULL);
    double st_s = difftime(myTime[1].tv_sec, myTime[0].tv_sec) * 1000;
    double st_m = difftime(myTime[1].tv_usec, myTime[0].tv_usec) / 1000;
    double st = st_s + st_m;
    double en_s = difftime(myTime[2].tv_sec, myTime[0].tv_sec) * 1000;
    double en_m = difftime(myTime[2].tv_usec, myTime[0].tv_usec) / 1000;
    double en = en_s + en_m;

    return en - st;
}

double sum_vec(int vec_size){
    // double a_vec[vec_size];
    // double b_vec[vec_size];
    // double c_vec[vec_size];

    for(int i=0;i<vec_size;i++){
        a_vec[i] = ((double)i) * 0.001;
        b_vec[i] = ((double)i) * 0.002;
    }

    // copy
    struct timeval myTime[3]; 
    struct tm *time_st;

    double ans = 0;
    gettimeofday(myTime, NULL);
    gettimeofday(myTime+1, NULL);
    for(int i=0;i<vec_size;i++){
        c_vec[i] = b_vec[i] + a_vec[i];
    }
    gettimeofday(myTime+2, NULL);

    double st_s = difftime(myTime[1].tv_sec, myTime[0].tv_sec) * 1000;
    double st_m = difftime(myTime[1].tv_usec, myTime[0].tv_usec) / 1000;
    double st = st_s + st_m;
    double en_s = difftime(myTime[2].tv_sec, myTime[0].tv_sec) * 1000;
    double en_m = difftime(myTime[2].tv_usec, myTime[0].tv_usec) / 1000;
    double en = en_s + en_m;

    return en - st;
}

int main(int argc, char *argv[]){
    int thread_num = atoi(argv[1]);

    int vec_size = atoi(argv[2]);
    printf("vec size=%d\n", vec_size);
    double times[3];

    // printf("ok0\n");

    times[0] = copy(vec_size);
    // printf("ok1\n");
    times[1] = inner_product(vec_size);
    // printf("ok2\n");
    times[2] = sum_vec(vec_size);
    // printf("ok3\n");
    
    for(int i=0;i<3;i++){
        printf("vec size:%d, task%d = %lf\n", vec_size, i, times[i]);
    }

}