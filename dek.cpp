// dek.cpp - double exponential kernel Tf(x) = int_0^1 exp(-|x - y|) f(y) dy
#include "xll12/xll/xll.h"

using namespace xll;

/*
This function returns a discretization of the linear operator
Tf(x) = &#8747; < subscript>0 < / subscript > < superscript>1 < / superscript > exp(-| x - y | ) f(y) dy
defined on L < superscript>2 < / superscript > [0, 1].
The kernel is evaluated at points i / n for 0 & #8804; i& #8804; n.
*/

AddIn xai_dek(
    Function(XLL_DOUBLE, L"?xll_dek", L"DEK")
    .Arg(XLL_DOUBLE, L"x", L"is first argument.")
    .Arg(XLL_DOUBLE, L"y", L"is the second argument.")
    .Category(L"LAPACK")
    .FunctionHelp(L"Return the double exponential kernel.")
    .Documentation(LR"(
The double exponential kernel is k(x,y) = exp(-|x - y|).
    )")
);
double WINAPI xll_dek(double x, double y)
{
#pragma XLLEXPORT
    return exp(-fabs(x - y));
}

