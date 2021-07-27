
Questions
=========


AXPY CUDA
---------

* How many more threads are run in version 2 compared to version 1? How much speedup might you expect as a result? How much speedup do you see in your plot?

* How many more threads are run in version 3 compared to version 2? How much speedup might you expect as a result? How much speedup do you see in your plot? (Hint: Is the speedup a function of the number of threads launched or the number of available cores, or both?)


* (AMATH 583) The cu_axpy_t also accepts as a second command line argument the size of the blocks to be used. Experiment with different block sizes with, a few different problem sizes (around :math:`2^{24}` plus or minus).  What block size seems to give the best performance?  Are there any aspects of the GPU as reported in deviceQuery that might point to why this would make sense?


nvprof
------

* Looking at some of the metrics reported by nvprof, how do metrics such as occupancy and efficiency compare to the ratio of threads launched between versions 1, 2, and 3?


norm
----

* Consider just the Second column for single and double.  Why might there be a difference in performance between the two?

* Consider just the First and Second columns for single precision.  Why might there be a difference in performance between the two?
(Hint:  What data structure are we starting with in the driver?  Our own ``Vector`` type.  What are its element types as compared to what we are sending to the GPU?)

* Compare and contrast strided partitioning for task-based parallelism (e.g., OpenMP or C++ tasks) with strided partitioning for GPU.  Why is it bad in the former case but good (if it is) in the latter case?


About PS7
---------

* The most important thing I learned from this assignment was ...


* One thing I am still not clear on is ...

