// dek.cpp - double exponential kernel Tf(x) = int_0^1 exp(-|x - y|) f(y) dy
#include "xll12/xll/xll.h"

using namespace xll;

AddIn xai_dek(
    Function(XLL_FP, L"?xll_dek", L"DEK")
    .Arg(XLL_WORD, L"n", L"is the reciprocal step size.")
    .Category(L"LAPACK")
    .FunctionHelp(L"Return discretized double exponential kernel.")
    .Documentation(LR"(
    This function returns a discretization of the linear operator 
    Tf(x) = &#8747;<subscript>0</subscript><superscript>1</superscript> exp(-|x - y|) f(y) dy 
    defined on L<superscript>2</superscript>[0,1].
    The kernel is evaluated at points i/n for 0 &#8804; i &#8804; n. 
    )")
);
_FP12* WINAPI xll_dek(WORD n)
{
#pragma XLLEXPORT
    static xll::FP12 k;

    k.resize(n + 1, n + 1);
    for (WORD i = 0; i <= n; ++i) {
        for (WORD j = i; j <= n; ++j) {
            k(j,i) = k(i, j) = exp(-fabs(i - j) / n);
        }
    }

    return k.get();
}

