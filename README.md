# Matrix Multiplication using Pthreads

## Overview
This project implements matrix multiplication using POSIX threads (pthreads) in C.

The program computes:
C = A × B

Where:
- A, B, C are N × N matrices
- M threads are used to divide the work

Each thread computes a portion of the resulting matrix by processing a subset of columns.

---

## Features
- Dynamic matrix allocation
- Multithreading using pthreads
- Mutex synchronization for shared data
- Global sum calculation of matrix C
- User input for matrix size, thread count, and initialization value

---

## Program Arguments
./matrix N M K


- `N` → size of matrix (NxN)
- `M` → number of threads (must divide N)
- `K` → initial value for matrices A and B

---

## Example Runs
./matrix 5 1 1
./matrix 10 2 10
./matrix 20 4 1


---

## How It Works

- Matrices A and B are initialized with value K
- Matrix C is initialized to 0
- Work is divided among M threads:
  - Each thread computes N/M columns of matrix C
- Mutex is used when:
  - Writing to matrix C
  - Updating global sum

---

## Compilation
gcc matrix.c -o matrix -lpthread


---

## Running
./matrix 10 2 5


---

## Output

- Prints matrices A, B, and C
- Displays total sum of all elements in C

---

## Synchronization

Two mutex locks are used:
- mutex1 → protects matrix C updates
- mutex2 → protects global sum

---

## Requirements
- GCC compiler
- POSIX Threads (pthreads)
- Linux / Unix environment

---

## Author
Josue Gallegos Cortes  
CS 3377 - Systems Programming in UNIX Environments  

---

## Notes
- N must be divisible by M
- Program uses simple thread division by columns
- Designed for educational purposes
