## Experiment 6: False Sharing (OpenMP-Specific)

### Aim
To study the impact of false sharing on parallel performance and demonstrate how cache-line padding can eliminate it.

---

### Theory
False sharing occurs when multiple threads update different variables that reside on the same cache line. Although there is no logical data dependency, the cache coherence protocol forces unnecessary invalidations, leading to performance degradation.

---

### Experimental Setup
- Programming Model: OpenMP
- Threads: Fixed number of threads
- Two implementations compared:
  - Unpadded shared array (false sharing)
  - Cache-line padded array (no false sharing)
- Execution time measured using omp_get_wtime()

---

### Code Explanation
In the unpadded version, each thread updates an element of a shared array. Since adjacent elements reside on the same cache line, frequent cache invalidations occur.

In the padded version, extra space is added so that each thread’s data resides on a separate cache line, eliminating false sharing.

---

### Results

| Implementation | Execution Time (s) |
|----------------|-------------------:|
| Unpadded       | 0.000123 |
| Padded         | 0.000061 |

---

### Observation
The padded implementation shows a noticeable reduction in execution time compared to the unpadded version. This improvement occurs because padding prevents multiple threads from updating variables on the same cache line, thereby reducing cache invalidation overhead.
