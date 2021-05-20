/*
	Name: Ramkumar Narayanan
	Date:
	Description:
	Status:
*/

#include<bits/stdc++.h>

#define ushort unsigned short
#define uint unsigned int

int main()
{
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);

	//uint Ah = 10;
	//uint Aw = 15;
	//uint Bh = 15;
	//uint Bw = 30;

	uint Ah = 2;
	uint Aw = 3;
	uint Bh = 3;
	uint Bw = 4;

	float Mat_A[Ah][Aw];
	float Mat_B[Bh][Bw];
	float Mat_C[Ah][Bw];

	/* lets populate the matrices */
	/* Mat_A */
	for(uint i=0; i<Ah; i++) {
		for(uint j=0; j<Aw; j++) {
			Mat_A[i][j] = i+j;
		}
	}
	/* Mat_B */
	for(uint i=0; i<Bh; i++) {
		for(uint j=0; j<Bw; j++) {
			Mat_B[i][j] = i+j;
		}
	}

	/* Naive matrix multiplication */
	for(uint i=0; i<Ah; i++) {
		for(uint j=0; j<Bw; j++) {
			a
			//for(uint k=0; k<Aw; k++) {
				//Mat_A[]
			//}
		}
	}


	/* printing the matrices */
	for(uint i=0; i<Ah; i++) {
		for(uint j=0; j<Ah; j++) {
			std::cout << Mat_A[i][j] << "\t";
		}
		std::cout << std::endl;
	}


	return 0;
}
