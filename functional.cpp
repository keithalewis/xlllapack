// functional.cpp - functional programming
/*
b = BIND(f,x1,,x3) function of one variable
*/
#include "xll12/xll/xll.h"

using namespace xll;

struct bind {
    std::vector<OPER12> args; // {f,x1,...}
    std::vector<LPXLOPER12> pargs;
    bind(WORD n, LPXLOPER12* px)
        : args(n), pargs(px, px + n)
    {
        for (WORD i = 0; i < n; ++i) {
            args[i] = *(px[i]);
            pargs[i] = &args[i];
        }
    }
    // fill in missing arguments 
    OPER12 operator()(LPXLOPER12* px)
    {
        OPER12 result;

        std::vector<WORD> missing;
        for (WORD i = 1, j = 0; i < args.size(); ++i) {
            if (args[i].isMissing()) {
                missing.push_back(i);
                args[i] = *(px[j++]);
            }
        }

        XLOPER12 operRes;
        int status = Excel12v(xlUDF, &operRes, (int)pargs.size(), &pargs[0]);
        for (WORD i : missing) {
            args[i] = OPER12();
        }
        result = operRes;
        Excel12(xlFree, 0, 1, &operRes);
        ensure (xlretSuccess == status);

        return result;
    }

};

AddIn xai_bind(
    Function(XLL_HANDLE, L"?xll_bind", L"CURRY")
    .Arg(XLL_LPOPER, L"f", L"is a function.")
    .Arg(XLL_LPOPER, L"x1", L"is an argument or missing.")
    .Arg(XLL_LPOPER, L"x2", L"is an argument or missing.")
    .Arg(XLL_LPOPER, L"x3", L"is an argument or missing.")
    .Uncalced()
    .Category(L"XLL")
    .FunctionHelp(L"Bind arguments to a function.")
);
HANDLEX WINAPI xll_bind(LPXLOPER12 pf, LPXLOPER12, LPXLOPER12, LPXLOPER12)
{
#pragma XLLEXPORT
    handlex result;

    try {
        OPER key = AddIn::RegIdMap()[pf->val.num];
        Args args = AddIn::AddInMap()[key];
        WORD n = (WORD)args.Arity();
        handle<bind> h(new bind(n + 1, &pf));
        result = h.get();
    }
    catch (const std::exception& ex) {
        XLL_ERROR(ex.what());
    }

    return result;
}

AddIn xai_call(
    Function(XLL_LPOPER, L"?xll_call", L"UNCURRY")
    .Arg(XLL_HANDLE, L"h", L"is a handle to a result of BIND.")
    .Arg(XLL_LPOPER, L"x1", L"is an argument.")
    .Arg(XLL_LPOPER, L"x2", L"is an argument.")
    .Arg(XLL_LPOPER, L"x3", L"is an argument.")
    .Category(L"XLL")
    .FunctionHelp(L"Call a bound function with arguments.")
);
LPOPER WINAPI xll_call(HANDLEX h, LPXLOPER12 px, LPXLOPER12, LPXLOPER12)
{
#pragma XLLEXPORT
    static OPER12 result;

    try {
        handle<bind> h_(h);
        result = (*h_)(&px);
    }
    catch (const std::exception& ex) {
        XLL_ERROR(ex.what());
    }

    return &result;
}

Auto<OpenAfter> xao_bind([] {
    OPER o(3, 1);
    o[0] = L"dek";
    o[1] = 0.;
    o[2] = 1.;
    LPXLOPER12 x[3];
    x[0] = (LPXLOPER12)&o[0];
    x[1] = (LPXLOPER12)&o[1];
    x[2] = (LPXLOPER12)&o[2];
    bind b(3, x);
    OPER r;
    r = b(nullptr);
    ensure(r == exp(-1));

    return 0;
});