
FNAME = none
OPENMP_FLAG = -fopenmp
LIB_OMP_FLAG = -lomp
XPREPROCESSOR = -Xpreprocessor

build_performance:  
	gcc -o main ${XPREPROCESSOR} ${OPENMP_FLAG} ${LIB_OMP_FLAG} performance.c

build_performance_avx:  
	gcc -o main ${XPREPROCESSOR} ${OPENMP_FLAG} ${LIB_OMP_FLAG} performance_avx.c

build_avx:
	gcc -o main -mavx avx_ex.c

build_problem3:
	gcc -o main problem3.c

run: main
	./main