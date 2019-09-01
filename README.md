# Excel add-in wrappers for LAPACK.

This add-in allows you to call LAPACK functions from Excel.
It works by creating in-memory C++ objects that return _handles_
that allow Excel to approach the speed of native code.

The functions [`ARRAY.SET`](https://keithalewis.github.io/xlllapack/html/10D065B4-0000-0000-0000-000000000000.htm)
and [`ARRAY.GET`](https://keithalewis.github.io/xlllapack/html/3BE47A40-0000-0000-0000-000000000000.htm)
access 2-dimensional arrays
of floating point numbers in memory so they don't take up real estate
in your worksheet. They can be acted on by [`ARRAY.APPLY`](https://keithalewis.github.io/xlllapack/html/71E97900-0000-0000-0000-000000000000.htm) and accessed
using [`ARRAY.SLICE`](https://keithalewis.github.io/xlllapack/html/37806B6A-0000-0000-0000-000000000000.htm).

You will need [Visual Studio 2019](https://visualstudio.microsoft.com/vs/)
and [Intel MKL](https://software.intel.com/en-us/mkl) for Windows. Be sure
to install the option to integrate with Visual Studio 2019.

Clone (or fork and clone) [xlllapack](https://github.com/keithalewis/xlllapack),
set the build configuration to `Debug` and either `Win32` or `x64` depending
on whether you have 32 or 64-bit Excel. Pressing `F5` should build the
add-in and start Excel with the add-in loaded. Use Ctrl-O to browse for example
spreadsheets.

You will have a much more pleasant experience if you enroll in the Office Insider Program.
This version returns the entire output of array functions.

Full documentation for the add-in can be found [here](https://keithalewis.github.io/xlllapack/).
