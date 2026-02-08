## Experiment 5: Synchronization Overhead in OpenMP

### Aim
To analyze the overhead introduced by different synchronization mechanisms in OpenMP.

---

### Theory
Synchronization is required when multiple threads access shared data. However, synchronization introduces overhead that can significantly impact performance.

This experiment compares the following synchronization mechanisms:
- critical section
- atomic operation
- reduction clause

---

### Experimental Setup
- Programming Model: OpenMP
- Operation: Summation of values
- Shared variable updated by multiple threads
- Execution time measured using omp_get_wtime()

---

### Results

| Synchronization Method | Execution Time (s) |
|------------------------|-------------------:|
| Critical Section       | 3.252360 |
| Atomic Operation       | 6.527298 |
| Reduction              | 0.017651 |

---

### Observation
The critical section introduces significant overhead due to serialized access to the shared variable. Atomic operations incur even higher overhead because the atomic update is performed in every iteration, causing cache coherence traffic. Reduction performs best by allowing each thread to use a private variable and combining results at the end.

---

### Conclusion
Synchronization overhead has a major impact on parallel performance. Reduction is the most efficient synchronization method for parallel accumulation. Atomic operations may perform worse than critical sections for fine-grained updates, while critical sections should be avoided in performance-critical code.
