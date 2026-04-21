# Assignment 6: Introduction to CUDA

## Student Details
- **Name:** [Your Name]
- **Roll No:** [Your Roll No]
- **Course:** Parallel and Distributed Computing (UCS645)
- **Platform:** Google Colab (Tesla T4 GPU)

---

## Overview
This assignment covers basic CUDA programming with focus on:
- GPU device properties and architecture
- Parallel array reduction on GPU
- 2D parallel matrix addition on GPU

### Implemented:
- **Part A:** Device Query
- **Part B:** Array Sum using CUDA
- **Part C:** Matrix Addition using CUDA

---

## Part A: Device Query

### GPU Details

| Property | Value |
|----------|-------|
| GPU Name | Tesla T4 |
| Architecture | Turing |
| Compute Capability | 7.5 |
| Clock Rate | 1590 MHz |
| Multiprocessors | 40 |
| ECC Enabled | Yes |
| Double Precision | Yes |
| Concurrent Kernels | Yes |

### Block and Grid Limits

| Property | Value |
|----------|-------|
| Max Threads per Block | 1024 |
| Max Block Dimensions | 1024 x 1024 x 64 |
| Max Grid Dimensions | 2147483647 x 65535 x 65535 |
| Warp Size | 32 |
| Max Threads per SM | 1024 |
| Registers per Block | 65536 |

### Memory Details

| Memory Type | Size |
|-------------|------|
| Global Memory | 14.56 GB |
| Shared Memory per Block | 48 KB |
| Constant Memory | 64 KB |
| L2 Cache | 4096 KB |
| Memory Bus Width | 256 bit |
| Memory Clock Rate | 5001 MHz |

### Question Answers

**Q1. Architecture and Compute Capability:**
Tesla T4 is based on NVIDIA Turing architecture
with compute capability 7.5.

**Q2. Maximum Block Dimensions:**
1024 x 1024 x 64 (X x Y x Z)
Maximum 1024 threads per block total.

**Q3. Maximum threads (grid=65535, block=512):**
65535 × 512 = 33,553,920 threads

**Q4. When NOT to launch maximum threads:**
- Input data is small — idle threads waste resources
- High register usage per thread causes spilling
- High shared memory usage limits concurrent blocks
- Memory bandwidth is the bottleneck
- Occupancy tuning shows fewer threads is better

**Q5. What limits maximum thread launches:**
- Register file — 65536 registers/block on T4
- Shared memory — only 48 KB per block
- Global memory — 14.56 GB total
- Hardware limits — max 1024 threads/block
- Warp scheduler capacity per SM

**Q6. Shared Memory:**
Fast on-chip memory shared by all threads in a block.
Tesla T4: 48 KB per block.
Used for partial sums, tile caching, inter-thread
communication within a block.

**Q7. Global Memory:**
Main GPU DRAM, largest but slowest memory.
Tesla T4: 14.56 GB.
Used for input/output arrays and large data.

**Q8. Constant Memory:**
Read-only cached memory, fast for broadcast access.
Tesla T4: 64 KB.
Used for kernel parameters and lookup tables.

**Q9. Warp Size:**
A warp = 32 threads executing the same instruction
simultaneously (SIMT model). Branch divergence causes
performance loss. Tesla T4 warp size: 32.
40 SMs × 32 warps = 1280 concurrent warps maximum.

**Q10. Double Precision:**
Yes, fully supported (compute capability 7.5 >= 2.0).
ECC memory also enabled. Note: T4 double precision
throughput is 1/32× of single precision.

---

## Part B: Array Sum

### Approach
- Array of 4,194,304 (2^22) float elements
- Each block reduces its chunk using shared memory
- Tree reduction inside each block
- Final reduction of block sums on CPU

### How Tree Reduction Works
### Configuration
| Parameter | Value |
|-----------|-------|
| Array Size | 4,194,304 elements |
| Block Size | 256 threads |
| Grid Size | 16,384 blocks |
| Total Threads | 4,194,304 |

### Results
| Metric | Value |
|--------|-------|
| CPU Time | ~12.7 ms |
| GPU Time | ~99.3 ms |
| Speedup | 0.13x |
| Verification | MATCH ✓ |

### Why GPU is Slower Here
Array sum is memory-bound with minimal computation
per element. GPU overhead dominates:
1. cudaMemcpy host to device (4M floats)
2. Kernel launch overhead
3. cudaMemcpy device to host (block sums)

CPU handles this efficiently in L3 cache.
GPU advantage appears at compute-heavy tasks
or datasets of 100M+ elements.

### Note on Float Precision
CPU and GPU results differ by ~3.8 out of ~2,097,000.
This is NOT a bug — float32 has only ~7 decimal digits
of precision. With 4M additions, tiny rounding errors
accumulate differently based on order of operations.
Error = 0.0002% which is acceptable for float32.

---

## Part C: Matrix Addition

### Approach
- Two 2048×2048 integer matrices A and B
- Each thread computes exactly ONE element of C
- 2D block and grid structure matches matrix layout
- C[row][col] = A[row][col] + B[row][col]

### Configuration
| Parameter | Value |
|-----------|-------|
| Matrix Size | 2048 x 2048 |
| Block Dimensions | 32 x 32 = 1024 threads |
| Grid Dimensions | 64 x 64 = 4096 blocks |
| Total Threads | 4,194,304 |

### Results
| Metric | Value |
|--------|-------|
| CPU Time | 30.75 ms |
| GPU Time | 17.69 ms |
| Speedup | **1.74x** |
| Verification | PASS ✓ (0 errors) |

### Kernel Analysis
| Metric | Value |
|--------|-------|
| Total Elements | 4,194,304 |
| Floating Ops (FLOPs) | 4,194,304 |
| Global Memory Reads | 8,388,608 |
| Global Memory Writes | 4,194,304 |

### Question Answers

**Q1. Floating point operations:**
Each thread performs 1 addition.
Total = 2048 × 2048 = 4,194,304 operations.

**Q2. Global memory reads:**
Each thread reads A[idx] and B[idx] = 2 reads.
Total = 2 × 4,194,304 = 8,388,608 reads.

**Q3. Global memory writes:**
Each thread writes C[idx] = 1 write.
Total = 4,194,304 writes.

### Why GPU is Faster Here
Matrix addition maps perfectly to GPU's 2D thread
structure. 4096 blocks of 1024 threads process
4,194,304 elements truly in parallel. The larger
matrix gives enough work to overcome launch
overhead — GPU wins at this scale.

### Sample Output Verification
| Index | A[i] | B[i] | C[i] |
|-------|------|------|------|
| 0 | 166 | 740 | 906 |
| 1 | 881 | 241 | 1122 |
| 2 | 12 | 758 | 770 |
| 3 | 21 | 940 | 961 |
| 4 | 535 | 743 | 1278 |

---

## Performance Summary

| Part | Task | CPU Time | GPU Time | Speedup | Status |
|------|------|----------|----------|---------|--------|
| A | Device Query | — | — | — | ✅ Done |
| B | Array Sum (4M) | 12.7 ms | 99.3 ms | 0.13x | ✅ Match |
| C | Matrix Add (2048²) | 30.75 ms | 17.69 ms | 1.74x | ✅ PASS |

---

## Key Takeaways

1. GPU excels at **compute-heavy, data-parallel** tasks
2. For **memory-bound** tasks with small data, CPU wins
3. **Matrix addition** at large scale shows clear GPU advantage
4. **Float32 precision loss** is expected for large reductions
5. **Warp divergence** and **memory coalescing** are critical
   for GPU performance optimization

---

## Files
| File | Description |
|------|-------------|
| `device_query.cu` | Part A — GPU device properties |
| `array_sum.cu` | Part B — Parallel array reduction |
| `matrix_add.cu` | Part C — 2D matrix addition |
| `Assignment6.ipynb` | Google Colab notebook |
| `README.md` | This file |

---

## How to Run

### On Google Colab (Recommended)
1. Open Google Colab
2. Runtime → Change Runtime Type → T4 GPU
3. Run all cells in Assignment6.ipynb

### Compile Manually
```bash
nvcc device_query.cu -o device_query && ./device_query
nvcc array_sum.cu    -o array_sum    && ./array_sum
nvcc matrix_add.cu   -o matrix_add  && ./matrix_add
```
