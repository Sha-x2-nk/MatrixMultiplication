// matrix multiplication kernels
#include "kernelsCPU.h"

// for time benching
#include<chrono>

#include<iostream>
#include<string>

// for effecient error checking
#define A_VAL 2.0f
#define B_VAL 3.0f

using namespace std;

template< typename T, int MAT_SIZE>
inline void initMat(T* A, T val) {
	for (int i = 0; i < MAT_SIZE * MAT_SIZE; ++i)
		A[i] = val;
}

template< typename T, int MAT_SIZE>
inline bool checkC(T* C) {
	const T C_VAL = A_VAL * B_VAL * MAT_SIZE;
	
	for (int i = 0; i < MAT_SIZE * MAT_SIZE; ++i)
		if (C[i] != C_VAL) return false;

	return true;
}

template<typename T, int MAT_SIZE>
void benchTimes(T *A, T *B, T *C, int idx, int iters){
	std::chrono::high_resolution_clock::time_point t0, t1;
	std::chrono::duration< double > fs;
	std::chrono::nanoseconds d; 
	std::chrono::duration< double > totfs= static_cast<std::chrono::duration< double >>(0);
	for(int i= 0; i< iters; ++i){
		switch(idx){
			case 1: 
				t0 = std::chrono::high_resolution_clock::now(); 
				matMul1<float, MAT_SIZE>(A, B, C);               
				t1 = std::chrono::high_resolution_clock::now(); 
				break;
			case 2: 
				t0 = std::chrono::high_resolution_clock::now(); 
				matMul2<float, MAT_SIZE>(A, B, C);               
				t1 = std::chrono::high_resolution_clock::now(); 
				break;
			case 4: 
				t0 = std::chrono::high_resolution_clock::now(); 
				matMul4<float, MAT_SIZE>(A, B, C);               
				t1 = std::chrono::high_resolution_clock::now(); 
				break;
			case 5: 
				t0 = std::chrono::high_resolution_clock::now(); 
				matMul5<float, MAT_SIZE, 64>(A, B, C);           
				t1 = std::chrono::high_resolution_clock::now(); 
				break; // 64 best
			case 6: 
				t0 = std::chrono::high_resolution_clock::now(); 
				matMul6<float, MAT_SIZE, 64>(A, B, C, MAT_SIZE); 
				t1 = std::chrono::high_resolution_clock::now(); 
				break; // 64 best
			case 8: 
				t0 = std::chrono::high_resolution_clock::now(); 
				matMul8<float, MAT_SIZE, 64>(A, B, C, MAT_SIZE); 
				t1 = std::chrono::high_resolution_clock::now(); 
				break; // 64 best
		}
		fs = t1 - t0;
		totfs+= fs;
		// result checking
		if( checkC<float, MAT_SIZE>(C)== false ){ printf("\nINCORRECT RESULT."); return; }
		initMat<float, MAT_SIZE>(C, 0); // reset C
	}
	printf("\nRESULTS CORRECT. ");
	totfs/= iters;
	d = std::chrono::duration_cast<std::chrono::nanoseconds>(totfs);
	std::cout << (d.count())/1000000000.0 << "s";
}

int main(int argc, char *args[])
{
	if(argc == 1){
		printf("\nUSAGE: program k, where k is the kernel index to be benched");
	}
	int bench_idx= std::stoi(args[1]);
	
	const int MAT_SIZE = 4096; 

	printf("\nINITIALISING ARRAYS.. ");
	auto t0 = std::chrono::high_resolution_clock::now();
	float* A = (float*)malloc(MAT_SIZE * MAT_SIZE * sizeof(float)); initMat<float, MAT_SIZE>(A, A_VAL);
	float* B = (float*)malloc(MAT_SIZE * MAT_SIZE * sizeof(float)); initMat<float, MAT_SIZE>(B, B_VAL);
	float* C = (float*)malloc(MAT_SIZE * MAT_SIZE * sizeof(float)); initMat<float, MAT_SIZE>(C, 0);
	auto t1 = std::chrono::high_resolution_clock::now();
	
	std::chrono::duration< double > fs = t1 - t0;
	std::chrono::milliseconds d = std::chrono::duration_cast<std::chrono::milliseconds>(fs);
	printf("DONE. ");
	std::cout << d.count() << "ms\n";
	
	benchTimes<float, MAT_SIZE>(A, B, C, bench_idx, 1); // matMul naive
	return 0;

}
