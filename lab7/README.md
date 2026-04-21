
# Assignment 7: CUDA Part II

## Student Details
- **Name:** Jasmol
- **Roll No:** 102497024
- **Course:** Parallel and Distributed Computing (UCS645)
- **Platform:** Google Colab — Tesla T4 GPU
- **CUDA Version:** 12.8

---

## Files

| File | Description |
|------|-------------|
| `problem1_thread_tasks.cu` | Different tasks per thread |
| `problem2_merge_sort.cu` | CPU vs CUDA merge sort |
| `problem3_vector_add.cu` | Vector addition + bandwidth |
| `Assignment7.ipynb` | Complete Colab notebook |
| `README.md` | This file |

## How to Run

    nvcc problem1_thread_tasks.cu -o p1 && ./p1
    nvcc problem2_merge_sort.cu   -o p2 && ./p2
    nvcc -O3 problem3_vector_add.cu -o p3 && ./p3

---

## Problem 1: Different Tasks per Thread

### Output

    ===== Problem 1: Different Tasks =====
    N = 1024
    Block size: 1024 threads
    Grid  size: 1 block

    --- Task A (Thread 0): Iterative Sum ---
      Result   : 524800
      Expected : 524800
      Match    : YES

    --- Task B (Thread 1): Formula Sum ---
      Result   : 524800
      Expected : 524800
      Match    : YES

    Both threads agree: YES

### Explanation

| Thread | Task | Method | Result |
|--------|------|--------|--------|
| Thread 0 | Iterative Sum | Loop 1 to 1024 | 524800 |
| Thread 1 | Formula Sum | N x (N+1) / 2 | 524800 |
| Others | Copy element | identity | — |

Key concept: Threads execute different code based
on threadIdx — this is intentional thread divergence.

---

## Problem 2: Merge Sort

### Output

    ===== Problem 2: Merge Sort =====
    Array size: 1000

    --- Part A: CPU Pipelined Merge Sort ---
      Time   : 0.1201 ms
      Sorted : YES

    --- Part B: CUDA Parallel Merge Sort ---
      Time   : 29.4066 ms
      Sorted : YES

    --- Part C: Performance Comparison ---
      CPU time : 0.1201 ms
      GPU time : 29.4066 ms
      Slowdown : 244.86x (CPU faster)
      NOTE: GPU wins at N >= 100,000+
      Outputs match: YES

### CPU Pipeline Approach

Recursive merge sort with 3 natural pipeline stages:

    Stage 1: Sort left half  [recursive]
    Stage 2: Sort right half [recursive]
    Stage 3: Merge both halves

### CUDA Parallel Approach

Bottom-up iterative — width doubles each pass:

    Pass 1 (width=1): 500 parallel merges
    Pass 2 (width=2): 250 parallel merges
    Pass 3 (width=4): 125 parallel merges
    ... until fully sorted

### Performance Comparison

| Method | Time | Result |
|--------|------|--------|
| CPU Pipeline | 0.1201 ms | Sorted YES |
| CUDA Parallel | 29.4066 ms | Sorted YES |
| Slowdown | 244.86x | CPU wins |

Why CPU wins for N=1000:
- Kernel launch overhead dominates (~5ms per launch)
- cudaMemcpy transfer cost for small data
- 1000 integers fit entirely in CPU L1 cache
- GPU parallelism wasted on too few elements

GPU wins at N >= 100,000+ where parallelism pays off.

---

## Problem 3: Vector Addition + Bandwidth

### Output

    ===== Problem 3: Vector Addition =====

    Vector size : 1048576 elements
    Block size  : 256 threads
    Grid  size  : 4096 blocks

    --- Device Properties ---
      GPU               : Tesla T4
      Memory Clock Rate : 5001000 kHz
      Memory Bus Width  : 256 bits

    --- 1.3 Theoretical Bandwidth ---
      Formula: 2 x memClockRate(Hz) x busWidth(bytes) / 1e9
      Theoretical BW : 320.06 GB/s

    --- 1.2 Kernel Timing ---
      Kernel time : 12.4676 ms

    --- 1.4 Measured Bandwidth ---
      Bytes Read    : 8388608 bytes (8.39 MB)
      Bytes Written : 4194304 bytes (4.19 MB)
      Total Bytes   : 12582912 bytes (12.58 MB)
      Kernel Time   : 0.012468 s
      Measured BW   : 1.01 GB/s

    ========================================
      Theoretical BW :   320.06 GB/s
      Measured BW    :     1.01 GB/s
      Efficiency     :     0.32 %
    ========================================

    Verification : PASS (errors: 0)

    --- Sample Results ---
    i      A[i]   B[i]   C[i]
    0      0.0    0.0    0.0
    1      0.5    1.5    2.0
    2      1.0    3.0    4.0
    3      1.5    4.5    6.0
    4      2.0    6.0    8.0

### 1.2 Kernel Timing

Kernel execution time measured using CUDA Events:

    cudaEventRecord(start);
    vectorAdd<<<gridSize, BLOCK_SIZE>>>(d_A, d_B, d_C, n);
    cudaEventRecord(stop);
    cudaEventElapsedTime(&kernel_ms, start, stop);

Result: 12.4676 ms

### 1.3 Theoretical Bandwidth

    Formula : 2 x memClockRate(Hz) x busWidth(bytes) / 1e9

    memoryClockRate = 5,001,000 kHz = 5,001,000,000 Hz
    memoryBusWidth  = 256 bits = 32 bytes
    DDR factor      = x2 (double data rate)

    theoreticalBW = 2 x 5,001,000,000 x 32 / 1e9
                  = 320.06 GB/s

### 1.4 Measured Bandwidth

    Formula : measuredBW = (RBytes + WBytes) / time_s / 1e9

    RBytes = 2 x 1048576 x 4 = 8,388,608 bytes
    WBytes = 1 x 1048576 x 4 = 4,194,304 bytes
    Total  = 12,582,912 bytes

    measuredBW = 12,582,912 / 0.012468 / 1e9
               = 1.01 GB/s

### Bandwidth Comparison

| Metric | Value |
|--------|-------|
| Theoretical BW | 320.06 GB/s |
| Measured BW | 1.01 GB/s |
| Efficiency | 0.32% |

Why efficiency is only 0.32%:

| Reason | Explanation |
|--------|-------------|
| Small data (12.58 MB) | GPU memory not saturated |
| Kernel launch overhead | Fixed cost dominates |
| Global memory latency | High first access latency |
| DDR not fully utilized | Bandwidth wasted |

---

## Overall Summary

| Problem | Task | Time | Result |
|---------|------|------|--------|
| P1 Thread 0 | Iterative Sum | instant | 524800 YES |
| P1 Thread 1 | Formula Sum | instant | 524800 YES |
| P2 CPU | Pipeline Sort | 0.1201 ms | Sorted YES |
| P2 GPU | Parallel Sort | 29.4066 ms | Sorted YES |
| P3 | Vector Add BW | 12.4676 ms | PASS 0.32% |

## Key Takeaways

1. Threads do different tasks via threadIdx branching
2. GPU kernel launch overhead dominates for small N
3. Theoretical BW of 320 GB/s never achieved in practice
4. Measured BW depends on data size and access patterns
5. GPU advantage only appears at large scale workloads
