### Results

| Threads | Time (s) | Bandwidth (GB/s) |
|--------:|---------:|-----------------:|
| 1 | 1.357060 | 3.54 |
| 2 | 0.828025 | 5.80 |
| 4 | 0.641049 | 7.49 |
| 8 | 0.725816 | 6.61 |

---

### Observation
The effective memory bandwidth increases as the number of threads increases from 1 to 4. Beyond 4 threads, bandwidth decreases due to memory bandwidth saturation and increased contention among threads.

---

### Conclusion
This experiment demonstrates memory bandwidth saturation in a multicore system. Increasing the number of threads improves performance only up to the saturation point, after which additional threads do not provide further benefits and may degrade performance.
