### Report: Vector Multiplication Using MPI

#### 1. Problem Statement
The task is to perform element-wise multiplication of two vectors using parallel processing with MPI (Message Passing Interface). The vectors are of size \( N \) and each process computes a portion of the result vector. The challenge involves dividing the work among multiple processes and gathering the results efficiently.

#### 2. Approach
To solve the problem, we use MPI to distribute the workload of vector multiplication across multiple processes. The steps involved are as follows:

1. **Initialization**:
   - Initialize the MPI environment.
   - Determine the total number of processes (`world_size`) and the rank of each process (`world_rank`).

2. **Data Distribution**:
   - Divide the vectors into smaller chunks, each of size `local_size` (calculated as \( N / \text{world\_size} \)).
   - Each process initializes its portion of the vectors `a` and `b`.

3. **Computation**:
   - Perform element-wise multiplication of the local portions of vectors `a` and `b` to produce the local result vector `c`.

4. **Gathering Results**:
   - Use `MPI_Gather` to collect the local result vectors from all processes into a single result vector on the root process (rank 0).

5. **Output**:
   - The root process prints the final result vector.

6. **Cleanup**:
   - Free dynamically allocated memory and finalize the MPI environment.

#### 3. Working

**Initialization**:
- The MPI environment is initialized, and the number of processes and the rank of each process are obtained using `MPI_Comm_size` and `MPI_Comm_rank`.

**Data Distribution**:
- Each process is responsible for a portion of the vectors. For a total vector size \( N \) and `world_size` processes, each process handles a sub-vector of size `local_size` = \( N / \text{world\_size} \).
- The vectors `a` and `b` are initialized such that each element is unique and based on the rank of the process to ensure that each process works on a distinct portion of the vectors.

**Computation**:
- Each process performs element-wise multiplication on its sub-vector portion. The multiplication is straightforward, iterating through the local portion and storing the results in the local result vector `c`.

**Gathering Results**:
- After computation, `MPI_Gather` is used to collect the results from all processes. The root process (rank 0) gathers the local results into the final result vector.

**Output**:
- The root process prints the final result vector, showcasing the outcome of the parallel computation.

**Cleanup**:
- Dynamically allocated memory for the vectors is freed, and the MPI environment is finalized using `MPI_Finalize`.

#### 4. Results
The vector multiplication program demonstrates efficient parallel computation by dividing the task among multiple processes and using MPI to handle communication and data gathering. The results printed by the root process confirm the correctness of the element-wise multiplication performed by each process. The approach ensures that the workload is evenly distributed and the final result is accurately assembled from the contributions of all participating processes.

By leveraging MPI, the program achieves scalability and performance improvements, especially for large vector sizes, by utilizing the computing power of multiple processors. This demonstrates the effectiveness of MPI in handling parallel processing tasks in scientific computing and other domains requiring high-performance computing solutions.
