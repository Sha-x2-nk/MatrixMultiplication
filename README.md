# FAST_MAT_MUL_CPU
RAM RAM

### BELOW ARE RESULTS SUMMARISED

| PROCESSOR | PLATFORM |
|--|--|
Intel Core i7-12650H | WINDOWS 11 |


| KERNEL | RUNTIME | relative speedup | absolute speedup
|--------|---------|--| -- |
| LVL1. NAIVE MATMUL| 928 seconds | 1 | 1 |
| LVL2. CACHE AWARE LOOP REARRANGEMENT | 113 seconds | 8.2x | 8.2x |
| LVL3. COMPILER CHANGE TO ICPX & -O3 | 13.623 seconds | 8.29x | 68.12x |
| LVL4. PARALLEL FOR LOOP USING TBB | 2.285 seconds | 5.96x | 406.1x |
| LVL5. TILING | 1.583 seconds | 1.443x | 586.2x |
| LVL6. PARALLEL RECURSION | 1.293 seconds | 1.2x | 717.7x |
| LVL7. COMPILER FLAGS fastmath, arch=native | 0.737 seconds | 1.75x | 1259x |
| LVL8. HARD CODED AVX2 INTRINSICS | 0.56 seconds | - slower | - slower |
| numpy openBLAS | 0.25 seconds | - | - |

All the kernels are in matMulCPU.h header file.


the first 2 kernels were compiled with MSVC.


I did this as a hobby project so the code lacks peoper benchmarking. All the runtimes mentioned here are a minimum of 4-5 code running iterations. The LVL 8 optimisation should work better on AVX-512 supported processors. (like 11th gen Intel Core)


The code is heavily inspired from <b><u>Charles Leiserson's</u></b> lecture on MIT OCW performance engineering. 


ANY NEW BENCHMARKS/IMPROVEMENTS ARE WELCOME.
