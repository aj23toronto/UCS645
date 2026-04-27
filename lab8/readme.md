# Assignment 8: GPU Accelerated Machine Learning

**Course:** UCS645 — Parallel Computing  
**Environment:** Google Colab (Tesla T4 GPU, CUDA 13.0, sm_75)

---

## Overview

This assignment implements GPU-accelerated CUDA kernels covering core concepts in parallel computing and machine learning primitives across 4 exercises.

---

## Exercises

### Ex01 — CUDA Basics (`ex01_cuda_basics.cu`)
- Vector scaling: `C[i] = k * A[i]`
- Squared difference: `C[i] = (A[i] - B[i])²`
- Launch configuration calculator using ceiling division
- Memory bandwidth benchmark (H2D and D2H) using CUDA events
- ReLU kernel and warp divergence experiment (stretch)

**Compile:**
```bash
nvcc -O2 -arch=sm_75 ex01_cuda_basics.cu -o ex01 && ./ex01
```

---

### Ex02 — Memory Hierarchy (`ex02_memory_hierarchy.cu`)
- Shared memory copy: global → shared → global with `__syncthreads()`
- Max reduction using shared memory tree with `fmaxf`
- Bank conflict profiling across strides 1, 2, 4, 8, 16, 32
- Histogram using `atomicAdd`
- Warp shuffle reduction using `__shfl_down_sync` (stretch)
- Two-phase shared memory histogram (stretch)

**Compile:**
```bash
nvcc -O2 -arch=sm_75 ex02_memory_hierarchy.cu -o ex02 && ./ex02
```

---

### Ex03 — ML Primitives (`ex03_ml_primitives.cu`)
- Sigmoid: `1 / (1 + exp(-x))`
- Tanh: `tanhf(x)`
- Leaky ReLU: `x > 0 ? x : alpha * x`
- ReLU backward (gradient gate)
- Binary Cross-Entropy loss with numerical clipping
- Numerically stable Cross-Entropy using log-sum-exp trick
- Fused Adam optimizer kernel (stretch)

**Compile:**
```bash
nvcc -O2 -arch=sm_75 ex03_ml_primitives.cu -o ex03 -lm && ./ex03
```

---

### Ex04 — CNN Layers (`ex04_cnn_layers.cu`)
- Tiled GEMM using 16×16 shared memory tiles (5-step implementation)
- GEMM benchmark: naive GPU vs tiled GPU vs cuBLAS
- Max pooling 2×2 with stride 2
- Batch normalization (inference mode): `y = γ(x - μ)/√(σ² + ε) + β`
- Direct Conv2D kernel (stretch)

**Compile:**
```bash
nvcc -O2 -arch=sm_75 ex04_cnn_layers.cu -o ex04 -lcublas && ./ex04
```

---

## Results

All exercises pass on Tesla T4 (Google Colab):

| Exercise | Result |
|----------|--------|
| Ex01 — CUDA Basics | All PASS |
| Ex02 — Memory Hierarchy | All PASS |
| Ex03 — ML Primitives | All PASS |
| Ex04 — CNN Layers | All PASS |

### Key observations
- GPU crossover point over CPU occurs around N = 2^14 for simple element-wise ops due to PCIe transfer overhead at small sizes
- Bank conflicts at stride=32 are ~1.8× slower than stride=1 on T4
- cuBLAS outperforms tiled GEMM significantly at large matrix sizes due to Tensor Core usage and vectorized memory access
- H2D bandwidth saturates at ~12.4 GB/s, D2H at ~13.1 GB/s on T4 PCIe
