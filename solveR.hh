//* Assume R = upper triangle of A and solve R x = b
template<typename T>
void solveR (const hdnum::DenseMatrix<T>& A, hdnum::Vector<T>& x, const hdnum::Vector<T>& b)
{
  if (A.rowsize()!=A.colsize() || A.rowsize()==0)
    HDNUM_ERROR("need square and nonempty matrix");
  if (A.rowsize()!=b.size())
    HDNUM_ERROR("right hand side incompatible with matrix");

  for (int i=A.rowsize()-1; i>=0; --i)
	{
    T rhs(b[i]);
	  for (std::size_t j=i+1; j<A.colsize(); j++)
		  rhs -= A[i][j] * x[j];
	  x[i] = rhs/A[i][i];
	}
}
