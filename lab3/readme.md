# Parallel Correlation Matrix Computation

## Problem Statement

Given a matrix of size **ny × nx** containing **ny input vectors (rows)**, compute the **correlation coefficient** between every pair of input vectors. For all `0 ≤ j ≤ i < ny`, compute:

correlation(row_i, row_j)
Store the result in the lower triangular matrix location:

result[i + j * ny]

All arithmetic operations are performed using **double precision**.

---

## Implementations

Three versions are included:

| Version     | Description                          |
|-------------|--------------------------------------|
| Sequential  | Baseline single-threaded implementation |
| OpenMP      | Multi-threaded parallel implementation |
| Optimized   | OpenMP + cache optimization + -O3 compiler optimizations |

---

## Compilation

```bash
make
## Execution
./correlate_program <ny> <nx>
Example:
./correlate_program 2000 2000
Performance Evaluation

Matrix Size Tested: 2000 × 2000

Execution Time Comparison
Threads	Time (sec)
1	3.79
2	2.92
4	1.76
8	1.09
Speedup Analysis

Speedup formula:
Speedup = T(1) / T(n)
| Threads | Total Time (sec) | Speedup |
| ------- | ---------------- | ------- |
| 1       | 3.79             | 1.00×   |
| 2       | 2.92             | 1.30×   |
| 4       | 1.76             | 2.15×   |
| 8       | 1.09             | 3.47×   |

Parallel efficiency for 8 threads:
Efficiency = 3.47 / 8 ≈ 43.4%
Observations

Time complexity grows approximately as O(ny² × nx).

Parallel implementation significantly reduces execution time.

Although speedup increases with threads, it is less than linear due to memory bandwidth limits and parallel overhead.

Larger matrix sizes improve parallel efficiency.

Optimization Techniques Used

Precomputation of row means and normalization

Lower triangle computation only

OpenMP parallelization for correlation computation

Improved memory access locality via row pointers

Compiler optimization flag -O3
