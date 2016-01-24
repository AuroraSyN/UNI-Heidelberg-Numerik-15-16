template<typename T>
void lr(hdnum::DenseMatrix<T>& A, hdnum::Vector<std::size_t>& perm)
{
  if (A.rowsize()!=A.colsize() || A.rowsize()==0)
    HDNUM_ERROR("need square and nonempty matrix");

  if (A.rowsize()!=perm.size())
    HDNUM_ERROR("permutation vector incompatible with matrix");

  // transformation to upper triangular
  for(std::size_t k=0; k<A.rowsize()-1; ++k )
  {
    // find a row with non-zero element and exchange rows
    for (std::size_t r=k; r<A.rowsize(); ++r)
    {
      // Die folgende Zeile hat den folgenden Hintergrund:
      // Testen ob ein Matrixeintrag 0 ist, kann in C++ nur
      // bedingt mit dem Operator == gemacht werden. Dies
      // funktioniert dann, wenn der Eintrag explizit
      // auf 0 gesetzt. In der Praxis ergeben sich aber auch
      // 'numerische' Nullen. Sie können zur Verdeutlichung
      // des Sachverhalts das folgende kleine Programm anschauen:
      // 
      // #include<iostream>
      // #include<cmath>
      // 
      // int main()
      // {
      //   double x = 0.;
      //   double y = std::sin(M_PI);
      //   std::cout << "x==0: " << (x==0.) << std::endl;
      //   std::cout << "y==0: " << (y==0.) << std::endl;
      // }
      //
      // Das Problem wird üblicherweise durch Definition eines
      // Schwellenwerts für 0 gelöst. So auch hier:
      //if (std::abs(A[r][k]) > 1e-8)
      if (A[r][k] != 0)
      {
        if (r>k)
        {
          // exchange complete row if r!=k
          for (std::size_t j=0; j<A.colsize(); ++j){
            T temp(A[k][j]);
            A[k][j] = A[r][j];
            A[r][j] = temp;
          }
        }
        perm[k]=r;
        break;
      }
    }

    if (A[k][k]==0)
      HDNUM_ERROR("matrix is singular");

    // modification
    for (std::size_t i=k+1; i<A.rowsize(); ++i)
    {
      T qik(A[i][k]/A[k][k]);
      A[i][k] = qik;                // left lower part of A becomes L
      for (std::size_t j=k+1; j<A.colsize(); ++j)
        A[i][j] -= qik * A[k][j];   // right upper part of A becomes R
    }
  }
}

//* apply permutations to a right hand side vector
template<typename T>
void permute_forward(const hdnum::Vector<std::size_t>& perm, hdnum::Vector<T>& b)
{
  if (b.size()!=perm.size())
    HDNUM_ERROR("permutation vector incompatible with rhs");

  for (std::size_t k=0; k<b.size()-1; ++k)
  {
    if (perm[k]!=k)
    {
      T temp(b[k]);
      b[k] = b[perm[k]];
      b[perm[k]] = temp;
    }
  }
}
