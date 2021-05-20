import numpy as np


Ar = 600;
Ac = 1000;
Br = 1000;
Bc = 1100;

# lets populate the matrices 
# Mat_A 
Mat_A = np.zeros([Ar, Ac]);
for r in range(0, Ar):
    for c in range(0, Ac):
        Mat_A[r][c] = r+c;

# Mat_B 
Mat_B = np.zeros([Br, Bc]);
for r in range(0, Br):
    for c in range(0, Bc):
        Mat_B[r][c] = r+c;

Mat_C = np.zeros([Ar, Bc]);
Mat_C = np.matmul(Mat_B.T, Mat_A.T)
print(Mat_C)

