


1.) What level of SIMD/vector support does the CPU your computer provide?
SSE3, SSSE3, SSE4A, SSE41, SSE42, AVX, AVX2


2.) What is the maximum operand size that your computer will support?
256-bit operands

3.) How many double-precision floating point numbers can fit into one operand given the maximum operand size that your CPU will support?
4 double-precision floating point numbers at 64-bits will fit inside a 256-bit operand.

4.) What is the clock speed of your CPU?  (You may need to look this up via "About this Mac" or "lscpu").
3.6GHz

5.) Based on the output from bandwidth.exe on your computer, what do you expect L1 cache and L2 cache sizes to be?  What are the corresponding bandwidths?   How do the cache sizes compare to what "about this mac" (or equivalent) tells you about your CPU?  (There is no "right" answer for this question -- but I do want you to do the experiment.)
L1 cache is about 32kB and my L2 cache is about 256kB. In about my mac it lists L2 as 256kB as well. I also found that my L1 cache is split between
instructions and data, at 32kB each giving a total of 64kB per code.

6 .) (Same as number 8) What is the (potential) maximum compute performance of your computer?  (The horizontal line.)  What are the L1, L2, and RAM bandwidths?  How do those bandwidths correspond to  what was measured above with the bandwidth program?
Maximum compute performance is 59.0 GFLOPs/sec. L1 = 194.7 GB/s, L2 = 132.0 GB/s, L3 = 94.3 GB/s, and DRAM = 28.7 GB/s. The random 128-bit reads from bandwidth is nearly identical to the values from roofline. The Sequential 256-bit
reads were much higher on L1 (282GB/s) then dropped to 123 GB/s for the L2.

7.) Based on the clock speed of your CPU and its maximum Glop rate, what is the (potential) maximum number of *double precision* floating point operations that can be done per clock cycle?  (Hint: Glops / sec :math:`\div` GHz = flops / cycle.)  There are several hardware capabilities that can contribute to supporting more than one operation per cycle: fused multiply add (FMA) and AVX registers.  Assuming FMA contributes a factor of two, SSE contributes a factor of two,  AVX/AVX2 contribute a factor of four, and AVX contributes a factor of eight of eight, what is the expected maximum number of floating point operations your CPU could perform per cycle, based on the capabilities your CPU advertises via cpuinfo (equiv. lscpu)?  Would your answer change for single precision (would any of the previous assumptions change)?
59 GFlops/sec / 3.6 GHz = 16.4 flops/cycle. This translates to 16.4 flops/cycle * 8 double precision floats ~ 131 double precision floating point operations per clock cycle.
Single precision would double the performance to 262 single precision floating point operations per second. This is because the AVX factor of 8 for double precision would double to 16 for single precision.
The CPU would be able to hold double the single precision values in the registry.

8.) What is the maximum compute performance of your computer?  (The horizontal line.)  What are the L1, L2, and DRAM bandwidths?  How do those bandwidths correspond to what was measured above?
Maximum compute performance is 59.0 GFLOPs/sec or . L1 = 194.7 GB/s, L2 = 132.0 GB/s, L3 = 94.3 GB/s, and DRAM = 28.7 GB/s. The random 128-bit reads from bandwidth is nearly identical to the values from roofline. The Sequential 256-bit
reads were much higher on L1 (282GB/s) then dropped to 123 GB/s for the L2.

9.) Referring to the figures about how data are stored in memory, what is it about the best performing pair of loops that is so advantageous?
THe best performing group was ikj. Since j is the index being performed the most, and j is moving along the row of B this allows the best memory allocation.
In the figure it would make both arrows point the same direction.

10.) What will the data access pattern be when we are executing ``mult_trans`` in i,j,k order?  What data are accessed in each if the matrices at step (i,j,k) and what data are accessed at step (i, j, k+1)? Are these accesses advantageous in any way?
Since the transpose operation switches the indices in B, the ijk order would be the most advantageous. It is equivalent to the optimization from the question above where we swaped the loop order, here we are swapping the index orders in B.

11.) Referring again to how data are stored in memory, explain why hoisting  ``C(i,j)`` out of the inner loop is so beneficial in mult_trans with the "ijk" loop ordering.
We are seeing that in the jump fom mult_trans_0 to mult_trans_1 becuase hoisting allows us to use this loop memory optimizaton method. The hoisting takes C(i,j) out of the lowest memory and add in more of the columns of A and B.
With the loop ordering adding more of A and B is highly advantageous.

12.) What optimization is applied in going from ``mult_2`` to ``mult_3``?
Even in the original mult_3 it implemented blocking which helps performance in large matrices. In the new mult_3 we are adding in the advantage of the loop ordering. The transpose of B has to be sent to mult_trans but this performance penalty is
small compared to the advantage of the loop ordering coming from the mult_trans function.

13.) How does your maximum achieved performance for ``mult`` (any version) compare to what bandwidth and roofline predicted?
The maximum performance from roofline, says 59 GFlops/sec and the best performance I got was 33.7 Gflops/sec from mult_trans_2 for a 128 sized matrix.
This achieved a little over half the maximum performance.




