
pnorm
-----

* What was the data race?
Saving the partial value in the worker_a funciton.

* What did you do to fix the data race?  Explain why the race is actually eliminated (rather than, say, just made less likely).
Changed the loop to operate on an intermediate variable, and put a mutex lock around the transfer from the intermediate value
the stored value. This prevents the data race from occuring because the intermediate variable is only accessible from the the
function that's operating on it so no other worker_a can access another worker_a's intermediate variable. Then the lock protects
the return variable.

* How much parallel speedup do you see for 1, 2, 4, and 8 threads?
1 thread doesn't offer any speed up, which makes sense since its essentially sequential. 2 threads is a little less than double.
4 threads is ~1.5 times faster than 2 threads and 8 threads didn't provide any increase in performance.

fnorm
-----

* How much parallel speedup do you see for 1, 2, 4, and 8 threads for ``partitioned_two_norm_a``?
It followed the same pattern as pnorm. The speedup increased for 2 and 4 threads but then 8 dropped back to 2.
Sequential still did better than 1 thread.

* How much parallel speedup do you see for 1, 2, 4, and 8 threads for ``partitioned_two_norm_b``?  
1 and 2 thread was slightly better than sequential. 4 and 8 threads performed even worse than sequential.

* Explain the differences you see between ``partitioned_two_norm_a`` and ``partitioned_two_norm_b``.
Function b is using the deferred launch parameter. This delays the execution of the task until the get function is called.
My guess why this performs much worse than function a, is because its not triggering until its needed, it bottlenecks
the threads getting to the CPU so its more like a sequential task instead of a parallel task.

cnorm
-----

* How much parallel speedup do you see for 1, 2, 4, and 8 threads?
I didn't see any performance increase in cyclic parrellization. It was
considerably worse. It did get better for each thread but even at 8 threads
it was only half as fast as sequential.

* How does the performance of cyclic partitioning compare to blocked?  Explain any significant differences, referring to, say, performance models or CPU architectural models.
The cyclic model performs much worse than the other models. Each worker is iterating through values in x very far from each other.
We learned form a previous assignment how when iterating over values next to each other, more can be stored in memory. This breaks
that advantage. We also learned from some Piazza posts ahout how even 1 thread is significantly worse than sequential here.
The one threaded approach is spreading out the work load over many cores so the data caching is significantly worse, and exasperates
the poor caching in cnorm to begin with.

rnorm
-----

* How much parallel speedup do you see for 1, 2, 4, and 8 threads?
All but one specific matrix size does the parallel do better for the higher thread counts. The rest are all lower but
fairly similar.

* What will happen if you use ``std:::launch::deferred`` instead of ``std:::launch::async`` when launching tasks?  When will the computations happen?  Will you see any speedup?  For your convenience, the driver program will also call ``recursive_two_norm_b`` -- which you can implement as a copy of ``recursive_two_norm_a`` but with the launch policy changed.
The deferred workers were marginally better than sequential and the async workers were actually worse than sequesntial.
The deferred task is preferential here because the workers aren't "forking" themselves during execution, they are just running the fully
unfurled worker at the time the get() is called.

General
-------

* For the different approaches to parallelization, were there any major differences in how much parallel speedup that you saw?
pnorm and fnorm were the fastest offering significant more performance than the sequential variation. The other methods were generally slower than
sequential. fnorm was just slightly better than pnorm.

* You may have seen the speedup slowing down as the problem sizes got larger -- if you didn't keep trying larger problem sizes.  What is limiting parallel speedup for two_norm (regardless of approach)?  What would determine the problem sizes where you should see ideal speedup?  (Hint: Roofline model.)
The limiting factor is still memory. Once each partition is larger than L1/L2 memory sizes we don't see that much better performance. We would want
our partitions to scale to the size of the problem keeping everything small enough to fit into lower memory cache.

Conundrum #1
------------

1. What is causing this behavior?
Walking through instruments, I see the mutex.lock() taking most of the time. Since by threading we are creating many functions
for very small computations. Each function has to lock and unlock when storing their result, and if the computations are small
and fast, the locking and unlocking is a large percentage of the time. When you run this sequentially the computation is small enough
to fit into L1/L2 memory and can run very quickly there.

2. How could this behavior be fixed?
One possible option could be to adjust the number of partitions in proportion to the vector size. It could try to create
an optimal size to maximize L1/L2 memory. For example, if a vector is small enough it would create only one partition. This
wouldn't be optimal since it still has the overhead from threading. Another way would for it to decide to perform the computation
sequentially or in parallel based on vector size.

3. Is there a simple implementation for this fix?
You would have two separate workers. One sequential with the locks and one for parallel with the locks. The partitioned
function would have to choose which to use based on the vector length. If it could know the system's L1 memory size
(maybe by hardcoding this in?), then it could determine the max vector length for L1 memory.


Parallel matvec
---------------

* Which methods did you implement?
I used threads. I threaded across each part. I chose threads since I didn't have to include mutex.lock() because
each memory position in y wasn't being updated by other treads. Eliminating the race condition.

* How much parallel speedup do you see for the methods that you implemented for 1, 2, 4, and 8 threads?
For the 8 threaded case, I noted 3-4x speed up for all the parallel methods. At least for all but the smallest 2 sizes.
For the 1 threaded case it performed about the same as the sequential runs. Then each thread addition, the performance
increased for all but the smallest 2 cases.


Conundrum #2
------------

1. What are the two "matrix vector" operations that we could use?
The first operation would be to switch and use the CSC t_matvec functions. This keeps the correct creation of Vector y.
The second would be to transpose P and use the CSR functions. The transpose is necessary because we would want to create y by y = mult(P',x).

2. How would we use the first in pagerank?  I.e., what would we have to do differently in the rest of pagerank.cpp to use that first operation?
The first would just require changing all the calls from CSRMatrix to CSCMatrix and just add in the number of threads to the mult call.

3. How would we use the second?
The second would require taking a transpose of P then the CSR matvec mult call. This creates more operations for the transpose and
might not make intuitive sense of the results since I don't think the pagerank matrix is symmetric.