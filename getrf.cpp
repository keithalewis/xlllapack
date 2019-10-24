// getrf.cpp - compute the LU factorization
// Copyright (c) 2013 KALX, LLC. All rights reserved.
#include "xlllapack.h"

using namespace xll;

static AddInX xai_getrf(
	FunctionX(XLL_FP, _T("?xll_getrf"), _T("GETRF"))
	.Arg(XLL_FP, _T("Matrix"), _T("is a matrix. "))
	.Category(CATEGORY)
	.FunctionHelp(_T("Compute the LU decompostion of Matrix. "))
	.Documentation(
		_T("DGETRF computes an LU factorization of a general M-by-N matrix A ")
		_T("using partial pivoting with row interchanges. ")
		_T("</para><para>")
		_T("The factorization has the form ")
		_T("   A = P * L * U ")
		_T("where P is a permutation matrix, L is lower triangular with unit ")
		_T("diagonal elements (lower trapezoidal if m &gt; n), and U is upper ")
		_T("triangular (upper trapezoidal if m &lt; n). ")
		_T("</para><para>")
		_T("This is the right-looking Level 3 BLAS version of the algorithm. ")
	)
);
xfp* WINAPI xll_getrf(xfp* pa)
{
#pragma XLLEXPORT
	try {
		lapack_int m = pa->rows;
		lapack_int n = pa->columns;
		std::vector<lapack_int> ipiv((std::min)(m, n));
		lapack_int info;

		// DGETRF(&m, &n, pa->array, &m, &ipiv[0], &info);
		info = LAPACKE_dgetrf(LAPACK_ROW_MAJOR, m, n, pa->array, m, &ipiv[0]);
		ensure(info == 0);
	}
	catch (const std::exception & ex) {
		XLL_ERROR(ex.what());

		return 0;
	}

	return pa;
}