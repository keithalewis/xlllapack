// xlllapack.h - Header file for LAPACK routines.
// Copyright (c) 2011 KALX, LLC. All rights reserved. No warranty is made.
#define EXCEL12
//#define HAVE_LAPACK_CONFIG_H
//#define LAPACK_COMPLEX_STRUCTURE
//extern "C" {
#include "mkl_lapacke.h"
//}
#include "xll12/xll/xll.h"
#define _T(s) L##s

#define CATEGORY _T("LAPACK")

using FPX = xll::FP12;
using xcstr = const wchar_t*;
using xword = WORD;
using xfp = _FP12;

