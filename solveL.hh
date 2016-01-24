//* Assume L = lower triangle of A with l_ii=1, solve L x = b
template<typename T>
void solveL (const hdnum::DenseMatrix<T>& A, hdnum::Vector<T>& x, const hdnum::Vector<T>& b)
{
  if (A.rowsize()!=A.colsize() || A.rowsize()==0)
    HDNUM_ERROR("need square and nonempty matrix");
  if (A.rowsize()!=b.size())
    HDNUM_ERROR("right hand side incompatible with matrix");

  for (std::size_t i=0; i<A.rowsize(); ++i)
  {
    T rhs(b[i]);
    for (std::size_t j=0; j<i; j++)
      rhs -= A[i][j] * x[j];
    x[i] = rhs;
  }
}
