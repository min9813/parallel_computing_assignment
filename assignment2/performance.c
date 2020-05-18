#pragma GCC target ("avx")
#include <stdlib.h>
#include <stdio.h>
#include <x86intrin.h>
#include <omp.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>

double add(int a, int b);
// double mul(int a, int b);



int main(int argc, char *argv[]){
    int thread_num = atoi(argv[1]);

    float a1 = 0.1, a2=0.2, a3 = 0.3, a4 = 0.4, a5 = 0.1, a6=0.5, a7=0.1, a8=1.1, a9=-0.3, a10=0.1;
    float b1 = -1.1, b2=-1.2, b3 = 1.3, b4 = -1.54, b5 = 10.3, b6=1.1, b7 = 1.11, b8 = 2.31, b9 = 5.3, b10 = -0.4;

    int N = 10000000;
    double st, en;

    if (thread_num == 0){
        thread_num = 1;
    }

    if (thread_num > 1){
        printf("start parallel computing, th=%d\n", thread_num);
        N = N * thread_num;
        omp_set_num_threads(thread_num);
        st = omp_get_wtime();
        #pragma omp parallel
        {
            int thread_id = omp_get_thread_num();
            int num = N / thread_num;
            int thread_part = num * thread_id;
            add(thread_part, thread_part+num);
            // mul(0, num);
        }

        en = omp_get_wtime();
        N = N / thread_num;
    }else{
        printf("start single computing, th=%d\n", thread_num);
        struct timeval myTime[3]; 
        struct tm *time_st;

        gettimeofday(myTime, NULL);
        gettimeofday(myTime+1, NULL);
        for(int i=0;i<thread_num*N;i++){
            // for(int j=0;j<N;j++){
            a1 += b1;
            a2 += b2;
            a3 += b3;
            a4 += b4;
            a5 += b5;
            b1 = b1 * a1;
            b2 = b2 * a2;
            b3 = b3 * a3;
            b4 = b4 * a4;
            b5 = b5 * a5;
            a6 *= b6;
            a7 *= b7;
            a8 *= b8;
            a9 *= b9;
            a10 *= b10;
            b6 = b6 + a6;
            b7 = b7 + a7;
            b8 = b8 + a8;
            b9 = b9 + a9;
            b10 = b10 + a10;
        }
        double ans = a1 + a2 + a3 + a4 + a5 + a6 + a7 + a8 + a9 + a10;
        ans += b1 + b2 + b3 + b4 + b5 + b6 + b7 + b8 + b9 + b10 ;
        gettimeofday(myTime+2, NULL);
        double st_s = difftime(myTime[1].tv_sec, myTime[0].tv_sec);
        double st_m = difftime(myTime[1].tv_usec, myTime[0].tv_usec) / 1000000;
        st = st_s + st_m;
        double en_s = difftime(myTime[2].tv_sec, myTime[0].tv_sec);
        double en_m = difftime(myTime[2].tv_usec, myTime[0].tv_usec)/1000000;
        en = en_s + en_m;
        printf("st = %lf, en=%lf\n", st, en);
        printf("ans = %lf\n", ans);
    }

    
    double gflops = thread_num * (N / 1000000 * 20. + 9.) *0.001;
    printf("thread_num=%d, elapsed time:%lf[ms], gflops=%lf. Gflops/s=%lf\n", thread_num, (en-st)*1000.0, gflops, gflops/((en-st)));
}

double add(int a, int b){
    float a1 = 0.1, a2=0.2, a3 = 0.3, a4 = 0.4, a5 = 0.1, a6=0.5, a7=0.1, a8=1.1, a9=-0.3, a10=0.1;
    float b1 = -1.1, b2=-1.2, b3 = 1.3, b4 = -1.54, b5 = 10.3, b6=1.1, b7 = 1.11, b8 = 2.31, b9 = 5.3, b10 = -0.4;
    for(int i=a;i<b;i++){
        a1 += b1;
        a2 += b2;
        a3 += b3;
        a4 += b4;
        a5 += b5;
        b1 = b1 * a1;
        b2 = b2 * a2;
        b3 = b3 * a3;
        b4 = b4 * a4;
        b5 = b5 * a5;
        a6 *= b6;
        a7 *= b7;
        a8 *= b8;
        a9 *= b9;
        a10 *= b10;
        b6 = b6 + a6;
        b7 = b7 + a7;
        b8 = b8 + a8;
        b9 = b9 + a9;
        b10 = b10 + a10;
    }

    double ans = a1 + a2 + a3 + a4 + a5 + a6 + a7 + a8 + a9 + a10;
    ans += b1 + b2 + b3 + b4 + b5 + b6 + b7 + b8 + b9 + b10 ;
    return ans;
}