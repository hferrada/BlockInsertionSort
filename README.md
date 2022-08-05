# BlockInsertionSort
Source code for the blockInsertionSort algorithm, a comparison-based sorting method published by Héctor Ferrada (2022) in the Journal of Computational Sciences [1].
The input is an array A of n cells. The method sorts A in O(n log n) worst-case time, under the RAM model. Experiments show that, for random arrays of 10 million cells, the method manages to sort the array in less than 1 second, even better than the times of the popular std::sort provided by C++ STL.

Author: 
	Hector Ferrada, Universidad Austral de Chile, hferrada@inf.uach.cl

Description:
	Here is provided the template of the algorithm called blockInsertionSort and its in-place version blockInsertionSortMaxB. Also is included the classical merge-sort and insertion sort algorithms used in the paper as baseline.

Compile:
	To use the code you must compile your program including the header 'Sorting.hpp'.
	Here also is provided an axample source code, 'testSorting.cpp', with a main routine where the blockInsertionSort method is called. Thus, by using the make command the binary 'testSort' will be created.
	
References:
	Please, if you want to include this tool as part of your research/work/experiments, use the following reference [1].

[1]. Héctor Ferrada. A Sorting Algorithm Based on Ordered Block Insertions.
To appear in Journal of computational Sciences, 2022.
