
Questions
=========


AXPY CUDA
---------

* How many more threads are run in version 2 compared to version 1? How much speedup might you expect as a result? How much speedup do you see in your plot?
There are 256 times more threads in version 2 compared to version 1. I would expect to see about a 256x speed up, which is about what I'm seeing in the chart. 

* How many more threads are run in version 3 compared to version 2? How much speedup might you expect as a result? How much speedup do you see in your plot? (Hint: Is the speedup a function of the number of threads launched or the number of available cores, or both?)
There are 16x more threads, which is 4096 total threads. We saw just over 10x speed up. Since this wasn't a perfect 16x speed up, that means that the number of cores and threads matter. Since we only have 2496 cores we are limited by the number of operations. 

* (AMATH 583) The cu_axpy_3 also accepts as a second command line argument the size of the blocks to be used. Experiment with different block sizes with, a few different problem sizes (around :math:`2^{24}` plus or minus).  What block size seems to give the best performance?  Are there any aspects of the GPU as reported in deviceQuery that might point to why this would make sense?
I'm seeing conistent performnce up to 2^31 but onsce after that I get terrible performance. I'm guessing this could be from going larger than a 32 bit integer. From 2^18 to 2^31 I saw the same performance. 

nvprof
------

* Looking at some of the metrics reported by nvprof, how do metrics such as occupancy and efficiency compare to the ratio of threads launched between versions 1, 2, and 3?
axpy_1: 0.015 occupancy and 7.65% multiprocessor activity (12.5% memory efficiency)
axpy_2: 0.127 occupancy and 7.2% multiprocessor activity (100% memory efficiency)
axpy_3: 0.752 occupancy and 40.35% multiprocessor activity (100% memory efficiency)
axpy_t: 0.778 occupancy and 45.12% multiprocessor activity (100% memory efficiency)
These results back up what we saw in the axpy graph in the earlier section. The higher the occupancy, and the higher the activity the better performance we are going to see. 

norm
----

* Consider just the Second column for single and double.  Why might there be a difference in performance between the two?
Since the computation is the same, the difference has to be coming from memory. There isn't a difference in first and second for the double, but the float run was pretty big. 
Its probably something to do with memory being cached and with floats being smaller more of it might be able to be cached. 

* Consider just the First and Second columns for single precision.  Why might there be a difference in performance between the two?
(Hint:  What data structure are we starting with in the driver?  Our own ``Vector`` type.  What are its element types as compared to what we are sending to the GPU?)
In our vector type, the information is stored as size_t. This stores it as a float size if we are using floats. Since floats take up half the space of doubles then more memory could be cached 
which could show our increase in performance. 

* Compare and contrast strided partitioning for task-based parallelism (e.g., OpenMP or C++ tasks) with strided partitioning for GPU.  Why is it bad in the former case but good (if it is) in the latter case?
In the OpenMP and C++ cases, a lot of performance has to come from the way the memory is stored. Since these programs are row based more information is brought in for values within the same row. 
For the GPU cases, we have many more threads doing many smaller amounts of tasks so the memory boost of having numbers next to each other doesn't help here. By having the numbers be strided we can grab them from 
different locations in memory we can grab those locations and move them to separate threads more easily than if they were all closer together. 

About PS7
---------

* The most important thing I learned from this assignment was ...
How important it is to understand the differences between GPU's and CPU's when trying to write efficient programs on them. Even though we're trying to accomplish the same task, we 
need to go about performing those tasks very differently to maximize our performance. 

* One thing I am still not clear on is ...
Why for the First column in norm_thrust, I see a drop off in performance for larger matrices for the floats. For the doubles, there isn't a drop off and performance keeps increasing. 
I would have expected doubles to behave the same as floats and drop off in performance for the very large matrices. 
