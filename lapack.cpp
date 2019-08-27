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

Auto<Open> xao([]() { _crtBreakAlloc = 3815; return 0; });