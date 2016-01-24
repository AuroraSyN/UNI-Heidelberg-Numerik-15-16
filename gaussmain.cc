// Gaussian Elimination
// 
// This program requires hdnum version 0.22
// 
// Compile: g++ -I../hdnum -o gaussmain gaussmain.cc 
//
#include <iostream>
#include <cstdlib>

#include "hdnum.hh"
#include "gauss.hh"


typedef double NumberType;
//typedef float NumberType;

int main(int argc, char ** argv)
{
  if(argc < 2){
	  std::cout << "Usage  : ./gem <number>" << std::endl;
	  std::cout << "Example: ./gem 10" << std::endl;
	  exit(0);
	}
  else
	{
	  int n = atoi( argv[1] );

    hdnum::Vector<NumberType> y(n),b(n);
    hdnum::DenseMatrix<NumberType> A(n,n);

    hdnum::fill(y,NumberType(1.0),NumberType(1.0));
    std::cout << "y=" << y << std::endl;

    hdnum::vandermonde(A,y);
    std::cout << "A=" << A << std::endl;

    A.mv(b,y);
    std::cout << "b=" << b << std::endl;


    std::cout << "Solve Ax=b: ";
    hdnum::Vector<NumberType> x(n);
    gauss(A,x,b);
    std::cout << "Solution x=" << x << std::endl;

    std::cout << "Quality of the solution: ";
    std::cout << "||x-y|| = " << (x-y).two_norm() << std::endl;

  }

  return 0;
}
