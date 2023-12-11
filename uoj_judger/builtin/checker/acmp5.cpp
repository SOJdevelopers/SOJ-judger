#include "testlib.h"
#include <cmath>

using namespace std;

const double EPS = 1E-5;

inline bool doubleAbsoluteCompare(double expected, double result, double MAX_DOUBLE_ERROR) {
    if (__testlib_isNaN(expected)) {
        return __testlib_isNaN(result);
    } else if (__testlib_isInfinite(expected)) {
        if (expected > 0) {
            return result > 0 && __testlib_isInfinite(result);
        } else {
            return result < 0 && __testlib_isInfinite(result);
        }
    } else if (__testlib_isNaN(result) || __testlib_isInfinite(result)) {
        return false;
    } else if (__testlib_abs(result - expected) <= MAX_DOUBLE_ERROR + 1E-15) {
        return true;
    } else {
        return false;
    }
}

inline double doubleAbsoluteDelta(double expected, double result) {
    double absolute = __testlib_abs(result - expected);
    return absolute;
}

int main(int argc, char * argv[])
{
    setName("compare two sequences of doubles, max absolute error = %.6lf", EPS);
    registerTestlibCmd(argc, argv);

    int n = 0;
    double j, p;

    while (!ans.seekEof()) 
    {
        n++;
        j = ans.readDouble();
        p = ouf.readDouble();
        if (!doubleAbsoluteCompare(j, p, EPS))
        {
            quitf(_wa, "%d%s numbers differ - expected: '%.6lf', found: '%.6lf', error = '%.6lf'",
                n, englishEnding(n).c_str(), j, p, doubleAbsoluteDelta(j, p));
        }
    }

    if (n == 1)
        quitf(_ok, "found '%.6lf', expected '%.6lf', error '%.6lf'", p, j, doubleAbsoluteDelta(j, p));

    quitf(_ok, "%d numbers", n);
}
