/* square_matrix.hpp */

#ifndef _SQUARE_MATRIX_HPP_
#define _SQUARE_MATRIX_HPP_

#include "matrix.hpp"

class SquareMatrix : public Matrix
{
public:
	SquareMatrix(); // standard constructor
	SquareMatrix(size_t rows); // NxN size
	SquareMatrix(const SquareMatrix& right); // copy constructor
	
	double determinant(); // returns det(A)
	double trace(); // returns trace(A)

private:
	double det(SquareMatrix& mat, size_t n); // inner functon for minors
};

#endif // !_SQUARE_MATRIX_HPP_