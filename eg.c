#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
//#include "structs.h"
#include "helper_functions.c"

#define N 4
#define HASH_SIZE 509


int main(void){
	int32_t a[3][2] = {{16,1},{30,5},{10,1}};
	int32_t b[3][2] = {{1,1},{1,5},{10,1}};
	int **bucket_hash_table;
	int32_t bits = (1 << N);
	int i,j;
	int rows = 3;


	int32_t  mask = (1 << N) - 1;


	//int32_t reorderedArray[3][3];

	int hist_size = 1 << N;//also TOTAL NUMBER OF BUCKETS

	int *histogram = (int*)calloc(hist_size,sizeof(int));
	int *pSum = (int*)malloc(sizeof(int)*hist_size);

	int *pSumDsp = (int*)malloc(sizeof(int)*hist_size);

	int32_t LSB;//keep least significant bytes w. size < 32 bytes;


	for(i = 0 ; i < rows ; i++){
		LSB = a[i][0] & mask;
		histogram[LSB]++;
	}


	pSum[0]=0; //prefix sums start from 0.pSum is the sum of all items with the same last n significant bits
	pSumDsp[0]=0;

	for(i = 1 ; i < hist_size; i++){
		pSum[i] = pSum[i-1] + histogram[i-1];
		pSumDsp[i] = pSumDsp[i-1] + histogram[i-1];
	}


	int32_t R[3][2]; //to be changed;Duplicate the original array keeping rowId and Relation Column

	for(i = 0; i < rows ; i++){
		LSB = a[i][0] & mask;
		R[pSumDsp[LSB]][0] = a[i][0];//key
		R[pSumDsp[LSB]][1] = a[i][1];//payload

		pSumDsp[LSB]++;
	}

	//create buckets for tables
	bucket_array *A = (bucket_array*)malloc(sizeof(bucket_array));
	//bucket_array *B = (bucket_array*)malloc(sizeof(bucket_array));
	A->bucketArray = (bucket**)malloc(sizeof(bucket*) * hist_size);
	for(i = 0 ; i < hist_size ; i++){
		A->bucketArray[i] = malloc(sizeof(bucket));
	}


	tuple *t = malloc(sizeof(tuple));
	int prg = 0;

	for (i = 0 ; i < hist_size ; i++){//check periptwsh opou to bucket den iparxei
		bucket *bck = A->bucketArray[i];
		if(histogram[i] != 0){
			printf("i is %d and hist[i] is %d \n",i,histogram[i]);
		bck->tuplesArray = (tuple**)malloc(sizeof(tuple*) * histogram[i]);
		for(j = 0 ; j < histogram[i] ; j++){
			bck->tuplesArray[j] = malloc(sizeof(tuple));
			bck->tuplesArray[j]->key = R[prg][0];
			bck->tuplesArray[j]->payload = R[prg][1];
			prg++;
		}

	}

	}


	// *bucket_hash_table = malloc(sizeof(int*) * HASH_SIZE); //Assigning space for buckets.An array,with size HASH_SIZE,of arrays.
	//
	// for(i = 0 ; i < hist_size ; i++){
	// 	for(j = 0 ; j < pSum[i])
	// }

/*Debug print */
// for( i=0; i< rows; i++){
// 	printf("|%d|%d=%x|%d|\n",i,R[i][0],R[i][0] & mask,R[i][1]);
// }

}
