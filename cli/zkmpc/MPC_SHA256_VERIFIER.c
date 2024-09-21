/*
 * modified by: Tan Teik Guan
 * date: 21 Sep 2024
 * project: myquantumkey
 *
 * Copyright (C) pQCee.
 */
/*
 ============================================================================
 Name        : MPC_SHA256_VERIFIER.c
 Author      : Sobuno
 Version     : 0.1
 Description : Verifies a proof for SHA-256 generated by MPC_SHA256.c
 ============================================================================
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "shared.h"

int NUM_ROUNDS = 136;

void printbits(uint32_t n) {
	if (n) {
		printbits(n >> 1);
		printf("%d", n & 1);
	}

}



int main(int argc, char * argv[]) {
	setbuf(stdout, NULL);
	init_EVP();
	openmp_thread_setup();

	if (argc != 4)
	{
		printf("Usage: %s <myquantumkey> <challenge> <proof filename>\n",argv[0]);
		return -1;
	}

	a as[NUM_ROUNDS];
	z zs[NUM_ROUNDS];
	FILE *file;
	char * challenge = argv[1];
	char proofstr[100];

	file = fopen(argv[3], "rb");
	if (!file) {
		printf("Unable to open file!");
		return -1;
	}
	fread(&as, sizeof(a), NUM_ROUNDS, file);
	fread(&zs, sizeof(z), NUM_ROUNDS, file);
	fclose(file);


	uint32_t y[8];
	reconstruct(as[0].yp[0],as[0].yp[1],as[0].yp[2],y);
	printf("Proof for hash: ");
	memset(proofstr,0,sizeof(proofstr));
	for(int i=0;i<8;i++) {
		sprintf(proofstr+(i*8),"%08x", y[i]);
	}
	if (strcmp(proofstr,argv[1]))
	{
		printf("Error: unmatched myquantumkey\n");
		printf("Expected [%s], obtained [%s]\n",proofstr,argv[1]);
		return -2;
	}

	int es[NUM_ROUNDS];
	H3(y, as, NUM_ROUNDS, es);


	int failed = 0;
	#pragma omp parallel for
	for(int i = 0; i<NUM_ROUNDS; i++) {
		int verifyResult = verify(as[i], es[i], zs[i],challenge);
		if (verifyResult != 0) {
			printf("Error in Proof (round %d)\n", i);
			failed = 1;
		}
	}
	if (!failed)
		printf("Proof verified ok\n");	
	
	openmp_thread_cleanup();
	cleanup_EVP();
	return EXIT_SUCCESS;
}
