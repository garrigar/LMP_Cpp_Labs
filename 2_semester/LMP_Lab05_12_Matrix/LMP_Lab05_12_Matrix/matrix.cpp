/* matrix.cpp */

#include "matrix.hpp"

Matrix::Matrix() // creates 1x1 identity matrix E = (1)
	: N(1)
	, M(1)
{
	data = new double[1];
	*data = 1;
}

Matrix::Matrix(size_t rows, size_t cols) // creates empty (0) matrix
	: N(rows)
	, M(cols)
{
	if (rows == 0 || cols == 0) // check params
		throw Error("Matrix constructor has 0 size at least in one dimension");

	data = new double[N*M];
	for (size_t i = 0; i < N; i++)
		for (size_t j = 0; j < M; j++)
			(*this)(i, j) = 0;

}

Matrix::Matrix(const Matrix & right)
	: N(right.N)
	, M(right.M)
{
	if (right.N == 0 || right.M == 0)
		throw Error("rvalue matrix has 0 size at least in one dimension");

	data = new double[N*M];
	for (size_t i = 0; i < N; i++)
		for (size_t j = 0; j < M; j++)
			(*this)(i, j) = right(i, j); // copy values
}

Matrix::~Matrix()
{
	delete[] data;
}

double& Matrix::operator()(size_t i, size_t j)
{
	if (i >= N || j >= M)
		throw Error("Matrix subscript out of bounds");
	return data[M*i + j];
}

double Matrix::operator()(size_t i, size_t j) const
{
	if (i >= N || j >= M)
		throw Error("const Matrix subscript out of bounds");
	return data[M*i + j];
}

Matrix& Matrix::operator=(const Matrix& mat)
{
	if (&mat == this) // self-assignment
		return *this;

	Matrix temp(mat); // new matrix with data from mat
	
	//swap(*this, mat);
	// swapping fields
	std::swap(this->data, temp.data);
	std::swap(this->N, temp.N);
	std::swap(this->M, temp.M);
	// now temp contains old data, whet it exits the scope, destructor deletes old data correctly

	return *this;
}

Matrix& Matrix::operator+=(const Matrix& right)
{
	if (right.N == 0 || right.M == 0)
		throw Error("rvalue matrix has 0 size at least in one dimension");
	if (N != right.N || M != right.M)
		throw Error("Operands differ by size");
	for (size_t i = 0; i < N; i++)
		for (size_t j = 0; j < M; j++)
			(*this)(i, j) += right(i, j); // adding by elements
	return *this;
}

Matrix& Matrix::operator-=(const Matrix& right)
{
	if (right.N == 0 || right.M == 0)
		throw Error("rvalue matrix has 0 size at least in one dimension");
	if (N != right.N || M != right.M)
		throw Error("Operands differ by size");
	for (size_t i = 0; i < N; i++)
		for (size_t j = 0; j < M; j++)
			(*this)(i, j) -= right(i, j); // subtracting by elements
	return *this;
}

Matrix& Matrix::operator*=(const Matrix& right)
{
	if (right.N == 0 || right.M == 0)
		throw Error("rvalue matrix has 0 size at least in one dimension");
	if (M != right.N)
		throw Error("Matrixes cannot be multiplicated");
	Matrix ans(N, right.M);
	for (size_t i = 0; i < ans.N; i++)
		for (size_t j = 0; j < ans.M; j++)
			for (size_t k = 0; k < M; k++)
				ans(i, j) += ((*this)(i, k) * right(k, j)); // matrix multiplication
	*this = ans;
	return *this;
}

Matrix& Matrix::operator*=(double d)
{
	for (size_t i = 0; i < N; i++)
		for (size_t j = 0; j < M; j++)
			(*this)(i, j) *= d; // multiplication by number
	return *this;
}

Matrix& Matrix::operator/=(double d)
{
	if (abs(d) < DBL_EPSILON) // if d is zero
		throw Error("Division by zero");
	for (size_t i = 0; i < N; i++)
		for (size_t j = 0; j < M; j++)
			(*this)(i, j) /= d; // division by number
	return *this;
}

Matrix Matrix::getTranspondedMatrix() // returns transponded matrix
{
	Matrix temp(M, N);
	for (size_t i = 0; i < N; i++)
		for (size_t j = 0; j < M; j++)
			temp(j, i) = (*this)(i, j);
	return temp;
}

bool operator==(const Matrix& left, const Matrix& right)
{
	if (left.N != right.N || left.M != right.M) // if dimensions are not equal
		return false;
	for (size_t i = 0; i < left.N; i++)
		for (size_t j = 0; j < left.M; j++)
			if (left(i, j) != right(i, j)) // compare by elements
				return false;
	return true;
}

bool operator!=(const Matrix& left, const Matrix& right)
{
	return !(left == right);
}

std::ostream& operator<<(std::ostream& os, const Matrix& matrix) // todo
{
	for (size_t i = 0; i < matrix.N; i++)
	{
		for (size_t j = 0; j < matrix.M; j++)
			os << matrix(i, j) << ' ';
		os << '\n';
	}	
	return os;
}

std::istream& operator>>(std::istream& is, Matrix& matrix) // todo
{
	for (size_t i = 0; i < matrix.N; i++)
		for (size_t j = 0; j < matrix.M; j++)
			is >> matrix(i, j);

	return is;
}

Matrix operator+(const Matrix & left, const Matrix & right)
{
	Matrix temp(left);
	return (temp += right);
}

Matrix operator-(const Matrix & left, const Matrix & right)
{
	Matrix temp(left);
	return (temp -= right);
}

Matrix operator*(const Matrix & left, const Matrix & right)
{
	Matrix temp(left);
	return (temp *= right);
}

Matrix operator*(const Matrix & left, double right)
{
	Matrix temp(left);
	return (temp *= right);
}

Matrix operator*(double left, const Matrix & right)
{
	return (right * left);
}

Matrix operator/(const Matrix & left, double right)
{
	Matrix temp(left);
	return (temp /= right);
}

Matrix::Error::Error(std::string msg) {	info = msg; } // raises error with sinfo

std::string Matrix::Error::what() {	return info; } // get error info
