/* square_matrix.cpp */

#include "square_matrix.hpp"

SquareMatrix::SquareMatrix() : Matrix(){}

SquareMatrix::SquareMatrix(size_t rows) : Matrix(rows, rows) {}

SquareMatrix::SquareMatrix(const SquareMatrix & right) : Matrix(right){}

double SquareMatrix::determinant() { return det(*this, N); }

double SquareMatrix::trace()
{
	double ans = 0;
	for (size_t i = 0; i < N; i++)
	{
		ans += (*this)(i, i);
	}
	return ans;
}

double SquareMatrix::det(SquareMatrix& mat, size_t n) {
	if (n == 1) // if size = 1
		return mat(0, 0);
	else if (n == 2) // if size = 2
		return mat(0, 0)*mat(1, 1) - mat(0, 1)*mat(1, 0);
	else {
		double ans = 0;
		int k = -1; // (-1)^(i+j)
		for (size_t i = 0; i < n; i++) {
			k *= (-1);
			SquareMatrix temp(n - 1); // minor (n-1)x(n-1)
			for (size_t j = 0; j < n; j++)
				if (j < i) { // if before the coloumn
					for (size_t k = 0; k < n - 1; k++)
						temp(k, j) = mat(k + 1, j); // "shift" up
				}
				else if (j > i) { // if after coloumn
					for (size_t k = 0; k < n - 1; k++)
						temp(k, j - 1) = mat(k + 1, j); // "shift" up and left
				}
			ans += det(temp, n - 1)*k*mat(0, i);
		}
		return ans;
	}

}