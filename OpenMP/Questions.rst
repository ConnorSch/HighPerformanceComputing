
Questions
=========

Norm
----

* Look through the code for ``run()`` in ``norm_utils.hpp``.  How are we setting the number of threads for OpenMP to use?
By setting omp_set_num_threads(nthreads) environment variabl for each thread up to the total number in the input. Then each thread runs through
the norm calculation for each trail.

* Which version of ``norm`` provides the best parallel performance?  How do the results compare to the parallelized versions of ``norm`` from ps5?
norm_block_reduction did the best overall. These versions were about 3 times faster than the results from ps5 for the smaller matrix sizes. The larger matrix sizes were around the same.

* Which version of ``norm`` provides the best parallel performance for larger problems (i.e., problems at the top end of the default sizes in the drivers or larger)?  How do the results compare to the parallelized versions of ``norm`` from ps5?
norm_cyclic_reduction does slightly better than norm_block_reduction or norm_parfor. These are around the same as the best results from ps5, maybe 1 Gflop/s better in certain scenarios.

* Which version of ``norm`` provides the best parallel performance for small problems (i.e., problems smller than the low end of the default sizes in the drivers)?  How do the results compare to the parallelized versions of ``norm`` from ps5?  
norm_block_reduction was the best performer for the smaller matrix sizes. It was roughly 3 times faster than the results from ps5.

Sparse Matrix-Vector Product
----------------------------

* How does ``pmatvec.cpp`` set the number of OpenMP threads to use?
The same way norm_utils does. We are setting the environment variable to the total number of threads to use.


* (For discussion on Piazza.)
What characteristics of a matrix would make it more or less likely to exhibit an error 
if improperly parallelized?  Meaning, if, say, you parallelized ``CSCMatrix::matvec`` with just basic  columnwise partitioning -- there would be potential races with the same locations in ``y`` being read and written by multiple threads.  But what characteristics of the matrix give rise to that kind of problem?  Are there ways to maybe work around / fix that if we knew some things in advance about the (sparse) matrix?
Since the matrix is sparse, most of its columns are 0's. Depending how the non-zero elements are arranged these can lead to different amounts of race conditions.
For example if the data is arranged in columns then CSRMatrix::t_matvec would be most prone to race conditions since it is updating y along column indices. The reverse of this logic applies to CSCMatrix::matvec


* Which methods did you parallelize?  What directives did you use?  How much parallel speedup did you see for 1, 2, 4, and 8 threads?
I used omp parallel for for CSRMatrix::matvec and CSCMatrix::t_matvec. Then I used omp critical for CSRMatrix::t_matvec and CSCMatrix::matvec.
The latter two are prone to race conditions so the critical was required. I thought about adding in a reduction but then I would have to add
a reduction member defined for Vector. I also added a omp critical for the COO matrix members. Since y depends on col_indices_ or row_indices_
the race condition is impossible to fully escape.
v

Sparse Matrix Dense Matrix Product (AMATH583 Only)
--------------------------------------------------


* Which methods did you parallelize?  What directives did you use?  How much parallel speedup did you see for 1, 2, 4, and 8 threads?  How does the parallel speedup compare to sparse matrix by vector product?
I parallelized CSRMatrix::matmat and CSCMatrix::matmat by using the omp parallel for directive. From our results in question 6, there shouldn't be a race condition for these.
For COOMatrix, CSCMatrix, and CSRMatrix I also moved the k loop to outer loop instead of the inside loop for matmat.
With all these improvements I saw a 2x performance boost in the COO and CSC cases. I saw up to 10x performance in CSR performance.
They were of similar magnitude to the performance increases in the sparse cases. CSR in the sparse case was still 2x faster than CSR in teh dense case.

PageRank Reprise
----------------

* Describe any changes you made to pagerank.cpp to get parallel speedup.  How much parallel speedup did you get for 1, 2, 4, and 8 threads?
I just changed it the same way I did in ps5b. I switched the input to a CSCMatrix instead of a CSRMatrix. This allows it to take advantage
of the parallelized CSCMatrix::t_matvec instead of the slower CSRMatrix::t_matvec.
For speedup with 1 thread I noticed the elapsed time for the read step was 500ms slower but the elapsed time in pagerank and rank was about the same.
By adding in more threads the pagerank computation started dropped. For 2 threads I saw a 400ms speedup, for 4 threads an additional 100ms and for 8 threads another 50ms speedup.

* (EC) Which functions did you parallelize?  How much additional speedup did you achieve?


Load Balanced Partitioning with OpenMP (Extra Credit)
-----------------------------------------------------

* Are there any choices for scheduling that make an improvement in the parallel performance (most importantly, scalability) of pagerank?
I was not able to find a choice that improved the performance. I would have thought that dynamic scheduling would achieve
the best results since the sparse matrices are not uniformly distributed.