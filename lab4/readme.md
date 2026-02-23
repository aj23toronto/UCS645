# UCS645 – Parallel & Distributed Computing  
## Lab 4: Introduction to MPI  

**Name:** Jasmol Arora  
**Platform:** macOS  
**MPI Library:** OpenMPI  

---

# 🔧 Environment Setup

- Language: C
- Compiler: mpicc
- MPI Implementation: OpenMPI
- Execution Command:
  ```
  mpirun -np <number_of_processes> ./program_name
  ```

---

# 1️⃣ Hello MPI Program

## Objective
Understand basic MPI initialization and process identification.

## Command
```
mpirun -np 4 ./hello
```

## Output
```
Hello from rank 2 out of 4 processes
Hello from rank 0 out of 4 processes
Hello from rank 3 out of 4 processes
Hello from rank 1 out of 4 processes
```

## Concepts Used
- MPI_Init
- MPI_Comm_rank
- MPI_Comm_size
- MPI_Finalize

✔ Demonstrates parallel execution and process ranks.

---

# 2️⃣ Ring Communication

## Objective
Implement point-to-point communication in a ring topology.

## Logic
- Process 0 starts with value = 100
- Each process adds its rank
- Message circulates in ring
- Final value returns to Process 0

## Command
```
mpirun -np 4 ./ring
```

## Output
```
Process 0 starting with value 100
Process 1 updated value to 101
Process 2 updated value to 103
Process 3 updated value to 106
Process 0 received final value 106
```

✔ Verified Calculation:  
100 + 0 + 1 + 2 + 3 = **106**

## Concepts Used
- MPI_Send
- MPI_Recv
- Circular rank calculation using modulo

---

# 3️⃣ Parallel Array Sum

## Objective
Compute sum of numbers 1–100 using parallel processing.

## Command
```
mpirun -np 4 ./array_sum
```

## Output
```
Process 0 local sum = 325
Process 1 local sum = 950
Process 2 local sum = 1575
Process 3 local sum = 2200

Global Sum = 5050
Expected = 5050
Average = 50.50
```

✔ Correct global sum = **5050**

## Concepts Used
- MPI_Scatter
- MPI_Reduce
- Parallel workload distribution

---

# 4️⃣ Global Maximum and Minimum

## Objective
Find global maximum and minimum across processes.

Each process:
- Generates 10 random numbers (0–1000)
- Computes local max and min
- Uses MPI_MAXLOC and MPI_MINLOC

## Command
```
mpirun -np 4 ./max_min
```

## Sample Output
```
Global Maximum = 956 (from Process 2)
Global Minimum = 0 (from Process 1)
```

✔ Correctly identified:
- Maximum value and corresponding process
- Minimum value and corresponding process

## Concepts Used
- MPI_Reduce
- MPI_MAX
- MPI_MIN
- MPI_MAXLOC
- MPI_MINLOC
- MPI_2INT structure

---

# 5️⃣ Parallel Dot Product

## Vectors Used
A = [1 2 3 4 5 6 7 8]  
B = [8 7 6 5 4 3 2 1]

## Command
```
mpirun -np 4 ./dot
```

## Output
```
Process 0 partial dot = 22
Process 1 partial dot = 38
Process 2 partial dot = 38
Process 3 partial dot = 22

Final Dot Product = 120
Expected = 120
```

✔ Verified dot product = **120**

## Concepts Used
- MPI_Scatter
- MPI_Reduce
- Parallel reduction

---

# 📊 Performance Measurement

A computational workload using square root calculations was implemented to measure scalability.

Timing functions used:
- MPI_Wtime()
- MPI_Barrier()

## Execution Times

| Processes (p) | Time Tp (seconds) |
|---------------|------------------|
| 1 | 0.699397 |
| 2 | 0.362658 |
| 4 | 0.188127 |
| 8 | 0.115206 |

---

## 🚀 Speedup Calculation

Formula:
Sp = T1 / Tp

| p | Speedup |
|---|---------|
| 1 | 1.00 |
| 2 | 1.93 |
| 4 | 3.72 |
| 8 | 6.07 |

---

## ⚡ Efficiency

Formula:
Ep = Sp / p

| p | Efficiency |
|---|------------|
| 1 | 100% |
| 2 | 96.5% |
| 4 | 93% |
| 8 | 76% |

---

# 🔍 Performance Analysis

- Execution time decreases as the number of processes increases.
- Near-linear speedup observed up to 4 processes.
- Efficiency decreases at 8 processes due to communication and synchronization overhead.
- Demonstrates practical scalability limits in parallel systems.

---

# 📚 Concepts Covered

- MPI Initialization and Finalization
- Process ranks and communicators
- Point-to-point communication
- Collective communication (Scatter, Reduce)
- Reduction operations (SUM, MAXLOC, MINLOC)
- Parallel workload distribution
- Speedup and efficiency analysis
- Scalability behavior

---

# ✅ Conclusion

This lab successfully demonstrates MPI-based parallel programming, inter-process communication, and performance evaluation. Experimental results validate theoretical speedup and efficiency concepts in distributed systems.

---
