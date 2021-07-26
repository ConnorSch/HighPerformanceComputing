
PS3 Questions
=============

Add your answers to this file in plain text after each question.  Leave a blank line between the text of the question and the text of your answer.

argv
----

1. What does `argv[0]` always contain?
the name of the program

2. Which entry of `argv` holds the first argument passed to the program?
argv[1]

3. Which entry of `argv` holds the second argument passed to the program?
argv[2]

4. How would you print just the last argument passed to a program?
argv[argc-1]

float vs double
----------------
//my system's performance: 3*1,000,000,000 operations / 0.843 seconds ~3.56 GFlop/s from efficiency3.exe
// my CPU's listed clock rate is 3.6 GHz

5.  What is the difference (ratio) in execution times 
between single and double precision for    *construction with no optimization*? Explain.
(3*1,000,000,000/41.326s) - (3*1,000,000,000/43.805s) = 0.073 - 0.068 = 0.005 GFlop/s
Double precision variables require more floating points to be stored so this leads to a slight decrease in efficiency.

6.  What is the difference (ratio) in execution times
between single and double precision for    *multiplication with no optimization*? Explain.
(1,000,000,000/5.78s) - (1,000,000,000/6.15s) = 0.173 - 0.163 = 0.01 GFlop/s
Since double precision variables are more precise, more digits are used in the multiplication, which takes slightly longer.

7.  What is the difference (ratio) in execution times 
between single and double precision for    *construction with optimization*? Explain.
(3*1,000,000,000/3.710s) - (3*1,000,000,000/6.724s) = 0.809 - 0.446 = 0.363 GFlop/s
The compiler was able to significantly speed up the creation of the floats vs the doubles. With a smaller data type size
the optimizer is able to manage the memory locations better.

8.  What is the difference (ratio) in execution times 
between single and double precision for    *multiplication with optimization*? Explain.
(1,000,000,000/1.003s) - (1,000,000,000/1.333s) = 0.997 - 0.75 = 0.247 GFlop/s
The compiler was still able to improve efficiency from double to float but less so compared to construction. The smaller
size means less numbers to have to multiple so that's why float would be faster. From these results it appears storing more
numbers takes longer than just multiplying them. Which makes sense since construction requires memory allocation which
might mean reaching out to RAM.

9.  What is the difference (ratio) in execution times 
for double precision    multiplication with and without optimization? Explain. 
(1,000,000,000/1.333s) - (1,000,000,000/6.150s) = 0.75 - 0.163 = 0.587 GFlop/s
In total executation comparisons, optimization allows for a significant boost in speed/performance. The optimizer is able
to perform some changes to teh loop to better manage the memory allocation along with possibly unrolling the loop to make
it faster during runtime.

Efficiency
----------

10.  If you double the problem size for matrix-matrix product, how many more operations will matrix-matrix product perform?
The total operations is n^3, where n is the matrix size. If you double n you will use (2*n)^3 or 8 times more operations.

11.  If the time to perform a given operation is constant, when you double the problem size for matrix-matrix product, how much more time will be required to compute the answer?
It would take 8 times longer to do the multiplation plus some extra time for the increased memory operations of the larger matrices

12.  What ratio did you see when doubling the problem size when mmtime called `mult_0`?  (Hint, it may be larger than what pure operation count would predict.)  Explain.
for smaller matrices (under 1024) it was a little over 10x for doubling but after 1024 it was closer to 8x longer

13.  What raio did you see when doubling the problem size when mmtime called `mult_3`?  Was this the same for `mult_0`?  Referring to the function in amath583.cpp, what optimizations are implemented and what kinds of performance benefits might they provide?
it was still about 10x longer but for all matrix sizes i tried. I twas also about 1/10 the time of mult_0.The methods are: Hoisting and Tiling and Blocking. These don't help with the scaling of the matrices but help utilize the L1 memory cache by breaking the
problem down to smaller matrix sizes, blocking. Hoisting is reducing the total operations by pulling the assignment outside of the lowest loop. The tiling is doing more operations at the lowest loop, this helps
performance by utilizing more lower level memory.

14. (Extra credit.)  Try also with `mult_1` and `mult_2`.
mult_1 was about half as fast as mult_3 for smaller matrices but did much worse than mult_3 with larger matrices.
mult_2 was very similar to mult_3 for smaller matrices (off by around 10%). Then for larger matrices the performance got a lot worse. mult_3 was 3x faster than mult_2 for size = 2048
mult_1 only used hoisting while mult_2 used hoisting and tiling. This was pretty demonstrative how each optimization method can help with performance. It appears to me that hoisting is helpful but not nearly
as much as tiling. It also showed that blocking is mostly helpful for larger matrices, which makes sense since smaller matrices are small enough to fit into the L1/L2 memory on their own.

All-Pairs
---------

15. What do you observe about the different approaches to doing the similarity computation?  Which algorithm (optimizations) are most effective?  Does it pay to make a transpose of A vs a copy of A vs just passing in A itself.  What about passing in A twice vs passing it in once (mult_trans_3 vs mult_trans_4)?
mult_3 did really well for most test cases but was not as efficient when the matrix size increased. Its performance dropped significantly. mult_0-2 performend really poorly along with mult_trans_0-1. These methods aren't well optimized so it wasn't nearly
as fast as ther other. Mult_trans_2-4 did very similar and were the same as mult_3 for the smaller test cases. The transpose solution is fairly significantly better than the straight matrix matrix product for all but the smallest examples.
When comparing mult_trans_3 vs 4 there was very little noticeable difference. Passing along a second matrix doesn't seem to have slowed the executation time down. They both performed the same. This makes sense since there is still the same number of multiplication
steps taking place and the same number of reading/writing steps happening.

16. What is the best performance over all the algorithms that you observed for the case of 1024 images?  What would the execution time be for 10 times as many images?  For 60 times as many images?  (Hint: the answer is not cubic but still potentially a problem.)  What if we wanted to do, say 56 by 56 images instead of 28 by 28?
The best performance for the 1024 case was mult_trans_3 which barely beat out mult_trans_4. Rerunning this process the difference changes and 3/4 are essentially the same.
For increasing the number of images I think the execution time would be doubling instead of cubic. With the blocking we are able to perform greater utilization of the CPU resources so while the number of operations won't go down we can process more at a time.
I think doubling the image size would be the same increase as increasing the number of images. The optimization will be able to hand the larger size up until a point where even the smaller blocks aren't small enough to fit into L1/L2 memory.

About PS3
---------


17. The most important thing I learned from this assignment was ...
How the different optimization techniques work to increase performance. How by blocking we can move all the operations to L1/L2 memory and with hoisting and tiling we can process more memory operations at one time.

18. One thing I am still not clear on is ...
Why i am getting different values from -O3 and -Ofast optimization. I understand -Ofast takes some assumptions that aren't always true mathematically and I guess that is causing me problems.
Based on what I tested i found that finite math flag is not allowing me to get the correct answer to the test cases. My guess would be that there are some near 0 values that are causing an infinity somewhere
that Ofast isn't properly handling but I don't really know. I can't find that much more information on this topic. I noticed through -Rpass=.* the difference in the methods was related to a sinking operation on the t += line.
From my research sinking is related to hoisting but I could not really find out why its different and why Ofast is doing it and why it is breaking my code.