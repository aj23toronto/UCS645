## Experiment 2 — Speedup and Efficiency Analysis

Speedup and efficiency were calculated using execution times obtained in Experiment 1.

### Formulas
- Speedup: S(p) = T₁ / Tₚ
- Efficiency: E(p) = S(p) / p

### Results

| Threads | Time (s) | Speedup | Efficiency |
|--------|----------|---------|------------|
| 1      | 0.664991 | 1.00    | 1.00       |
| 2      | 0.251391 | 2.64    | 1.32       |
| 4      | 0.221430 | 3.00    | 0.75       |
| 8      | 0.212354 | 3.13    | 0.39       |

### Observation
Speedup increases with the number of threads, but efficiency decreases due to parallel overhead, synchronization cost, and memory contention.
