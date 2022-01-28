//============================================================================
// Name        : testSort.cpp
// Author      : Héctor Ferrada
// Copyright   : 
// Description : Code to test the blockInsertionSort Algorithm [1].
//
// Bibliogrphy
// [1] Ferrada, A Sorting Algorithm Based on Ordered Block Inserts,
// Journal on computational Sciences, 2022.
//============================================================================

#include <iostream>
#include <cstdlib>
#include <random>
#include <ctime>
#include <algorithm>
#include "Sorting.hpp"

using namespace std;
using namespace srt; // namespace created in Sorting.hpp

// Structure with all globals parameters program
typedef struct {
	int *stlS;	// array to use in std::sort method
	int *stlQ; 	// array to use in std::qsort method
	int *I;		// array to use in srt::insertionSort method
	int *BI;	// array to use in srt::blockinsertionsort method
	int *BImaxB;	// array to use in srt::blockinsertionsort_max_B method

	size_t n;	// array length
	size_t REPET;	// experiment repetitions. The REPET arrays will be created for each algorithm

	bool NORMAL;	// flag probability: 1 = NORMAL, 0 = UNIFORM
	size_t stddev;	// Standard deviation for normal distribution, media = n/2
} ParProg;

#define PRINT 0
#define TEST 0
#define MIN 0
#define MAX 1000000

void testSort(ParProg par);
void runExpInsertionSort(ParProg par, bool small);
void runBaseLineExperiments(ParProg par);
template<typename T> void genArray(T *A, size_t n, bool flagNormal, size_t stddev);
template<typename T> void copyArray(T *O, size_t n, T *D);
template<typename T> void printArray(T* A, size_t l, size_t r);

// A comparator function used by qsort
int compare(const void * a, const void * b){
    return ( *(int*)a - *(int*)b );
}

int main(int argc, char **argv){
	ParProg par;

	if(argc < 4){
		// -n normal distribution, -med media -std stddev; -f <prefix> save into a file
		cout << "Execution Error! call: ./tastSort <n> <REPET> <NORMAL_flag> [<stddev>]" << endl;
		exit(EXIT_FAILURE);
	}
	par.n = atoi(argv[1]);
	par.REPET = atoi(argv[2]);
	par.NORMAL = atoi(argv[3]);
	if (par.NORMAL)
		par.stddev = atoi(argv[4]);

	cout << "Parameters..." << endl;
	cout << "n = " << par.n << endl;
	cout << "REPET = " << par.REPET << endl;
	cout << "Normal = " << par.NORMAL << endl;
	if (par.NORMAL)
		cout << "stddev = " << par.stddev << endl;

	par.stlS = new int[par.n];
	par.stlQ = new int[par.n];
	par.I = new int[par.n];
	par.BI = new int[par.n];
	par.BImaxB = new int[par.n];

	if (TEST)
		testSort(par);
	runBaseLineExperiments(par);

	cout << "################## " << endl;
	return EXIT_SUCCESS;
}


void runBaseLineExperiments(ParProg par){
	size_t k;
	clock_t timeQ;
	float extraB, extraBmaxB, acStlQ, acStlS, acBI, acBImaxB, acI;

	k = log(par.n)/log(srt::blockIS);
	k = pow(srt::blockIS,k);
	extraB = (float)(k*sizeof(int))/(1024*1024);
	cout <<endl << "blockIS = " << srt::blockIS << ", Extra size --> " << extraB << " MiB., with " << k << " cells" << endl;

	extraBmaxB = (float)(srt::maxBlockIS*sizeof(int))/(1024*1024);
	cout << "Extra size for block insertion sort MaxB = " << extraBmaxB << " MiB --> " << srt::maxBlockIS << " cells" << endl;

	acStlQ = acStlS = acBI = acBImaxB = acI = 0.0;
	cout << "_________________________________________________" << endl;
	cout << "  Executing experiments (all sorts), " << par.REPET << " repetitions " << endl;
	for (k=0; k<par.REPET; k++){
		genArray(par.stlS, par.n, par.NORMAL, par.stddev);
		copyArray(par.stlS, par.n, par.stlQ);
		copyArray(par.stlS, par.n, par.I);
		copyArray(par.stlS, par.n, par.BI);
		copyArray(par.stlS, par.n, par.BImaxB);

		timeQ = clock();
		blockInsertionSort(par.BI, 0, par.n-1);
		acBI += (float)(clock() - timeQ)/CLOCKS_PER_SEC;

		timeQ = clock();
		blockInsertionSortMaxB(par.BImaxB, 0, par.n-1);
		acBImaxB += (float)(clock() - timeQ)/CLOCKS_PER_SEC;

		timeQ = clock();
		qsort(par.stlQ, par.n, sizeof(int), compare);
		acStlQ += (float)(clock() - timeQ)/CLOCKS_PER_SEC;

		timeQ = clock();
		sort(par.stlS, par.stlS+par.n);
		acStlS += (float)(clock() - timeQ)/CLOCKS_PER_SEC;
		
		if(0){  // WARNING !! insertionsort is very slow...
			clock();
			insertionSort(par.I, 0, par.n-1);
			acI += (float)(clock() - timeQ)/CLOCKS_PER_SEC;
		}
	}

	cout << "Time blockInsertionSort : " << 1000*acBI/par.REPET<< " ms" << endl;
	cout << "Time blockInsertionSortMaxB: " << 1000*acBImaxB/par.REPET<< " ms" << endl;
	cout << "Time stl::qsort = " << 1000*acStlQ/par.REPET<< " ms" << endl;
	cout << "Time stl::sort = " << 1000*acStlS/par.REPET<< " ms" << endl;
	//cout << "Time insertionsort = " << 1000*acI/par.REPET<< " ms" << endl;
}


void testSort(ParProg par){
	int m;
	size_t i, k;
	float extraS;
	par.stlS = new int[par.n];
	par.BI = new int[par.n];
	par.BImaxB = new int[par.n];

	extraS = (float)(srt::maxBlockIS*sizeof(int))/(1024*1024);
	cout << "Testing ..." << endl;
	cout << "   Extra size for block insertion sort MaxB = " << extraS << " MiB --> " << srt::maxBlockIS << " cells" << endl;

	for (k=0; k<par.REPET; k++){
		genArray(par.stlS, par.n, par.NORMAL, par.stddev);
		copyArray(par.stlS, par.n, par.stlQ);
		copyArray(par.stlS, par.n, par.I);
		copyArray(par.stlS, par.n, par.BI);
		copyArray(par.stlS, par.n, par.BImaxB);

		if (PRINT){
			cout << k << ", To sort this array = " << endl;
			printArray(par.stlS, 0, par.n-1);
		}
		sort(par.stlS, par.stlS+par.n);
		if (PRINT){
			cout << "   Sorted array = " << endl;
			printArray(par.stlS, 0, par.n-1);
		}
		qsort(par.stlQ, par.n, sizeof(int), compare);
		insertionSort(par.I, 0, par.n-1);

		if (k==0){
			m = round(log(par.n/blockIS) / log(blockIS));
			m = pow(blockIS, m);
			extraS = (float)(m*sizeof(int))/(1024*1024);
			cout << "   blockIS = " << blockIS;
			cout << ", Extra size block insertion sort = " << extraS << " MiB --> " << m << " cells" << endl;
		}
		blockInsertionSort(par.BI, 0, par.n-1);
		if (PRINT){
			cout << "   BI array = " << endl;
			printArray(par.BI, 0, par.n-1);
		}
		blockInsertionSortMaxB(par.BImaxB, 0, par.n-1);
		if (PRINT){
			cout << "   BImaxB array = " << endl;
			printArray(par.BImaxB, 0, par.n-1);
		}
		for (i=0; i<par.n; i++){
			if(par.stlS[i] != par.BI[i] || par.stlS[i] != par.BImaxB[i] ||
					par.stlS[i] != par.I[i] || par.stlS[i] != par.stlQ[i]){
				cout << "ERROR... test = " << k << ", cell i = " << i << endl;
				cout << "par.stl[i] = " << par.stlS[i] << endl;
				cout << "par.stlQ[i] = " << par.stlQ[i] << endl;
				cout << "par.I[i] = " << par.I[i] << endl;
				cout << "par.BI[i] = " << par.BI[i] << endl;
				cout << "par.BImaxB[i] = " << par.BImaxB[i] << endl;
				exit(1);
			}
		}
	}
	cout << "Test Ok !!" << endl;
}



//=====================================================================
// generate X nondecreasing array, PATT array for experiments and sample array for bSearch
template<typename T>
void genArray(T *A, size_t n, bool flagNormal, size_t stddev){
	size_t i;
	T num;
	bool pseudoIncrese = 0;
	int DT = 1000;

	if (flagNormal){
		default_random_engine generator;
		normal_distribution<double> distribution(n/2, stddev);	// (mean, stddev)

		for (i=0; i<n; i++){
			num = distribution(generator);
	    	while (num<0)
	    		num = distribution(generator);
	    	A[i] = num;
	    }
	}else{
		if (pseudoIncrese){
			for (i=0; i<n; i++)
				A[i] =  i + (rand()%(DT));
		}else{
			for (i=0; i<n; i++)
				A[i] =  MIN + (rand()%(MAX-MIN));
		}
	}
}

// copy the array O[0..n-1] to D[0..n-1]
template<typename T>
void copyArray(T *O, size_t n, T *D){
	for (size_t i=0; i<n; i++)
		D[i] = O[i];
}

template<typename T>
void printArray(T* A, size_t l, size_t r){
	for (size_t i=l; i<=r; i++)
		cout << A[i] << " ";
	cout << endl;
}
