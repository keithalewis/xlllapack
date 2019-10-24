// getri.cpp - invert a matrix
// Copyright (c) 2013 KALX, LLC. All rights reserved.
#include "xlllapack.h"

using namespace xll;

static AddInX xai_getri(
	FunctionX(XLL_FP, _T("?xll_getri"), _T("GETRI"))
	.Arg(XLL_FP, _T("Matrix"), _T("is the matrix to be inverted. "))
	.Category(CATEGORY)
	.FunctionHelp(_T("Call DGETRI to invert a square matrix."))
	.Documentation(
		_T("DGETRI computes the inverse of a matrix using the LU factorization ")
		_T("computed by DGETRF. ")
		_T("</para><para>")
		_T("This method inverts U and then computes inv(A) by solving the system ")
		_T("inv(A)*L = inv(U) for inv(A). ")
	)
);
xfp* WINAPI xll_getri(xfp* pa)
{
#pragma XLLEXPORT
	try {
		ensure(pa->rows == pa->columns);

		lapack_int n = pa->rows;
		lapack_int info, lwork(-1);
		std::vector<lapack_int> ipiv(n);
		std::vector<double> work(1);

		// get optimal work size
		// DGETRI(&n, pa->array, &n, &ipiv[0], &work[0], &lwork, &info);
		info = LAPACKE_dgetri(LAPACK_ROW_MAJOR, n, pa->array, n, &ipiv[0]);
		ensure(info == 0);
		lwork = (int)work[0];
		work.resize(lwork);

		// DGETRF(&n, &n, pa->array, &n, &ipiv[0], &info);
		info = LAPACKE_dgetrf(LAPACK_ROW_MAJOR, n, n, pa->array, n, &ipiv[0]);
		ensure(info == 0);
		// DGETRI(&n, pa->array, &n, &ipiv[0], &work[0], &lwork, &info);
		info = LAPACKE_dgetri(LAPACK_ROW_MAJOR, n, pa->array, n, &ipiv[0]);
		ensure(info == 0);
	}
	catch (const std::exception & ex) {
		XLL_ERROR(ex.what());

		return 0;
	}

	return pa;
}