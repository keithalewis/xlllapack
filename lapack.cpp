// lapack.cpp - BLAS routines from MKL
// Copyright (c) 2011 KALX, LLC. All rights reserved. No warranty is made.
#include "xlllapack.h"

using namespace xll;

#ifdef _DEBUG
static AddInX xai_lapack(
	Documentation(
		_T("LAPACK (Linear Algebra PACKage) is a software library for numerical linear algebra. ")
		_T("It provides routines for solving systems of linear equations and linear least squares, ")
		_T("eigenvalue problems, and singular value decomposition. ")
		_T("It also includes routines to implement the associated matrix factorizations such as ")
		_T("LU, QR, Cholesky and Schur decomposition. ")
		_T("LAPACK was originally written in FORTRAN 77 and is now written in Fortran 90. ")
	)
);
#endif

static AddInX xai_array_set(
	FunctionX(XLL_HANDLEX, _T("?xll_array_set"), _T("ARRAY.SET"))
	.Arg(XLL_FPX, _T("Array"), _T("is an array of numbers. "))
	.Uncalced()
	.Category(CATEGORY)
	.FunctionHelp(_T("Return a handle to an array."))
	.Documentation(_T("The array is stored in member."))
);
HANDLEX WINAPI xll_array_set(const xfp* pa)
{
#pragma XLLEXPORT
	handle<FPX> ha(new FPX(*pa));

	return ha.get();
}

static AddInX xai_array_get(
	FunctionX(XLL_FPX, _T("?xll_array_get"), _T("ARRAY.GET"))
	.Arg(XLL_HANDLEX, _T("Handle"), _T("is handle to an arry returned by ARRAY.SET. "))
	.Category(CATEGORY)
	.FunctionHelp(_T("Return a handle to an array."))
	.Documentation(_T(""))
);
xfp* WINAPI xll_array_get(HANDLEX h)
{
#pragma XLLEXPORT
	handle<FPX> ha(h);

	return ha->get();
}

#include <random>

// use MKL vector random number generator???

static std::default_random_engine e;

static AddInX xai_array_random(
	FunctionX(XLL_FPX, _T("?xll_array_random"), _T("ARRAY.RANDOM"))
	.Arg(XLL_WORDX, _T("Rows"), _T("is the number of rows."))
	.Arg(XLL_WORDX, _T("Columns"), _T("is the number of columns."))
	.Arg(XLL_DOUBLEX, _T("_Min"), _T("is the optional lower bound of the random numbers generated. Default is 0."))
	.Arg(XLL_DOUBLEX, _T("_Max"), _T("is the optional upper bound of the random numbers generated. Default is 1. "))
	.Category(CATEGORY)
	.FunctionHelp(_T("Return a Rows x Columns array of uniformly distributed random numbers between Min and Max."))
	.Documentation(_T(""))
);
xfp* xll_array_random(xword r, xword c, double min, double max)
{
#pragma XLLEXPORT
	static FPX a;
	
	a.resize(r, c);

	if (max == 0 && min == 0)
		max = 1;

	std::uniform_real_distribution<double> u(min, max);

	for (xword i = 0; i < a.size(); ++i)
		a[i] = u(e);

	return a.get();
}
