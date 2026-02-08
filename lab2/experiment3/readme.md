## Experiment 3 — Strong and Weak Scaling

### Strong Scaling
The problem size was kept constant while increasing the number of threads.

| Threads | Time (s) |
|--------:|---------:|
| 1 | 0.642607 |
| 2 | 0.262973 |
| 4 | 0.241769 |
| 8 | 0.233938 |

**Observation:** Execution time decreases initially but saturates due to parallel overhead and memory bandwidth limitations.

---

### Weak Scaling
The problem size was increased proportionally with the number of threads.

| Threads | Problem Size (N) | Time (s) |
|--------:|-----------------:|---------:|
| 1 | 25M | 0.066959 |
| 2 | 50M | 0.163660 |
| 4 | 100M | 0.363766 |
| 8 | 200M | 0.912180 |

**Observation:** Execution time increases with problem size due to memory bandwidth contention and cache effects in shared-memory systems.
