import numpy as np
a = np.array([[1, 2, 3, 4],
     [6, 7, 8, 9],
     [11, 12, 13, 14],
     [16, 17, 18, 19],
     [21, 22, 23, 24]])

b = np.array([[1, 2, 3, 4, 5],
     [6, 7, 8, 9, 10],
     [11, 12, 13, 14, 15],
     [16, 17, 18, 19, 20]])

product = np.zeros((len(a), len(b[0])))
for i in range(0, len(a)):
    for j in range(0, len(b[0])):
        for k in range(0, len(a[0])):
            product[i][j] += a[i][k]*(b.T)[j][k]

print(product)
