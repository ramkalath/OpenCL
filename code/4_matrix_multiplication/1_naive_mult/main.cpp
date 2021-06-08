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

	uint Ar = 800;
	uint Ac = 1000;
	uint Br = 1000;
	uint Bc = 718; // increase this number by one more you will encounter seg fault

	float Mat_A[Ar][Ac];
	float Mat_B[Br][Bc];
	float Mat_C[Ar][Bc];

	/* lets populate the matrices */
	/* Mat_A */
	for(uint r=0; r<Ar; r++) {
		for(uint c=0; c<Ac; c++) {
			Mat_A[r][c] = r+c;
		}
	}

	/* Mat_B */
	for(uint r=0; r<Br; r++) {
		for(uint c=0; c<Bc; c++) {
			Mat_B[r][c] = r+c;
		}
	}

	/* Mat_C - initialize to 0's */ 
	for(uint r=0; r<Ar; r++) {
		for(uint c=0; c<Bc; c++) {
			 Mat_C[r][c] = 0;
		}
	}

	/* printing the matrices */
	//std::cout << "Matrix A =>" << std::endl;
	//for(uint r=0; r<Ar; r++) {
		//for(uint c=0; c<Ac; c++) {
			//std::cout << Mat_A[r][c] << "\t";
		//}
		//std::cout << std::endl;
	//}

	//std::cout << "Matrix B =>" << std::endl;
	//for(uint r=0; r<Br; r++) {
		//for(uint c=0; c<Bc; c++) {
			//std::cout << Mat_B[r][c] << "\t";
		//}
		//std::cout << std::endl;
	//}

	/* Naive matrix multiplication */
	for(uint r=0; r<Ar; r++) {
		for(uint c=0; c<Bc; c++) {
			for(uint k=0; k<Ac; k++) {
				Mat_C[r][c] = Mat_C[r][c] + Mat_A[r][k] * Mat_B[k][c];
			}
		}
	}

	std::cout << "Resultant Matrix C is" << std::endl;
	for(uint c=0; c<Bc; c++) {
		for(uint r=0; r<Ar; r++) {
			std::cout << Mat_C[r][c] << "\t";
		}
		std::cout << std::endl;
	}



	return 0;
}
