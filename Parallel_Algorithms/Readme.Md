## Parallel Algorithms

https://en.cppreference.com/w/cpp/algorithm.html  
https://en.cppreference.com/w/cpp/algorithm/execution_policy_tag.html 

The C++ Standard Library (STL) parallel algorithms are special overloads of existing algorithms (like std::sort, std::for_each, std::transform) and new algorithms (like std::reduce) that take an **Execution Policy** as the first argument.

Execution Policies
The execution policy dictates how the algorithm should run. We include <execution> to use these:
| Policy Object	| Name	| Description |	Use Case |
|---------------|-------|-------------|----------|
| std::execution::**seq** | Sequential | Forces sequential/series execution. No parallelism is allowed. Identical to not specifying a policy. | Baseline timing, debugging, or when parallelism overhead is too high. |
| std::execution::**par** |	Parallel | Allows parallel execution (across multiple threads/cores). | When the operation is compute-intensive and the order of elements doesn't matter (e.g., summing up a list). |
| std::execution::**par_unseq** | Parallel Unsequenced | Parallel execution on one or more threads, with each thread possibly vectorized. | Best performance for numeric, compute-heavy, and non-associative (floating-point) operations.
| std::execution::**unseq** | Unsequenced | Allows vectorization (SIMD) but forces single-threaded execution. (Less common) | Compute-heavy tasks that benefit from SIMD but don't need multi-threading.


I will be testing out each of these and existing algorithms one by one.