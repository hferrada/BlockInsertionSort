# BlockInsertionSort
This is the source code for the blockInsertionSort algorithm, a comparison-based sorting method that was published by Héctor Ferrada (2022) in the Journal of Computational Sciences.
The input is an array A, of type <T>, of $n$ cells and the method sorts it in O(n log n) time under the RAM model.

Author: 
	Hector Ferrada, Universidad Austral de Chile, hferrada@inf.uach.cl

Description:
  Here is provided the template of the algorithm called blockInsertionSort and its in-place vertion blockInsertionSortMaxB.
  Also is included the classical merge-sort and insertion sort algorithms used in the paper.

Compile:
	To use the code you must compile your program including the header 'Sorting.hpp'.
	Here also is provided an axample source code, 'testing.cpp', with a main routine where the blockInsertionSort method
  is called. Thus, by using the make command the binary 'testSort' will be created.
	
References:
	Please, if you want to include this tool as part of your work/experiments, use the following reference [1].

[1]. Héctor Ferrada. A Sorting Algorithm Based on Ordered Block Inserts,
Journal of computational Sciences, 2022.
