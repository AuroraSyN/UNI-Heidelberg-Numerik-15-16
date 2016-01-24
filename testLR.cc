//
// Dateiname:    testLR.cc (Testprogramm für die LR-Zerlegung)
// Kompilieren:  g++ -I../hdnum -o testLR testLR.cc
//
#include <iostream>
#include <iomanip>
#include <cstdlib>

#include "hdnum.hh"

#include "solveR.hh"
#include "solveL.hh"
#include "LR.hh"

//typedef double number;
typedef float NumberType;

int main(int argc, char ** argv)
{
  if(argc < 2)
  {
    std::cout << "Usage  : ./testLR Dimension" << std::endl;
    std::cout << "Example: ./testLR 7" << std::endl;
    exit(0);
  }
  else
  {
    int n = atoi( argv[1] );
    std::cout << "Dimension=" << n << std::endl;

    hdnum::DenseMatrix<NumberType> A(n, n);
    hdnum::Vector<NumberType> x(n);
    hdnum::Vector<NumberType> b(n);

    // Testmatrix A:
    hdnum::vandermonde(A,x);
    std::cout << "A=" << A << std::endl;

    // Testvektor b
    // Konstruiere b durch Wahl von beliebigem x zur besseren Ergebniskontrolle
    hdnum::fill(x, NumberType(1.0), NumberType(1.0));   // x = (1,2,3,4,...)
    A.mv(b,x);           // b = A*x
    std::cout << "b=A*x=" << b << std::endl;

    // Hilfsvektoren:
    hdnum::Vector<NumberType> y(n); // fuer die Loesung
    hdnum::Vector<NumberType> z(n); // fuer die Zwischenloesung
    hdnum::Vector<std::size_t> p(n); // Indexvektor, speichert die Zeilenvertauschungen

    // Anwenden des Algorithmus
    lr(A, p);
    permute_forward(p, b);  // Wende Zeilenvertauschungen auf b an.
    solveL(A, z, b);         // Loese die Gleichung L*z = b
    solveR(A, y, z);         // Loese die Gleichung R*y = z, d.h. zusammen: L*R*y = b

    // Vergleiche Loesungsvektor y mit der echten Loesung x.
    std::cout << "y=" << y << std::endl;

    std::cout << "||y-x||=" << std::setprecision(15) << (y-x).two_norm() << std::endl;

    return 0;
  }
}
