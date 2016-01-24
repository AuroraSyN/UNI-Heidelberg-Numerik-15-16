#include <iostream>
#include "hdnum.hh"
#include "LR.hh"
#include "solveL.hh"
#include "solveR.hh"
#include "solveLeastSquares.hh"

typedef double NumberType;

int main ()
{
  hdnum::DenseMatrix<NumberType> A;

  hdnum::readMatrixFromFile("A6_linear.dat", A);
  //hdnum::readMatrixFromFile("A6_quadratic.dat", A);

  // Ausgabe
  A.scientific(false);
  std::cout << "A = " << A << std::endl;

  std::size_t m = A.rowsize();
  std::size_t n = A.colsize();

  hdnum::Vector<NumberType> x(n);
  hdnum::Vector<NumberType> b;
  hdnum::readVectorFromFile("b6.dat", b);

  b.scientific(false);
  std::cout << "b = " << b << std::endl;

  solveLeastSquares( A, b, x );

  std::cout << "Solution x = " << x << std::endl;// schöne Ausgabe  

  b*=-1.0;
  A.umv(b,x);
  std::cout << "quadratic error = |Ax-b| = " << b.two_norm_2() << std::endl;

  return 0
}
