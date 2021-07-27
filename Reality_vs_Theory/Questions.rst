

- At what problem size do the answers between the computed norms start to differ?
The two_norm with reversed values differs around a 12,500 matrix size. They both differ after a matrix size
of 25,000.

- How do the absolute and relative errors change as a function of problem size?
The relative difference remains small over all matrix sizes (small is 10^-16).
The absolute difference does grow with with increasing matrix size. It's increase in magnitude
increases by an order of magnitude for every order of magnitude increase in matrix size after the initial difference.

- Does the Vector class behave strictly like a member of an abstract vector class?
No it does not. A pure mathematical vector class should not have any difference in the way the norm is calculated.
These changes do make a difference although it is a small difference.

- Do you have any concerns about this kind of behavior?
Not for any small matrix sizes. Once the matrix size exceeds 1 billion the absolute difference is
on a scale of 10^-10 which is large enough to be considered. For matrices for a million rows or smaller its not much of an issue.


