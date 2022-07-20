/*
 * Sorting.hpp
 *
 *  Created on: July-2022
 *      Author: Héctor Ferrada
 *
 *  This code provides the templates for the algoritms: 
 *     - blockInsertionSort --> appeared in paper [1]
 *     - blockInsertionSortMaxB --> appeared in paper [1]
 *     - insertionSort.
 *     - mergeSort.
 *  
 * Bibliogrphy
 * [1] H. Ferrada, A Sorting Algorithm Based on Ordered Block Inserts,
 * Journal on computational Sciences, 2022.
 */

#ifndef SORTING_HPP_
#define SORTING_HPP_

#include <iostream>
#include <cstdlib>
#include <cmath>
using namespace std;

namespace srt{

// DEFAULT CONFIGURATION
size_t blockIS = 16; 		// block size for blockInsertionSort and  blockInsertionSortMaxB, it must be a power of two
size_t maxBlockIS = 1048576; 	// Maximum block length for block blockInsertionSortMaxB. Default: 16^5 = 32^4 = 1048576 = 4 MiB as extra size

template<typename T>
void blockInsertionSort(T *A, size_t l, size_t r){
	size_t pos, ini, end, dt, bLev, sp, ep, lenB, n = r-l+1, potBIS = log2(blockIS);
	long int i, j;
	T key;

	// 1- sort all small blocks: Blk_1, Blk_2, ..
	ini=l;
	end=ini+blockIS;
	while(ini<=r){
		if(end>r) end=r+1;
		for(pos=ini+1; pos<end; pos++){
			key = A[pos];
			j = pos-1;
			while (j>=(long int)ini && key<A[j]){
				A[j+1] = A[j];
				j--;
			}
			A[j+1] = key;
		}
		ini=end;
		end+=blockIS;
	};
	if (n<=blockIS)
		return;

	dt = log(n)/log(blockIS);
	dt = pow(blockIS,dt);
	if (dt==n)
		dt>>=potBIS;
	T* ArrBI = new T[dt];		// extra size

	// We iterate for any segments S[sp...ep] of k blocks, for k in {blockIS, blockIS^2, blockIS^3, ...}
	bLev = blockIS;
	while (bLev < n){
		sp = l;
		while(sp<=r){
			ep = sp + (bLev<<potBIS) -1;
			if(ep>r) ep=r;
			ini=sp+bLev;
			end=ini+bLev;
			if(end>ep+1){
				end=ep+1;
				lenB = end-ini;
			}else
				lenB = bLev;

			// 2- copy the block Blk_2 from A[sp..ep] to ArrBI[]
			for(pos=ini; pos<end; pos++)
				ArrBI[pos-ini] = A[pos];

			// 3- insert all sorted blocks, from Blk_3 to the last block into A[sp..ep]
			ini=sp+(bLev<<1);
			end=ini+bLev;
			j = sp+bLev-1;
			while(ini<=ep){
				if(end>ep+1){
					end=ep+1;
					dt=end-ini;
				}else
					dt=bLev;
				for(i=end-1; i>=(long int)ini; i--){
					key = A[i];
					while (j>=(long int)sp && key<A[j]){
						A[j+dt] = A[j];
						j--;
					}
					A[j+dt] = key;
					dt--;
				}
				j=ini-1;
				ini=end;
				end+=bLev;
			}

			// 4- Insert ArrBI (blk_2) in A
			dt = lenB;
			j = ep-lenB;
			for(i=lenB-1; i>=0; i--){
				key = ArrBI[i];
				while (j>=(long int)sp && key<A[j]){
					A[j+dt] = A[j];
					j--;
				}
				A[j+dt] = key;
				dt--;
			}
			// A[sp..ep] is already sorted
			sp = ep+1;
		}
		// to multiply by blockIS for the next level
		bLev <<= potBIS;
	}
	delete [] ArrBI;
}

template<typename T>
void blockInsertionSortMaxB(T *A, size_t l, size_t r){
	size_t pos, ini, fin, dt, bLev, sp, ep, lenB, potBIS = log2(blockIS);
	long int i, j;
	T key;

	// 1- sort all small blocks: Blk_1, Blk_2, ..
	ini=l;
	fin=ini+blockIS;
	while(ini<=r){
		if(fin>r) fin=r+1;
		for(pos=ini+1; pos<fin; pos++){
			key = A[pos];
			j = pos-1;
			while (j>=(long int)ini && key<A[j]){
				A[j+1] = A[j];
				j--;
			}
			A[j+1] = key;
		}
		ini=fin;
		fin+=blockIS;
	};
	if (r-l<blockIS)
		return;

	T* ArrBIB = new T[maxBlockIS];		// extra size
	bLev = blockIS;
	// We iterate for any segments S[sp...ep] of k blocks, for k in {blockIS, blockIS^2, blockIS^3, ..., maximum-size}
	while (bLev <= maxBlockIS){
		sp = l;
		while(sp<=r){
			if ((bLev<<potBIS) > maxBlockIS)
				ep = r;
			else{
				ep = sp + (bLev<<potBIS) -1;
				if(ep>r)
					ep=r;
			}

			// 2- copy the block Blk_2 from A[sp..ep] to ArrBIB[]
			ini=sp+bLev;
			fin=ini+bLev;
			if(fin>ep+1){
				fin=ep+1;
				lenB = fin-ini;
			}else
				lenB = bLev;
			for(pos=ini; pos<fin; pos++)
				ArrBIB[pos-ini] = A[pos];

			// 3- insert all sorted blocks, from blk_3 to the last block into A[sp..ep]
			ini=sp+(bLev<<1);
			fin=ini+bLev;
			j = sp+bLev-1;
			while(ini<=ep){
				if(fin>ep+1){
					fin=ep+1;
					dt=fin-ini;
				}else
					dt=bLev;

				for(i=fin-1; i>=(long int)ini; i--){
					key = A[i];
					while (j>=(long int)sp && key<A[j]){
						A[j+dt] = A[j];
						j--;
					}
					A[j+dt] = key;
					dt--;
				}
				j=ini-1;
				ini=fin;
				fin+=bLev;
			}

			// 4- Insert ArrBIB (blk_2) in A
			dt = lenB;
			j = ep-lenB;
			for(i=lenB-1; i>=0; i--){
				key = ArrBIB[i];
				while (j>=(long int)sp && key<A[j]){
					A[j+dt] = A[j];
					j--;
				}
				A[j+dt] = key;
				dt--;
			}
			// A[sp..ep] is already sorted
			sp = ep+1;
		}
		bLev <<= potBIS;	// to multiply by blockIS for the next level
	}
	delete [] ArrBIB;
}


// classic insertionsort
template<typename T>
void insertionSort(T *A, size_t l, size_t r){
	T key;
	size_t i, j;

	for(i=l+1; i<=r; i++){
		key = A[i];
		j = i-1;
		while (j>=l && A[j]>key){
			A[j+1] = A[j];
			j--;
		}
		A[j+1] = key;
	}
}

// classic merge rutine
template<typename T>
void merge(T *A, size_t l, size_t m, size_t r){
	size_t i, j, k;
	size_t n1 = m - l + 1;
	size_t n2 = r - m;
    T *L = new int[n1];
    T *R = new int[n2];

    for (i = 0; i < n1; i++)
        L[i] = A[l + i];
    for (i = 0; i < n2; i++)
        R[i] = A[m + 1 + i];

    i = j =  0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            A[k] = L[i];
            i++;
        }
        else {
            A[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if there are any
    while (i < n1) {
        A[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if there are any
    while (j < n2) {
        A[k] = R[j];
        j++;
        k++;
    }

    delete [] L;
    delete [] R;
}


// classic mergesort algorithm to sort A[l..r]
template<typename T>
void mergeSort(T *A, size_t l, size_t r){
    if(l>=r) return;

    size_t m = (l+r-1)/2;
    mergeSort(A, l, m);
    mergeSort(A, m+1, r);
    merge(A, l, m, r);
}

}
#endif /* SORTING_HPP_ */
