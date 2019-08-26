// lapack.h - Header file for LAPACK routines.
// Copyright (c) 2011 KALX, LLC. All rights reserved. No warranty is made.
#include "mkl_lapack.h"
#define EXCEL12
#include "xll/xll.h"

#define CATEGORY _T("LAPACK")

typedef xll::traits<XLOPERX>::xcstr xcstr;
typedef xll::traits<XLOPERX>::xword xword;
typedef xll::traits<XLOPERX>::xfp xfp;

#include <mkl_trans.h>
namespace mkl {

	// inplace transpose
	inline void dimatcopy(xfp* a)
	{
		mkl_dimatcopy('R', 'T', a->rows, a->columns, 1., a->array, a->columns, a->rows);

		std::swap(a->rows, a->columns);
	}

} // namespace mkl