// g++ -I../hdnum/ -o knotenfluss knotenfluss.cc
#include <iostream>
#include <cstdlib>
#include "hdnum.hh"

// Funktion zum Aufstellen der Matrix
template<class NumberType>
void FlussMatrix( hdnum::DenseMatrix<NumberType> &A ){
  int M( A.rowsize() );
  int N( A.colsize() );
  if(M!=N)
    HDNUM_ERROR("Matrix muss quadratisch sein!");

  // TODO Implementieren Sie hier das Aufstellen des Gleichungssystems
}

// Funktion zur Berechnung der Frobenius-Norm einer Matrix
template<class NumberType>
NumberType FrobeniusNorm( const hdnum::DenseMatrix<NumberType> &A ){
  int M(A.rowsize());
  int N(A.colsize());
  if(M!=N)
    HDNUM_ERROR("Matrix muss quadratisch sein!");

  NumberType result=0.0;

  // TODO Implementieren Sie hier die Frobeniusnorm!

  return result;
}

// Funktion zur Berechnung des betragsgrößten Eigenwertes
template<class NumberType>
NumberType MaxEigenwert( const hdnum::DenseMatrix<NumberType> &A )
{
  // TODO: Implementieren Sie hier die Potenzmethode
}

// Hauptprogramm
int main(int argc, char ** argv){

  // Anzahl der Knoten
  const int N(4);
  // Größe der Matrix
  const int n(??);
  // Datentyp für die Matrix
  typedef double REAL;
  // Matrix initialisieren
  hdnum::DenseMatrix<REAL> A(n,n);
  
  // pretty-printing einmal setzen für alle Matrizen
  A.scientific(false);
  A.width(15);

  FlussMatrix(A);

  // TODO Geben Sie hier alle verfügbaren Matrixnormen von A,
  // sowie den maximalen Eigenwert aus.

  return 0;
}
