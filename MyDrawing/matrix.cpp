#include "matrix.h"
#include <string>
#include <cmath>
#include <iostream>
 
using namespace std;


mrow::mrow (unsigned int size, double* matrix_row):size(size),matrix_row(matrix_row)
{
	if(size<1){
		throw std::runtime_error(" Operator[]:Size cannot be less than 1");
	}
}


double& mrow::operator[](unsigned int col)
{
	if(col >= this->size){
		throw std::runtime_error("Operator[]: Col index out of range");
	}
	return this->matrix_row[col];
}

double mrow::operator[](unsigned int col) const
{
	if(col >= this->size){
		throw std::runtime_error("Operator[]:Col index out of range");
	}
	return this->matrix_row[col];
}
	

// Parameterized constructor
matrix::matrix(unsigned int rows, unsigned int cols):rows(rows),cols(cols) 
{  	
	//check exception
	if (rows < 1 || cols < 1)
	{
		throw std::runtime_error("Parameterized constructor: bad arguments");
	}
	//create matrix
	the_matrix = new double*[this->rows];
	for(int i=0;i<rows;i++){
		the_matrix[i] = new double[cols];
		for(int j=0;j<cols;j++){
			the_matrix[i][j] = 0.0;
		}
	}	
}

// Copy constructor
matrix::matrix(const matrix& from):rows(from.rows),cols(from.cols)
{
	//copy matrix
	the_matrix = new double*[rows];
	for(int i=0;i<rows;i++){
		the_matrix[i] = new double[cols];
		for(int j=0;j<cols;j++){
			the_matrix[i][j] = from.the_matrix[i][j];
		}
	}
}

// Destructor
matrix::~matrix()
{
	// delete atrix from heap
	for(int i=0;i<rows;i++){
		delete[] the_matrix[i];
	}
	delete[] the_matrix;
}

// Assignment operator
matrix& matrix::operator=(const matrix& rhs)
{
	// check if matrix rhs is same as the_matrix
	if(this==&rhs){
		cout<<"Same Matrix"<<endl;
		return *this;
	}
	
	//free the_matrix 
	for(int i=0;i<rows;i++){
		delete[] the_matrix[i];
	}
	delete[] the_matrix;
	
	//Assign rhs value
	this->rows = rhs.rows;
	this->cols = rhs.cols;
	this->the_matrix = new double*[this->rows];
	//copy rhs values
	for(int i=0;i<this->rows;i++){
		this->the_matrix[i] = new double[this->cols ];
		for(int j=0;j<this->cols ;j++){
			this->the_matrix[i][j] = rhs.the_matrix[i][j];
		}
	}
	return *this;
}

// Named constructor (static)
matrix matrix::identity(unsigned int size)
{	
	//check exception
	if (size < 1)
	{
		throw std::runtime_error("Named constructor: bad arguments");
	}
	//create new matrix
	matrix matrix_i(size,size);
	//add identity values to the matrix
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			if(i==j){
				matrix_i.the_matrix[i][j] = 1.0;
			}
		}
	}
	return matrix_i;	
}




// Binary operations
matrix matrix::operator+(const matrix& rhs) const
{
	// stub
	if(this->rows != rhs.rows || this->cols != rhs.cols){
		throw std::runtime_error("Operator +: Matrixes should "
					"be of same size");
	}
	matrix retMat(this->rows,this->cols);
	for(int i=0;i<this->rows;i++){
		for(int j=0;j<this->cols;j++){
			retMat.the_matrix[i][j] = this->the_matrix[i][j]+ 
							rhs.the_matrix[i][j];
		}
	}
	return retMat;
}


matrix matrix::operator*(const matrix& rhs) const
{
	// stub
	if(this->cols != rhs.rows){
		throw std::runtime_error("Operator *: Matrixes should " 
		"be compatible");
	}
	matrix retMat(this->rows,rhs.cols);
	for(int i =0;i<this->rows;i++){
		for(int j=0;j<rhs.cols;j++){
			retMat.the_matrix[i][j] = 0;
			for(int k =0;k<rhs.rows;k++){
				retMat.the_matrix[i][j] += this->the_matrix[i][k]
									* rhs.the_matrix[k][j];
			}
		}
	}
	return retMat;
}


matrix matrix::operator*(const double scale) const
{
	// stub
	matrix retMat(*this);
	for(int i =0;i<this->rows;i++){
		for(int j=0;j<this->cols;j++){
			retMat.the_matrix[i][j] = scale * this->the_matrix[i][j];
		}
	}
	
	return retMat;
	
}


// Unary operations
matrix matrix::operator~() const
{
	// stub
	matrix retMat(this->cols,this->rows);
	for(int i=0;i<this->rows;i++){
		for(int j=0;j<this->cols;j++){
			retMat.the_matrix[j][i] = this->the_matrix[i][j];
		}
	}
	
	return retMat;
}
	

void matrix::clear()
{
	for(int i=0;i<this->rows;i++){
		for(int j=0;j<this->cols;j++){
			this->the_matrix[j][i] = 0.0;
		}
	}
	return;
}

mrow matrix::operator[](unsigned int row)
{
	// stub
	if(row>= this->rows){
		throw std::runtime_error("Operator[]: Row index out of range");
	}
	
	mrow mr(this->cols,this->the_matrix[row]);
	
	return mr;
}

mrow matrix::operator[](unsigned int row) const
{
	// stub
	if(row>= this->rows){
		throw std::runtime_error("Operator[]: Row index out of range ");
	}
	
	mrow mr(this->cols,this->the_matrix[row]);
	return mr;
}

std::ostream& matrix::out(std::ostream& os) const
{
	os<<"["<<endl;
	for(int i=0;i<this->rows;i++){
		os<<"[ ";
		for(int j=0;j<this->cols;j++){
			os<<this->the_matrix[i][j]<<", ";
		}
		os<<"]"<<endl;
		
	}
	os<<"]"<<endl;
	return os;
	
}
		


// Global insertion and operator
std::ostream& operator<<(std::ostream& os, const matrix& rhs)
{
	// stub
	rhs.out(os);
	return os;
}

// Global scalar multiplication
matrix operator*(const double scale, const matrix& rhs)
{
	// stub
	matrix retMat(rhs);
	retMat.operator *(scale);
	
	return retMat;
}


