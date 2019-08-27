// gesv.cpp - computes the solution to system of linear equations A * X = B for GE matrices 
#include "xlllapack.h"

using namespace xll;

static AddInX xai_gesv(
	FunctionX(XLL_FP, _T("?xll_gesv"), _T("GESV"))
	.Arg(XLL_FP, _T("A"), _T("is a square matrix."))
	.Arg(XLL_FP, _T("B"), _T("is a matrix having the same number of rows as A. "))
	.Category(CATEGORY)
	.FunctionHelp(_T("Call DGESV to solve AX = B for X."))
	.Documentation(
	_T("DGESV computes the solution to a real system of linear equations")
		_T("<quote>A * X = B,</quote>")
	 _T("where A is an N-by-N matrix and X and B are N-by-NRHS matrices.")
	 _T("</para><para>")
	 _T("The LU decomposition with partial pivoting and row interchanges is")
	 _T("used to factor A as")
		_T("<quote>A = P * L * U,</quote>")
	 _T("where P is a permutation matrix, L is unit lower triangular, and U is")
	 _T("upper triangular.  The factored form of A is then used to solve the")
	 _T("system of equations A * X = B.")
	)
);
xfp* WINAPI xll_gesv(xfp* pa, xfp* pb)
{
#pragma XLLEXPORT
	static FPX x;

	try {
		ensure (pa->rows == pa->columns);
		ensure (pa->rows == pb->rows);

		lapack_int n = pa->rows;
		lapack_int m = pb->columns;
		std::vector<lapack_int> ipiv(n);
		lapack_int info;

		//		dgetrf(&n, &n, pa->array, &n, &ipiv[0], &info);
		info = LAPACKE_dgetrf(LAPACK_ROW_MAJOR, n, m, pa->array, n, &ipiv[0]);
		ensure (info == 0);

		//		dgetrs(&trans, &n, &m, pa->array, &n, &ipiv[0], pb->array, &n, &info);
		info = LAPACKE_dgetrs(LAPACK_ROW_MAJOR, 'T', n, m, pa->array, n, &ipiv[0], pb->array, n);
		ensure(info == 0);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());

		return 0;
	}

	return pb;
}