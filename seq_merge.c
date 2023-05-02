#include <stdio.h> 

/* Parellel merge */

/*
The idea is, given two lists
a = a_0, ... a_r
b = b_0, ... b_r

partition each list into p parts 
a = A_0, ... A_p
b = B_0, ... B_p
where p is number of processes

merge(a,b) should do merge(A_0, B_0), ... merge(A_p, B_p)
we want |A_i| + |B_i| = (2r)/ p for an even balance

must have that max(|A_i|, |B_i|) <= min(|A_i+1|, |B_i+1|)


*/

