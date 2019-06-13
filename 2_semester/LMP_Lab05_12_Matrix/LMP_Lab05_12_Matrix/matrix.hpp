/* matrix.hpp */

#ifndef _MATRIX_HPP_
#define _MATRIX_HPP_

#include <iostream>
#include <string>

class Matrix
{
protected:
	double *data; // to store elements
	size_t N; // number of rows
	size_t M; // number of coloumns

public:

	class Error // inner exeption class
	{
	private:
		std::string info;
	public:
		Error(std::string msg);
		std::string what();
	};

	Matrix(); // standard constructor
	Matrix(size_t rows, size_t cols); // N rows, M cols
	Matrix(const Matrix& right); // copy constructor
	~Matrix(); // destructor

	double& operator() (size_t i, size_t j); // indexation
	double operator() (size_t i, size_t j) const; // indexation in const instanses

	Matrix& operator=(const Matrix& right); // assignment op

	Matrix& operator+=(const Matrix& right);
	Matrix& operator-=(const Matrix& right);
	Matrix& operator*=(const Matrix& right);
	Matrix& operator*=(double d);
	Matrix& operator/=(double d);
	
	friend bool operator==(const Matrix& left, const Matrix& right);
	friend bool operator!=(const Matrix& left, const Matrix& right);

	friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix);
	friend std::istream& operator>>(std::istream& is, Matrix& matrix);

	Matrix getTranspondedMatrix(); // returns transponded matrix

};

Matrix operator+(const Matrix& left, const Matrix& right);

Matrix operator-(const Matrix& left, const Matrix& right);

Matrix operator*(const Matrix& left, const Matrix& right);

Matrix operator*(const Matrix& left, double right);

Matrix operator*(double left, const Matrix& right);

Matrix operator/(const Matrix& left, double right);

#endif // !_MATRIX_HPP_
