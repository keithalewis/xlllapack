#include <algorithm>
#include "xll12/xll/xll.h"

#define _T(s) L##s
#ifndef CATEGORY
#define CATEGORY L"ARRAY"
#endif

using namespace xll;

static AddInX xai_array_set(
	FunctionX(XLL_HANDLE, _T("?xll_array_set"), _T("ARRAY.SET"))
	.Arg(XLL_FP, _T("Array"), _T("is an array of numbers. "))
	.Uncalced()
	.Category(CATEGORY)
	.FunctionHelp(_T("Return a handle to an array."))
	.Documentation(_T("The array is stored in memory and can be retrieved using ARRAY.GET."))
);
HANDLEX WINAPI xll_array_set(const _FP12* pa)
{
#pragma XLLEXPORT
	handle<xll::FP12> ha(new xll::FP12(*pa));

	return ha.get();
}

static AddInX xai_array_get(
	FunctionX(XLL_FP, _T("?xll_array_get"), _T("ARRAY.GET"))
	.Arg(XLL_HANDLE, _T("Handle"), _T("is handle to an array returned by ARRAY.SET. "))
	.Category(CATEGORY)
	.FunctionHelp(_T("Return an array from a handle."))
	.Documentation(_T("Retrieve an array created by ARRAY.SET."))
);
_FP12* WINAPI xll_array_get(HANDLEX h)
{
#pragma XLLEXPORT
	try {
		return handle<xll::FP12>(h)->get();
	}
	catch (const std::exception & ex) {
		XLL_ERROR(ex.what());
	}

	return 0;
}

static AddIn xai_array_apply(
	Function(XLL_LPOPER, L"?xll_array_apply", L"ARRAY.APPLY")
	.Arg(XLL_LPOPER, L"f", L"is a handle to a user defined function.")
	.Arg(XLL_LPOPER, L"x", L"is an array of values for the first argument.")
	.Arg(XLL_LPOPER, L"y", L"is an array of values for the second argument.")
	.Category(CATEGORY)
	.FunctionHelp(L"Return a matrix of values.")
	.Documentation(
		L"Return a two-dimensional array of f(x,y). "
		L"If y is missing then return a one-dimensional array of f(x). "
	)
);
LPOPER WINAPI xll_array_apply(const LPOPER pf, const LPOPER px, const LPOPER py)
{
#pragma XLLEXPORT
	static OPER result;

	try {
		if (py->isMissing()) {
			result.resize(px->size(), 1);

			for (WORD i = 0; i < px->size(); ++i) {
				result[i] = Excel(xlUDF, *pf, (*px)[i]);
			}
		}
		else {
			result.resize(px->size(), py->size());

			for (WORD i = 0; i < px->size(); ++i) {
				for (WORD j = 0; j < py->size(); ++j) {
					result(i, j) = Excel(xlUDF, *pf, (*px)[i], (*py)[j]);
				}
			}
		}
	}
	catch (const std::exception & ex) {
		XLL_ERROR(ex.what());

		return 0;
	}

	return &result;
}

AddIn xai_array_interval(
	Function(XLL_FP, L"?xll_array_interval", L"ARRAY.INTERVAL")
	.Number(L"start", L"is the first value of the array.")
	.Number(L"stop", L"is the last value of the array.")
	.Number(L"step", L"is the step size or count.")
	.Category(L"ARRAY")
	.FunctionHelp(L"Return an interval from start to stop (inclusive).")
	.Documentation(
		L"If step is less than 1, use that as the increment. "
		L"If step is greater than 1, use that as the count for an array of equally spaced elements. "
	)
);
_FP12* WINAPI xll_array_interval(double b, double e, double n)
{
#pragma XLLEXPORT
	static xll::FP12 result;

	try {
		ensure(b < e);
		ensure(n > 0);

		if (n <= 1) {
			result.resize(static_cast<RW>((e - b) / n) + 1, 1);
			for (WORD i = 0; i < result.size(); ++i)
				result[i] = b + i * n;
		}
		else {
			double dx = (e - b) / (n - 1);
			result.resize(static_cast<RW>(n), 1);
			for (WORD i = 0; i < result.size(); ++i)
				result[i] = b + i * dx;
		}

	}
	catch (const std::exception & ex) {
		XLL_ERROR(ex.what());

		return 0;
	}

	return result.get();
}

AddIn xai_array_slice(
	Function(XLL_FP, L"?xll_array_slice", L"ARRAY.SLICE")
	.Array(L"Array", L"is an array for numbers.")
	.Word(L"start", L"is the first index into the the array.")
	.Word(L"stride", L"is the step increment.")
	.Word(L"count", L"is the number of elements to take.")
	.Category(L"ARRAY")
	.FunctionHelp(L"Return a slice of an array.")
	.Documentation(
		L"Return array elements at start, start + stride, ..., start + (count-1)*stride. "
		L"If count is zero then all available elements are taken. "
	)
);
_FP12* WINAPI xll_array_slice(const _FP12* pa, WORD i, WORD di, WORD n)
{
#pragma XLLEXPORT
	static xll::FP12 result;

	try {
		ensure(i < size(*pa));

		if (di == 0)
			di = 1;

		if (n == 0)
			n = static_cast<WORD>((size(*pa) - i) / di);

		result.resize(n, 1);
		for (WORD j = 0; j < n; ++j)
			result[j] = pa->array[i + j * di];
	}
	catch (const std::exception & ex) {
		XLL_ERROR(ex.what());

		return 0;
	}

	return result.get();
}

AddIn xai_array_sort(
	Function(XLL_FP, L"?xll_array_sort", L"ARRAY.SORT")
	.Array(L"array", L"is the array to be sorted.")
	.Long(L"n", L"is the number of elements to sort.")
	.Category(CATEGORY)
	.FunctionHelp(L"Sort an array of numbers.")
	.Documentation(LR"(
Sort an array in numeric order. If n is zero then all elements are sorted from high to low. 
If n is -1 all elements are sorted from low to high. Other values of n perform a partial sort
in decending order if n is positive and increasing order if n is negative.
)")
);
_FP12* WINAPI xll_array_sort(_FP12* pa, LONG n)
{
#pragma XLLEXPORT

	if (n == 0) {
		std::sort(begin(*pa), end(*pa));
	}
	else if (n == -1) {
		std::sort(begin(*pa), end(*pa), std::less<double>{});
	}
	else if (n > 0) {
		std::partial_sort(begin(*pa), pa->array + n, end(*pa));
	}
	else {
		std::partial_sort(begin(*pa), pa->array - n, end(*pa), std::less<double>{});
	}

	return pa;
}

AddIn xai_array_grade(
	Function(XLL_FP, L"?xll_array_grade", L"ARRAY.GRADE")
	.Array(L"array", L"is the array to be graded.")
	.Long(L"n", L"is the number of elements to grade.")
	.Category(CATEGORY)
	.FunctionHelp(L"Grade an array of numbers.")
	.Documentation(LR"(
Grade an array in numeric order. If n is zero then all elements are graded from high to low. 
If n is -1 all elements are graded from low to high. Other values of n perform a partial grade
in decending order if n is positive and increasing order if n is negative.
The result of INDEX(a, 1 + ARRAY.GRADE(a,n)) is identical to ARRAY.SORT(a,n). 
)")
);
#pragma warning(push)
#pragma warning(disable: 4244)
_FP12* WINAPI xll_array_grade(const _FP12* pa, LONG n)
{
#pragma XLLEXPORT
	static xll::FP12 iota;

	iota.resize(size(*pa));

	for (int i = 0; i < iota.size(); ++i)
		iota[i] = i;

	const double* a = pa->array;
	const auto& p = [n, a](int i, int j) {
		return n >= 0 ? a[i] < a[j] : a[i] > a[j];
	};

	if (n == 0 || n == -1) {
		std::sort(iota.begin(), iota.end(), p);
	}
	else {
		std::partial_sort(iota.begin(), iota.begin() + abs(n), iota.end(), p);
	}

	return iota.get();
}
#pragma warning(pop)

#include <random>


// use MKL vector random number generator???

static std::default_random_engine e;

static AddInX xai_array_random(
	FunctionX(XLL_FP, _T("?xll_array_random"), _T("ARRAY.RANDOM"))
	.Arg(XLL_WORD, _T("Rows"), _T("is the number of rows."))
	.Arg(XLL_WORD, _T("Columns"), _T("is the number of columns."))
	.Arg(XLL_DOUBLE, _T("_Min"), _T("is the optional lower bound of the random numbers generated. Default is 0."))
	.Arg(XLL_DOUBLE, _T("_Max"), _T("is the optional upper bound of the random numbers generated. Default is 1. "))
	.Category(CATEGORY)
	.FunctionHelp(_T("Return a Rows x Columns array of uniformly distributed random numbers between Min and Max."))
	.Documentation(_T("Uses std::default_random_engine and std::uniform_real_distribution."))
);
_FP12* xll_array_random(WORD r, WORD c, double min, double max)
{
#pragma XLLEXPORT
	static xll::FP12 a;

	a.resize(r, c);

	if (max == 0 && min == 0)
		max = 1;

	std::uniform_real_distribution<double> u(min, max);

	for (WORD i = 0; i < a.size(); ++i)
		a[i] = u(e);

	return a.get();
}
