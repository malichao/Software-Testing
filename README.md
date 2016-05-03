# Software-Testing

This project is a course project of Software Test. In this poject we want to study the techniques for test cases reduction.Specifically,greedy algorithm and integer linear programming(ILP) are used to perform test case reduction.  

###Greedy Algorithm

A greedy algorithm is an algorithm that follows the problem solving heuristic of making the locally optimal choice at each stage with the hope of finding a global optimum. In many problems, a greedy strategy does not in general produce an optimal solution, but nonetheless a greedy heuristic may yield locally optimal solutions that approximate a global optimal solution in a reasonable time. In test reduction,it iteratively selects test cases that maximizes the code coverage until all the statements are covered.  
  
  
###ILP Algorithm

Integer programming is NP-hard. A special case, 0-1 integer linear programming, in which unknowns are binary, and only the restrictions must be satisfied, is one of Karp's 21 NP-complete problems.So in this project we used an opensource ILP solver -- [lp_solve](http://lpsolve.sourceforge.net/5.5/). lp_solve is a free (LGPL license) linear (integer) programming solver based on the revised simplex method and the Branch-and-bound method for the integers.Three way to use lp_solve

  	Via the API
  	Via input files
  	Via an IDE
  	
In this project we used input files since it's easier to program comparing to the API method and could be automated while IDE could not.  
##Example
